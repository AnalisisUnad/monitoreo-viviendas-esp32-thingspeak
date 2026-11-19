# Sistema de monitoreo ambiental de viviendas con ESP32 y ThingSpeak

Prototipo funcional desarrollado para el curso Proyecto de grado (202016907) de la Universidad Nacional Abierta y a Distancia - UNAD.

## Descripción

El sistema permite monitorear tres variables ambientales asociadas a viviendas de Bogotá:

- Temperatura ambiental.
- Humedad relativa.
- Concentración simulada de CO2.

El ESP32 realiza la adquisición y procesamiento de los datos dentro del entorno Wokwi. Posteriormente, los valores son transmitidos mediante WiFi hacia ThingSpeak para su almacenamiento, visualización y seguimiento.

## Tecnologías utilizadas

- ESP32.
- DHT22.
- Entrada analógica para simulación de CO2.
- LCD 16x2 con interfaz I2C.
- Wokwi.
- ThingSpeak.

## Enlaces del prototipo

Wokwi:
https://wokwi.com/projects/481140252651954177

ThingSpeak - canal público:
https://thingspeak.mathworks.com/channels/3588736

## Campos de ThingSpeak

- Field 1: Temperatura.
- Field 2: Humedad.
- Field 3: CO2.

## Archivos

- `sketch.ino`: código fuente del ESP32.
- `diagram.json`: configuración de componentes y conexiones para Wokwi.
- `libraries.txt`: bibliotecas requeridas por el simulador.

## Seguridad

La clave de escritura de ThingSpeak no se publica en este repositorio. Para ejecutar una copia del proyecto debe reemplazarse `REEMPLAZAR_CON_WRITE_API_KEY` por una Write API Key válida del canal correspondiente.

## Alcance

La concentración de CO2 se representa mediante una entrada analógica simulada. El prototipo está orientado a validar la integración funcional entre adquisición, procesamiento, visualización local y transmisión IoT; no constituye un instrumento de medición ambiental certificado.
# Sistema de monitoreo ambiental de viviendas con ESP32 y ThingSpeak

Proyecto académico desarrollado para el curso Proyecto de grado (202016907) de la Universidad Nacional Abierta y a Distancia - UNAD.

## Descripción

El prototipo permite simular, procesar y transmitir tres variables ambientales asociadas con viviendas de Bogotá:

- Temperatura ambiental.
- Humedad relativa.
- Concentración simulada de CO2.

El ESP32 funciona como unidad central de procesamiento. La simulación se ejecuta en Wokwi y los datos son enviados a ThingSpeak para su almacenamiento, visualización y seguimiento.

## Tecnologías utilizadas

- ESP32.
- DHT22.
- Entrada analógica para simulación de CO2.
- LCD I2C 16x2.
- Wokwi.
- ThingSpeak.
- Arduino/C++.

## Arquitectura

Wokwi -> ESP32 -> adquisición de datos -> procesamiento -> transmisión -> ThingSpeak -> visualización.

## ThingSpeak

Channel ID: 3588736

Campos configurados:

1. Temperatura.
2. Humedad.
3. CO2.

La Write API Key no se publica en este repositorio por seguridad. Para reproducir el proyecto se debe reemplazar el marcador `REEMPLAZAR_CON_WRITE_API_KEY` por una clave de escritura válida.

## Simulación en Wokwi

https://wokwi.com/projects/481140252651954177

## Canal de visualización en ThingSpeak

https://thingspeak.mathworks.com/channels/3588736

## Consideraciones

La variable de CO2 utilizada en la simulación representa un valor generado mediante una entrada analógica. No corresponde a la calibración de un sensor físico de CO2 ni debe utilizarse como medición certificada de calidad ambiental.

## Autor académico

José Ricardo Castro González

Universidad Nacional Abierta y a Distancia - UNAD.
