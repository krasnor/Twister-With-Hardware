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

// ### player
// values of last limb scan 99 == not found on field
int Pos_P1_L_Hand = 99;
int Pos_P1_R_Hand = 99;
int Pos_P1_L_Foot = 99;
int Pos_P1_R_Foot = 99;

int Pos_P2_L_Hand = 99;
int Pos_P2_R_Hand = 99;
int Pos_P2_L_Foot = 99;
int Pos_P2_R_Foot = 99;

void setup() {
  Serial.begin(9600);
  Serial.println("Test Recognize Limbs/player pads");
}

void loop() {
  // put your main code here, to run repeatedly:
  scanFullFieldForLimbs(R1);
  printLimbScanValues();
  delay(1500);
}

// ! this method will overwrite any already found limbs on an other field
void recognizeLimb(int field, int rs1) {
  float res = measureResistance(field, rs1);


  // ! do not set a limb to not found as it will overwrite found limbs on other fields!
  //

  //---400
  // 470    s1 left   hand
  if (res > 400 && res <= 570) {
    Serial.print("s1 lh on ");
    Serial.println( field);
    Pos_P1_L_Hand = field;
  }
  //---570
  // 680    s1 right  hand
  if (res > 570 && res <= 780) {
    Serial.print("s1 rh on ");
    Serial.println( field);
    Pos_P1_R_Hand = field;
  }
  //---780
  // 820    s2 left   hand
  if (res > 720 && res <= 920) {
    Serial.print("s2 lh on ");
    Serial.println( field);
    Pos_P2_L_Hand = field;
  }
  //---920
  // 1k     s2 right  hand
  if (res > 920 && res <= 1100) {
    Serial.print("s2 rh on ");
    Serial.println( field);
    Pos_P2_R_Hand = field;
  }
  //---1,1k
  // 1,2k   s1 left   foot
  if (res > 1100 && res <= 1350) {
    Serial.print("s1 lf on ");
    Serial.println( field);
    Pos_P1_L_Foot = field;
  }
  //---1,35k
  // 1,5k   s1 right  foot
  if (res > 1350 && res <= 1650) {
    Serial.print("s1 rf on ");
    Serial.println( field);
    Pos_P1_R_Foot = field;
  }
  //--- 1,65k
  // 1,8k   s2 left   foot
  if (res > 1650 && res <= 2000) {
    Serial.println("s2 lf on ");
    Serial.println( field);
    Pos_P2_L_Foot = field;
  }
  //---2k
  // 2,2k   s2 right  foot
  if (res > 2000 && res <= 2400) {
    Serial.println("s2 rf on ");
    Serial.println( field);
    Pos_P2_R_Foot = field;
  }
  //---2,4k

}

void scanFullFieldForLimbs(int rs1) {
  // reset last scan
  Pos_P1_L_Hand = 99;
  Pos_P1_R_Hand = 99;
  Pos_P1_L_Foot = 99;
  Pos_P1_R_Foot = 99;

  Pos_P2_L_Hand = 99;
  Pos_P2_R_Hand = 99;
  Pos_P2_L_Foot = 99;
  Pos_P2_R_Foot = 99;

  // make new scan
  recognizeLimb(Field00, rs1);
  recognizeLimb(Field01, rs1);
  recognizeLimb(Field02, rs1);
  recognizeLimb(Field03, rs1);

  recognizeLimb(Field04, rs1);
  recognizeLimb(Field05, rs1);
  recognizeLimb(Field06, rs1);
  recognizeLimb(Field07, rs1);

  recognizeLimb(Field08, rs1);
  recognizeLimb(Field09, rs1);
  recognizeLimb(Field10, rs1);
  recognizeLimb(Field11, rs1);

  recognizeLimb(Field12, rs1);
  recognizeLimb(Field13, rs1);
  recognizeLimb(Field14, rs1);
  recognizeLimb(Field15, rs1);

}

void printLimbScanValues() {
  Serial.println("# last LimbScan values");
  Serial.print("Player 1");
  Serial.print(" hand l: ");
  Serial.print(Pos_P1_L_Hand);
  Serial.print(" r: ");
  Serial.print(Pos_P1_R_Hand);
  Serial.print(" foot L: ");
  Serial.print(Pos_P1_L_Foot);
  Serial.print(" R: ");
  Serial.println(Pos_P1_R_Foot);

  Serial.print("Player 2");
  Serial.print(" hand l: ");
  Serial.print(Pos_P2_L_Hand);
  Serial.print(" r: ");
  Serial.print(Pos_P2_R_Hand);
  Serial.print(" foot l: ");
  Serial.print(Pos_P2_L_Foot);
  Serial.print(" r: ");
  Serial.println(Pos_P2_R_Foot);
  Serial.println("#");
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
