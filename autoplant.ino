int sensor = A0;
const int threshold = -5; //positive lvls > 0 = wet, negative lvls = dry
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
    digitalWrite(led, HIGH);
    delay(1000);
}

void flash(){
    Serial.println("Watering Plant");
    delay(500);  
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(500); 
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(500);  
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(5000); 
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
    delay(1000);  
    flash();  
    digitalWrite(relay, LOW);
        Serial.println("Pump off");
    delay(1000);
  } else {
    digitalWrite(led, LOW);
    digitalWrite(relay, LOW);
    Serial.println("Pump off");
    delay(1000);
  }
//  delay(1000); //testing
  Serial.println("Will check moisture level again in 3 more days!");
  delay(259200000); //check every 3 days
}
