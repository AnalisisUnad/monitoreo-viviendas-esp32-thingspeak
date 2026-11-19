/*
  UNIVERSIDAD NACIONAL ABIERTA Y A DISTANCIA - UNAD

  Curso: Proyecto de grado - 202016907
  Grupo: 104
  Estudiante: José Ricardo Castro González

  PROYECTO:
  Sistema de monitoreo y alerta de temperatura,
  humedad y concentración de CO2 en viviendas
  de Bogotá mediante ESP32 y plataforma ThingSpeak.

  DISPOSITIVO: ESP32
  ENTORNO DE SIMULACIÓN: Wokwi

  VARIABLES:
  1. Temperatura ambiental - DHT22
  2. Humedad relativa - DHT22
  3. Concentración de CO2 - Entrada analógica simulada

  PLATAFORMA: ThingSpeak
*/

#include <Arduino.h>
#include <DHTesp.h>
#include <WiFi.h>
#include <ThingSpeak.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

const int DHT_PIN = 13;
const int CO2_PIN = 35;

DHTesp dht;
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient client;

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const unsigned long CHANNEL_ID = 3588736;
const char* WRITE_API_KEY = "REEMPLAZAR_CON_WRITE_API_KEY";

float temperatura = NAN;
float humedad = NAN;
int co2 = 0;
bool dhtValido = false;

unsigned long ultimaLectura = 0;
unsigned long ultimoEnvio = 0;

const unsigned long intervaloLectura = 2500;
const unsigned long intervaloEnvio = 20000;

void conectarWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password, 6);

  Serial.print("Conectando a WiFi");
  unsigned long inicio = millis();

  while (WiFi.status() != WL_CONNECTED &&
         millis() - inicio < 15000) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi conectado correctamente");
    Serial.print("Direccion IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Error de conexion WiFi");
  }
}

void leerVariables() {
  TempAndHumidity datos = dht.getTempAndHumidity();

  dhtValido = isfinite(datos.temperature) &&
              isfinite(datos.humidity);

  if (dhtValido) {
    temperatura = datos.temperature;
    humedad = datos.humidity;
  }

  int lecturaCO2 = analogRead(CO2_PIN);
  co2 = map(lecturaCO2, 0, 4095, 400, 2000);
  co2 = constrain(co2, 400, 2000);

  lcd.clear();
  lcd.setCursor(0, 0);

  if (dhtValido) {
    lcd.print("T:");
    lcd.print(temperatura, 1);
    lcd.print("C H:");
    lcd.print(humedad, 0);
    lcd.print("%");
  } else {
    lcd.print("Error DHT22");
  }

  lcd.setCursor(0, 1);
  lcd.print("CO2:");
  lcd.print(co2);
  lcd.print(" ppm");

  Serial.println("--------------------------------");

  if (dhtValido) {
    Serial.print("Temperatura: ");
    Serial.print(temperatura, 1);
    Serial.println(" C");

    Serial.print("Humedad relativa: ");
    Serial.print(humedad, 1);
    Serial.println(" %");
  } else {
    Serial.println("Error de lectura del DHT22");
  }

  Serial.print("CO2 simulado: ");
  Serial.print(co2);
  Serial.println(" ppm");
}

void enviarDatosThingSpeak() {
  if (!dhtValido) {
    Serial.println("No se envian datos: lectura DHT22 no valida");
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    conectarWiFi();

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("No fue posible enviar los datos a ThingSpeak");
      return;
    }
  }

  ThingSpeak.setField(1, temperatura);
  ThingSpeak.setField(2, humedad);
  ThingSpeak.setField(3, co2);

  int respuesta = ThingSpeak.writeFields(CHANNEL_ID, WRITE_API_KEY);

  if (respuesta == 200) {
    Serial.println("Datos enviados correctamente a ThingSpeak");
  } else {
    Serial.print("Error al enviar datos a ThingSpeak. Codigo: ");
    Serial.println(respuesta);
  }
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  dht.setup(DHT_PIN, DHTesp::DHT22);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("MONITOREO");
  lcd.setCursor(0, 1);
  lcd.print("AMBIENTAL");

  conectarWiFi();
  ThingSpeak.begin(client);

  ultimaLectura = millis() - intervaloLectura;
  ultimoEnvio = millis();

  Serial.println("Sistema de monitoreo iniciado");
}

void loop() {
  unsigned long ahora = millis();

  if (ahora - ultimaLectura >= intervaloLectura) {
    ultimaLectura = ahora;
    leerVariables();
  }

  if (ahora - ultimoEnvio >= intervaloEnvio) {
    ultimoEnvio = ahora;
    enviarDatosThingSpeak();
  }

  delay(20);
}

