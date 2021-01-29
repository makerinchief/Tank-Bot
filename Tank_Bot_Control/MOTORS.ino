//SoftPWM Library by Brett Hagman
//  https://github.com/bhagman/SoftPWM

#include <SoftPWM.h>

//Left Side
int motor1_Apin = 5; //Hardware PWM
int motor1_Bpin = 6; //Hardware PWM
int motor2_Apin = 7;
int motor2_Bpin = 8;

//Right Side
int motor3_Apin = 14;  //A0
int motor3_Bpin = 15;  //A1
int motor4_Apin = 16;  //A2
int motor4_Bpin = 17;  //A3

void SetupMotors() {

  SoftPWMBegin();

  SoftPWMSet(motor1_Apin, 0);
  SoftPWMSet(motor1_Bpin, 0);
  SoftPWMSet(motor2_Apin, 0);
  SoftPWMSet(motor2_Bpin, 0);
  SoftPWMSet(motor3_Apin, 0);
  SoftPWMSet(motor3_Bpin, 0);
  SoftPWMSet(motor4_Apin, 0);
  SoftPWMSet(motor4_Bpin, 0);

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

  //Left Side
  SoftPWMSet(motor1_Apin, motorSpeed);
  SoftPWMSet(motor1_Bpin, 0);
  SoftPWMSet(motor2_Apin, motorSpeed);
  SoftPWMSet(motor2_Bpin, 0);

}

void LeftBackward(int motorSpeed) {

  //Left Side
  SoftPWMSet(motor1_Apin, 0);
  SoftPWMSet(motor1_Bpin, motorSpeed);
  SoftPWMSet(motor2_Apin, 0);
  SoftPWMSet(motor2_Bpin, motorSpeed);

}

void LeftStop() {

  //Left Side
  SoftPWMSet(motor1_Apin, 0);
  SoftPWMSet(motor1_Bpin, 0);
  SoftPWMSet(motor2_Apin, 0);
  SoftPWMSet(motor2_Bpin, 0);

}

void RightForward(int motorSpeed) {

  //Right Side
  SoftPWMSet(motor3_Apin, motorSpeed);
  SoftPWMSet(motor3_Bpin, 0);
  SoftPWMSet(motor4_Apin, motorSpeed);
  SoftPWMSet(motor4_Bpin, 0);

}

void RightForward(int motorSpeed) {

  //Right Side
  SoftPWMSet(motor3_Apin, 0);
  SoftPWMSet(motor3_Bpin, motorSpeed);
  SoftPWMSet(motor4_Apin, 0);
  SoftPWMSet(motor4_Bpin, motorSpeed);

}
void RightStop() {

  //Right Side
  SoftPWMSet(motor3_Apin, 0);
  SoftPWMSet(motor3_Bpin, 0);
  SoftPWMSet(motor4_Apin, 0);
  SoftPWMSet(motor4_Bpin, 0);

}
