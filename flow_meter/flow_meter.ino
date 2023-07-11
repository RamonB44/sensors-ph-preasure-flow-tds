#include "ADS1X15.h"

int FLOW_PIN = 2;
double FLOW_RATE;
volatile int COUNT;
int FLOW_CONSTANTE = 4.00;  // 1 L / 250 pulsos segun especificacion de fabricante * 1000 mL | Este valor es solo proporcionado por el fabricante pero puede variar

void setup() {
  Serial.begin(9600);
  pinMode(FLOW_PIN, INPUT);
  attachInterrupt(0, FLOW, RISING);
  Wire.begin();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);

  ADS.begin();
}

void loop() {
  ADS.setGain(0);
  COUNT = 0;
  interrupts();
  delay(1000);
  noInterrupts();

  FLOW_RATE = (COUNT * FLOW_CONSTANTE);
  WATER_FLOW_MEASURE = FLOW_RATE;
  FLOW_RATE = FLOW_RATE * 60;
  FLOW_RATE = FLOW_RATE / 1000;

  Serial.println("FLOWRATE: " + FLOW_RATE + " l/min");
  Serial.println("WATERFLOW_MEASURE: " + WATERFLOW_MEASURE " ml");
}

void FLOW() {
  COUNT++;
}
