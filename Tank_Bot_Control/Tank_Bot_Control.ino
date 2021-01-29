/*

  Tank Bot
  Justin C Kirk 2020

  justin.c.kirk@gmail.com
  https://www.makerinchief.com/
  https://github.com/makerinchief/TankBot

  Tank Bot Parts:

  4 x 6 Volt DC Hobby Motors Motors + Tires
  2 x L9110S DC Motor Drivers
  1 x Arduino Nano
  1 x Nano Breakout Board with headers for NRF2401 Module
  1 x NRF24l01 2.4GHz RF Transceiver
  2 x 5 AA Battery Holder
  10 x 1.2 Volt NiMh AA Batteries
  1 x Breadboard Half Size

    The motor driver uses two GPIO pins to control each channel.  These can
  be driven using PWM.  Using the SoftPWM library, non hardware PWM pins can
  be used as a software PWM pin.

*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 tankRadio(10, 9); // CE, CSN
const byte tankBotAddress[6] = "00001";

struct ControllerData {

  int16_t left_xAxis;
  int16_t left_yAxis;
  int16_t left_button;

  int16_t right_xAxis;
  int16_t right_yAxis;
  int16_t right_button;

};

ControllerData controller;

int16_t axisThreshold = 55;
int16_t axisMax = 255;

unsigned long tankCurrent;
unsigned long tankPrevious;
long tankInterval = 10;



//Unused GPIO Pins:    0,1,2,3,4,  A5, A6, A7
int greenLed = 3;
int redLed = 4;


void setup() {

  Serial.begin(9600);

  tankRadio.begin();
  tankRadio.openReadingPipe(0, tankBotAddress); // 00001
  tankRadio.setPALevel(RF24_PA_MIN);
  tankRadio.startListening();

  SetupMotors();

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

}

void loop() {

  //TestTank(100);
  //TestRadioTest();
  GetController();

}

void TestRadioTest() {

  if (tankRadio.available()) {
    char receiveText[32] = "";
    tankRadio.read(&receiveText, sizeof(receiveText));
    Serial.print("TankBot Got: ");
    Serial.println(receiveText);
  }

}

void GetController() {

  tankCurrent = millis();

  if (tankCurrent - tankPrevious > tankInterval) {

    if (tankRadio.available()) {

      char receiveText[32] = "";
      tankRadio.read(&controller, sizeof(ControllerData));

      //print raw
      //PrintControllerData();

      //Remap values to send to motor driver
      controller.left_yAxis = map(controller.left_yAxis, 0, 1023, -255, 255);
      controller.right_yAxis = map(controller.right_yAxis, 0, 1023, -255, 255);

      //print adjusted
      //PrintControllerData();

      //Control Left Side
      if (controller.left_yAxis > dataThreshold) {
        LeftForward(controller.left_yAxis / 2);
      } else if (controller.left_yAxis < -dataThreshold) {
        LeftBackward(abs(controller.left_yAxis / 2));
      } else {
        LeftStop();
      }

      //Control Right Side
      if (controller.right_yAxis > dataThreshold) {
        RightForward(controller.right_yAxis / 2);
      } else if (controller.right_yAxis < -dataThreshold) {
        RightBackward(abs(controller.right_yAxis / 2));
      } else {
        RightStop();
      }


      //Turn on LEDs
      if (controller.left_button == 1) {
        digitalWrite(greenLed, HIGH);
      } else {
        digitalWrite(greenLed, LOW);
      }

      if (controller.right_button == 1) {
        digitalWrite(redLed, HIGH);
      } else {
        digitalWrite(redLed, LOW);
      }

    }

    tankPrevious = tankCurrent;
  }

}



void PrintControllerData() {

  Serial.print(controller.left_xAxis);
  Serial.print("  ");
  Serial.print(controller.left_yAxis);
  Serial.print("  ");
  Serial.print(controller.left_button);
  Serial.print("  ");

  Serial.print(controller.right_xAxis);
  Serial.print("  ");
  Serial.print(controller.right_yAxis);
  Serial.print("  ");
  Serial.print(controller.right_button);
  Serial.println();

}
