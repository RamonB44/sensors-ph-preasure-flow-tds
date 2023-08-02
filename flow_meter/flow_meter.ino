
int FLOW_PIN = 2;
float FLOW_RATE;
volatile float COUNT;
float FLOW_CONSTANTE = 4.00;  // 1 L / 250 pulsos segun especificacion de fabricante * 1000 mL | Este valor es solo proporcionado por el fabricante pero puede variar
float WATER_FLOW_MEASURE;

void setup() {
  Serial.begin(9600);
  pinMode(FLOW_PIN, INPUT);
  attachInterrupt(0, FLOW, RISING);
}

void loop() {
  COUNT = 0;
  interrupts();
  delay(1000);
  noInterrupts();

  FLOW_RATE = (COUNT * FLOW_CONSTANTE);
  WATER_FLOW_MEASURE = FLOW_RATE;
  FLOW_RATE = FLOW_RATE * 60;
  FLOW_RATE = FLOW_RATE / 1000;
  Serial.println(COUNT);
  Serial.print("FLOWRATE: ");Serial.print(FLOW_RATE, 1);Serial.println(' l/m');
  Serial.print("WATERFLOW: ");Serial.print(WATER_FLOW_MEASURE, 1);Serial.println(' ml/pulso');
}

void FLOW() {
  COUNT++;
}
