void setup() {
 Serial.begin(9600);
}

void loop() {
  if (Serial.available() >= 27) {
    if (Serial.read() == 0x7E) {
      for (int i = 1; i < 19; i++) {
        byte discardByte = Serial.read();
      }
      int analogMSB1      = Serial.read();
      int analogLSB1      = Serial.read();
      int analogReading1  = analogLSB1 + (analogMSB1 * 256);
      Serial.println(analogReading1);

      int analogMSB2      = Serial.read();
      int analogLSB2      = Serial.read();
      int analogReading2  = analogLSB2 + (analogMSB2 * 256);
      Serial.println(analogReading2);

      int analogMSB3      = Serial.read();
      int analogLSB3      = Serial.read();
      int analogReading3  = analogLSB3 + (analogMSB3 * 256);
      Serial.println(analogReading3);

      int analogMSB4      = Serial.read();
      int analogLSB4      = Serial.read();
      int analogReading4  = analogLSB4 + (analogMSB4 * 256);
      Serial.println(analogReading4);
    }
  }
}
