/*!
 * @file DFRobot_PH_Test.h
 * @brief This is the sample code for Gravity: Analog pH Sensor / Meter Kit V2, SKU:SEN0161-V2.
 * @n In order to guarantee precision, a temperature sensor such as DS18B20 is needed, to execute automatic temperature compensation.
 * @n You can send commands in the serial monitor to execute the calibration.
 * @n Serial Commands:
 * @n    enterph -> enter the calibration mode
 * @n    calph   -> calibrate with the standard buffer solution, two buffer solutions(4.0 and 7.0) will be automaticlly recognized
 * @n    exitph  -> save the calibrated parameters and exit from calibration mode
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Jiawei Zhang](jiawei.zhang@dfrobot.com)
 * @version  V1.0
 * @date  2018-11-06
 * @url https://github.com/DFRobot/DFRobot_PH
 */

// 65536 Bit resolution ADS 11X5

#include "DFRobot_PH.h"
#include <EEPROM.h>
#include "ADS1X15.h"
#include "Wire.h"  //allows communication over i2c devices

#define PH_PIN A0 // default pin for ESP8622
float voltage, phValue, phValueESP, temperature = 25;
float neutralAV = 1500, acidAV = 2032.44;
int baudRate = 9600;
int16_t val_0;
float vol_0;
DFRobot_PH ph;

ADS1115 ADS(0x48);

void setup() {
  Serial.begin(baudRate);
  ph.setRange(neutralAV,acidAV);
  ph.begin();
  Wire.begin();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  ADS.begin();
}

void loop() {
  static unsigned long timepoint = millis();
  ADS.setGain(0);
  if (millis() - timepoint > 1000U) {  //time interval: 1s
    timepoint = millis();
    //temperature = readTemperature();         // read your temperature sensor to execute temperature compensation
    voltage = (analogRead(PH_PIN) / 1023.0) * 5000;  // read the voltage
    val_0 = ADS.readADC(0);
    vol_0 = ADS.toVoltage(val_0);
    float val_1 = (val_0 / 65535.0) * 5000;
    Serial.print("Voltage ADC: ");
    Serial.print(vol_0, 2);
    Serial.print(" R AV ADC: ");
    Serial.print(val_0);
    Serial.print(" AV ADC: ");
    Serial.println(val_1);
    phValue = ph.readPH(val_1, temperature);  // convert voltage to pH with temperature compensation
    phValueESP = ph.readPH(voltage, temperature);  // convert voltage to pH with temperature compensation
    Serial.print("Analog Value ESP8266: ");
    Serial.println(analogRead(PH_PIN));
    Serial.print("temperature:");
    Serial.print(temperature, 1);
    Serial.print("^C  pH:");
    Serial.println(phValue, 3);
    Serial.print("^C  pH ESP:");
    Serial.println(phValueESP, 3);
  }
  ph.calibration(voltage, temperature);  // calibration process by Serail CMD
}

float readTemperature() {
  //add your code here to get the temperature from your temperature sensor
}