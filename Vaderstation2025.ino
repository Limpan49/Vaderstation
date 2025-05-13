/* 
File: Vaderstation2025.ino
Author: Linus Ahlgren
Date: 2025-05-13
Description: En väderstation som mäter lufttryck, två olika luftfuktigheter och två olika temperaturer. 
*/

// Bilbloteken som används
#include "thingProperties.h"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

#define DHTPIN 2           // Sensor 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define BMP280_ADDRESS 0x76
Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // De olika sensorerna
  if (!bmp.begin(BMP280_ADDRESS)) {
    Serial.println("Kunde inte hitta BMP280!");
    while (1);
  }

  dht.begin();
}

void loop() {
  ArduinoCloud.update();

  // Läsning från sensorerna
  float h = dht.readHumidity();
  float tDHT = dht.readTemperature();
  float tBMP = bmp.readTemperature();
  float p = bmp.readPressure() / 100.0; // hPa

  // DHT-värden och kontroll 
  if (!isnan(h) && !isnan(tDHT)) {
    humidity = h;
    tempDHT = tDHT;
  } else {
    Serial.println("Fel vid läsning från DHT11!");
  }

  tempBMP = tBMP;
  pressure = p;

  // Seriel utskrift
  Serial.print("DHT11 Temp: "); Serial.print(tempDHT);
  Serial.print(" °C, Humidity: "); Serial.print(humidity);
  Serial.print(" %, BMP Temp: "); Serial.print(tempBMP);
  Serial.print(" °C, Pressure: "); Serial.print(pressure); Serial.println(" hPa");

  // Väntar 2 sekunder
  delay(2000); 
}
