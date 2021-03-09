

//Left Side
int leftPwm = 5;
int leftA = 4;
int leftB = 3;

int rightPwm = 6;
int rightA = 7;
int rightB = 8;

void SetupMotors() {

  pinMode(leftPwm, OUTPUT);
  pinMode(leftA, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(rightPwm, OUTPUT);
  pinMode(rightA, OUTPUT);
  pinMode(rightB, OUTPUT);

}

void TestTank(int motorSpeed) {

  Serial.println("FORWARD");
  LeftForward(motorSpeed);
  RightForward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("BACKWARD");
  LeftBackward(motorSpeed);
  RightBackward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("RIGHT");
  LeftForward(motorSpeed);
  RightBackward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

  Serial.println("LEFT");
  LeftBackward(motorSpeed);
  RightForward(motorSpeed);
  delay(2000);
  LeftStop();
  RightStop();
  delay(2000);

}


//Never have a motor's A and B pins on at the same time!
void LeftForward(int motorSpeed) {
  
  analogWrite(leftPwm, motorSpeed);
  digitalWrite(leftA, LOW);
  digitalWrite(leftB, HIGH);

}

void LeftBackward(int motorSpeed) {

  analogWrite(leftPwm, motorSpeed);
  digitalWrite(leftA, HIGH);
  digitalWrite(leftB, LOW);

}

void LeftStop() {

  analogWrite(leftPwm, 0);
  digitalWrite(leftA, LOW);
  digitalWrite(leftB, LOW);

}

void RightForward(int motorSpeed) {

  analogWrite(rightPwm, motorSpeed);
  digitalWrite(rightA, LOW);
  digitalWrite(rightB, HIGH);

}

void RightBackward(int motorSpeed) {

  analogWrite(rightPwm, motorSpeed);
  digitalWrite(rightA, HIGH);
  digitalWrite(rightB, LOW);

}
void RightStop() {

  analogWrite(rightPwm, 0);
  digitalWrite(rightA, LOW);
  digitalWrite(rightB, LOW);
}
