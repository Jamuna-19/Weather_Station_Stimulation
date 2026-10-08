#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!ina219.begin()) {
    Serial.println("INA219 not found!");
    while (1);
  }

  ina219.setCalibration_32V_2A();
}

void loop() {

int bulbADC = analogRead(A0);
float bulbVoltage = (bulbADC *5)/ 1023;
  float loadVoltage = ina219.getBusVoltage_V();
  float shuntVoltage = ina219.getShuntVoltage_mV();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();


  float buckOutputVoltage =
      loadVoltage + (shuntVoltage / 1000.0);


  Serial.print("TP5100 Input Voltage: ");
  Serial.print(buckOutputVoltage, 2);
  Serial.println(" V");

Serial.print("Bulb Voltage: ");
Serial.print(bulbVoltage, 2);
Serial.println(" V");

  Serial.print("TP5100 Output Voltage: ");
  Serial.print(loadVoltage, 2);
  Serial.println(" V");

  Serial.print("Load Current: ");
  Serial.print(current_mA, 2);
  Serial.println(" mA");

  Serial.print("Load Power: ");
  Serial.print(power_mW, 2);
  Serial.println(" mW");

  Serial.println();

  delay(5000);
}
