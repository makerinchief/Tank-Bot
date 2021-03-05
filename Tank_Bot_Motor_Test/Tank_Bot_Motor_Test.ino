

int pinA = 5;
int pinB = 6;




void setup() {
  Serial.begin(9600);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {


  Serial.println("Forward");
  analogWrite(pinA, 150);
  digitalWrite(pinB, HIGH);
  delay(2000);

  Serial.println("Stop");
  analogWrite(pinA, 0);
  digitalWrite(pinB, LOW);
  delay(2000);

  Serial.println("Backward");
  analogWrite(pinA, 150);
  digitalWrite(pinB, LOW);
  delay(2000);

  Serial.println("Stop");
  analogWrite(pinA, 0);
  digitalWrite(pinB, LOW);
  delay(2000);


}
