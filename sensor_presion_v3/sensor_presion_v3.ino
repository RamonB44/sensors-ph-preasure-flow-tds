#include "ADS1X15.h"
#include "Arduino.h"
#include "Wire.h"  //allows communication over i2c devices

const int pressureZero = 6291.45;              //analog reading of pressure transducer at 0psi or 0MPa
const int pressureMax = 58982.4;               //analog reading of pressure transducer at 1450.38psi or 10MPa
const int pressuretransducermaxPSI = 1450.38;  //psi value of transducer being used
const int baudRate = 9600;                     //constant integer to set the baud rate for serial monitor
const int sensorreadDelay = 1000;              //constant integer to set the sensor read delay in milliseconds

float pressureValue = 0;  //variable to store the value coming from the pressure transducer

ADS1115 ADS(0x48);

void setup()  //setup routine, runs once when system turned on or reset
{
  Serial.begin(baudRate);  //initializes serial communication at set baud rate bits per second
  Wire.begin();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  ADS.begin();
}

void loop()  //loop routine runs over and over again forever
{
  int16_t val_0 = ADS.readADC(0);      // read analog value from A0 in ADS
  float vol_0 = ADS.toVoltage(val_0);  // convert analog value into voltage value
  pressureValue = val_0;
  pressureValue = ((pressureValue - pressureZero) * pressuretransducermaxPSI) / (pressureMax - pressureZero);  //conversion equation to convert analog reading to psi

  Serial.print("\tAnalog0: ");
  Serial.println(val_0);
  Serial.print("\tVoltage: ");
  Serial.println(vol_0, 5);  // print voltage with 5 decimals
  Serial.print("psi: ");
  Serial.println(pressureValue, 1);  //prints presasure value from decimal
  delay(sensorreadDelay);            //delay in milliseconds between read values
}