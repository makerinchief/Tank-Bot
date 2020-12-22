//SoftPWM Library by Brett Hagman
//  https://github.com/bhagman/SoftPWM

#include <SoftPWM.h>

//Left Side
int motor1_Apin = 5;
int motor1_Bpin = 6;
int motor2_Apin = 7;
int motor2_Bpin = 8;

//Right Side
int motor3_Apin = 14;
int motor3_Bpin = 15;
int motor4_Apin = 16;
int motor4_Bpin = 17;

void SETUP_MOTORS() {

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

void testTank(int _speed) {

  Serial.println("FORWARD");
  left_Forward(_speed);
  right_Forward(_speed);
  delay(2000);
  left_Stop();
  right_Stop();
  delay(2000);

  Serial.println("BACKWARD");
  left_Backward(_speed);
  right_Backward(_speed);
  delay(2000);
  left_Stop();
  right_Stop();
  delay(2000);

  Serial.println("RIGHT");
  left_Forward(_speed);
  right_Backward(_speed);
  delay(2000);
  left_Stop();
  right_Stop();
  delay(2000);

  Serial.println("LEFT");
  left_Backward(_speed);
  right_Forward(_speed);
  delay(2000);
  left_Stop();
  right_Stop();
  delay(2000);
  
}



void left_Forward(int _speed) {

  //Left Side
  SoftPWMSet(motor1_Apin, _speed);
  SoftPWMSet(motor1_Bpin, 0);
  SoftPWMSet(motor2_Apin, _speed);
  SoftPWMSet(motor2_Bpin, 0);

}

void left_Backward(int _speed) {

  //Left Side
  SoftPWMSet(motor1_Apin, 0);
  SoftPWMSet(motor1_Bpin, _speed);
  SoftPWMSet(motor2_Apin, 0);
  SoftPWMSet(motor2_Bpin, _speed);

}

void left_Stop() {

  //Left Side
  SoftPWMSet(motor1_Apin, 0);
  SoftPWMSet(motor1_Bpin, 0);
  SoftPWMSet(motor2_Apin, 0);
  SoftPWMSet(motor2_Bpin, 0);

}

void right_Forward(int _speed) {

  //Right Side
  SoftPWMSet(motor3_Apin, _speed);
  SoftPWMSet(motor3_Bpin, 0);
  SoftPWMSet(motor4_Apin, _speed);
  SoftPWMSet(motor4_Bpin, 0);

}

void right_Backward(int _speed) {

  //Right Side
  SoftPWMSet(motor3_Apin, 0);
  SoftPWMSet(motor3_Bpin, _speed);
  SoftPWMSet(motor4_Apin, 0);
  SoftPWMSet(motor4_Bpin, _speed);

}
void right_Stop() {

  //Right Side
  SoftPWMSet(motor3_Apin, 0);
  SoftPWMSet(motor3_Bpin, 0);
  SoftPWMSet(motor4_Apin, 0);
  SoftPWMSet(motor4_Bpin, 0);

}
