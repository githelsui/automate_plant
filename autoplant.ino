int sensor = A0;
const int threshold = 34;
const int relay = 5;
const int led = 16;
int lvl;
char res[64];

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(led, OUTPUT);
    pinMode(relay, OUTPUT);
    Serial.println("Autoplant");
    digitalWrite(led, LOW);
    delay(1000);
}

void loop() {
  digitalWrite(led, HIGH);
  lvl = analogRead(sensor);
  lvl = map(lvl, 550, 0, 0, 100);
  sprintf(res, "Moisture Level: %3d\r\n", lvl);
  Serial.print(res);

  if(lvl < threshold){
    digitalWrite(relay, HIGH);
    Serial.println("Pump on");
    delay(2000);  
    digitalWrite(relay, LOW);
    digitalWrite(led, LOW);
    digitalWrite(led, HIGH);
    digitalWrite(led, LOW);
    digitalWrite(led, HIGH);
    Serial.println("Pump off");
    delay(2000);
  } else {
    digitalWrite(relay, LOW);
    Serial.println("Pump off");
    delay(1000);
  }
  delay(1000);
  //delay(345600); //check every 4 days
}
