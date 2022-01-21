int sensor = A0;
int lvl;
char res[64];

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("Autoplant");
}

void loop() {
  lvl = analogRead(sensor);
  lvl = map(lvl, 550, 0, 0, 100);
  sprintf(res, "Moisture Level: %3d% \r\n", lvl);
  Serial.print(res);
  delay(1000);
}
