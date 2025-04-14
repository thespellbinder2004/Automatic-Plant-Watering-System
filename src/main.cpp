#include <Arduino.h>
#include <Wire.h>
#include "lcd_display.h"
#include "soilSensor.h"
#include "config.h"
// Based on joseph testing, approx min = 2100, approx max = 3000
#define relayPin RELAY_PIN

int soilMoisturePercentage = 0;
void taskDisplay(void *parameter){
  while (true){
    lcdDisplay::lcdWriteFormatted("Moisture: " + String(soilMoisturePercentage) + "%");
    delay(300);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  lcdDisplay::lcdInit();

  pinMode(relayPin, OUTPUT);

  lcdDisplay::lcdPrintTopBottom("We love you sir", "Rengel Corpuz");
  delay(2000);
  xTaskCreate(taskDisplay, "Task 1", 2048, NULL, 1, NULL);

}


int startTime = 0;
int duration = 0;

void loop() {
  Serial.println(SoilSensor::getSoilMoistureCapacitance());
  soilMoisturePercentage = SoilSensor::getSoilMoisturePercentage();
  if (soilMoisturePercentage <= 60){
    digitalWrite(relayPin, HIGH);
  }
  if (soilMoisturePercentage > 60){
    digitalWrite(relayPin, LOW);
  }
  delay(5);
}
