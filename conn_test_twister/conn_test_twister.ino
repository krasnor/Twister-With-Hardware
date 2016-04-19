float Quellspannung = 5.0;
int R1 = 2700.0; //Wert des bekannten Widerstands


// MAP Field -> AnalogPin
int Field00 = 0;
int Field01 = 1;
int Field02 = 2;
int Field03 = 3;
int Field04 = 4;
int Field05 = 5;
int Field06 = 6;
int Field07 = 7;
int Field08 = 8;
int Field09 = 9;
int Field10 = 10;
int Field11 = 11;
int Field12 = 12;
int Field13 = 13;
int Field14 = 14;
int Field15 = 15;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
  Serial.println("Twister Game - Field Conectivity test");
}

void loop() {
  // put your main code here, to run repeatedly:

Serial.println("####################################  START OF CONNECTIVITY TEST ########################");
doConnectivityTest(false);
Serial.println("####################################  END OF CONNECTIVITY TEST   ########################");


/**
Serial.print("15: _");
Serial.println(measureResistance(Field15,R1),2);
delay(2000);
doMeasureAllFields();
*/
delay(2000);

}

void doConnectivityTest(boolean fast){
  doConnectivityTest(Field00 ,R1, fast);
  doConnectivityTest(Field01 ,R1, fast);
  doConnectivityTest(Field02 ,R1, fast);
  doConnectivityTest(Field03 ,R1, fast);
  
  doConnectivityTest(Field04 ,R1, fast);
  doConnectivityTest(Field05 ,R1, fast);
  doConnectivityTest(Field06 ,R1, fast);
  doConnectivityTest(Field07 ,R1, fast);
  
  doConnectivityTest(Field08 ,R1, fast);
  doConnectivityTest(Field09 ,R1, fast);
  doConnectivityTest(Field10 ,R1, fast);
  doConnectivityTest(Field11 ,R1, fast);

  doConnectivityTest(Field12 ,R1, fast);
  doConnectivityTest(Field13 ,R1, fast);
  doConnectivityTest(Field14 ,R1, fast);
  doConnectivityTest(Field15 ,R1, fast);
}
void doConnectivityTest(int field, int resistance, boolean fast){
 int currField = field;
 
boolean doStage1 = true;
boolean doStage2 = true;
Serial.print("Field ");
Serial.print(currField);
Serial.print(": Bitte auflegen -470ohm - ");
while(doStage1){ // stage 1 - 470ohm resistor
  float res = measureResistance(currField,resistance);
  if(res > 440 && res < 525){
    Serial.print(res,2);
    Serial.print("OK");
    doStage1 = false;
  }
  delay(1000);
}
if(fast){
  Serial.println(" - OKOK");
  return;
}
Serial.print(" 1800ohm - ");
while(doStage2){ // stage 2 - 1800ohm resistor
   float res = measureResistance(currField,resistance);
  if(res > 1650 && res < 2000){
    Serial.print(res,2);
    Serial.print("OK");
    doStage2 = false;
  }
  delay(1000);
}
Serial.println(" - OKOK");
}

void doMeasureAllFields(){
  Serial.println("#printing measured vals of fields");
  measureResistanceLog(Field00,R1);
  measureResistanceLog(Field01,R1);
  measureResistanceLog(Field02, R1);
  measureResistanceLog(Field03,R1);
  
  measureResistanceLog(Field04,R1);
  measureResistanceLog(Field05, R1);
  measureResistanceLog(Field06,R1);
  measureResistanceLog(Field07,R1);
  
  measureResistanceLog(Field08, R1);  
  measureResistanceLog(Field09, R1);
  measureResistanceLog(Field10,R1);
  measureResistanceLog(Field11,R1);
  
  measureResistanceLog(Field12, R1);
  measureResistanceLog(Field13,R1);
  measureResistanceLog(Field14,R1);
  measureResistanceLog(Field15, R1);
  Serial.println("#printing measured vals of fields");

}
void measureResistanceLog(int pin, int rs1) {
  long Messwert;
  float SpannungR2; //Spannung über dem zu messenden Widerstand
  float Widerstand;

  //5 Messungen machen und Mittelwert bilden
  Messwert = 0;
  for (int i = 0; i < 5; i++) {
    Messwert += analogRead(pin);
  }
  Messwert = trunc(Messwert / 5);

  //Spannung berechnen
  SpannungR2 = (Quellspannung / 1023.0) * Messwert;
  //Serial.print(pin, 10);
  //Serial.print(":Spannung ueber R2 betraegt ");
  //Serial.print(SpannungR2, 2);
  //Serial.println(" Volt!");
  //Berechnung: (R2 = rs1 * (U2/U1))
  Serial.print(pin, 10);
  Widerstand = rs1 * (SpannungR2 / (Quellspannung - SpannungR2));
  Serial.print("Der Widerstand hat ");
  Serial.print(Widerstand, 2);
  Serial.println(" Ohm.");
  //Serial.println();
}

float measureResistance(int pin, int rs1) {
  long Messwert;
  float SpannungR2; //Spannung über dem zu messenden Widerstand
  float Widerstand;

  //5 Messungen machen und Mittelwert bilden
  Messwert = 0;
  for (int i = 0; i < 5; i++) {
    Messwert += analogRead(pin);
  }
  Messwert = trunc(Messwert / 5);

  //Spannung berechnen
  SpannungR2 = (Quellspannung / 1023.0) * Messwert;
  //Berechnung: (R2 = rs1 * (U2/U1))
  Widerstand = rs1 * (SpannungR2 / (Quellspannung - SpannungR2));
  return Widerstand;
}
