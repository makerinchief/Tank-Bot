/*

  Tank Bot
  Justin C Kirk 2020

  justin.c.kirk@gmail.com
  https://www.makerinchief.com/12
  https://github.com/makerinchief/TankBot

  Tank Bot Parts:


  1 x Arduino Nano
  1 x Nano Breakout Board with headers for NRF2401 Module
  1 x NRF24l01 2.4GHz RF Transceiver
  4 x DC TT Hobby Motors Motors + Tires
  1 x L298N DC Motor Drivers

  1 x 5 AA Battery Holder
  5 x 1.2 Volt NiMh AA Batteries
  1 x Breadboard Half Size

*/

//NRFLite is used to make communication easy
//https://github.com/dparson55/NRFLite
#include <SPI.h>
#include <NRFLite.h>

const static uint8_t TANK_BOT_ID = 0;

const static uint8_t RADIO_CE = 10;
const static uint8_t RADIO_CSN = 9;

struct ControllerPacket {

  int16_t left_xAxis;
  int16_t left_yAxis;
  int16_t left_button;

  int16_t right_xAxis;
  int16_t right_yAxis;
  int16_t right_button;

};

NRFLite tankRadio;
ControllerPacket controllerData;

//Used to create dead zones for controller joysticks
int16_t axisThreshold = 55;

//Use a timer instead of delay()
unsigned long tankCurrent;
unsigned long tankPrevious;
long tankInterval = 10;

//Unused GPIO Pins: 0, 1, 2, A5, A6, A7
int greenLed = 3;
int redLed = 4;


void setup() {

  Serial.begin(115200);

  tankRadio.init(TANK_BOT_ID, RADIO_CE, RADIO_CSN);

  SetupMotors();

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

}

void loop() {

  //TestTank(150);

//  tankCurrent = millis();
//
//  if (tankCurrent - tankPrevious > tankInterval) {
//    //TestController();
//    GetController();
//    //PrintData();
//    tankPrevious = tankCurrent;
//  }



  while (tankRadio.hasData() ) {
    //TestController();
    GetController();
    //PrintData();
  }

}


void GetController() {

  tankRadio.readData(&controllerData);
  //Serial.println(tankRadio.readData(&controllerData))
  //print raw
  //PrintData();

  //Remap values to send to motor driver
  controllerData.left_yAxis = map(controllerData.left_yAxis, 0, 1023, 255, -255);
  controllerData.right_yAxis = map(controllerData.right_yAxis, 0, 1023, 255, -255);

  Serial.print(controllerData.left_yAxis);
  Serial.print("  :  ");
  Serial.println(controllerData.right_yAxis);

  //print adjusted
  //PrintData();

  //Control Left Side
  if (controllerData.left_yAxis > axisThreshold) {
    LeftForward(controllerData.left_yAxis);
  } else if (controllerData.left_yAxis < -axisThreshold) {
    LeftBackward(abs(controllerData.left_yAxis));
  } else {
    LeftStop();
  }

  //Control Right Side
  if (controllerData.right_yAxis > axisThreshold) {
    RightForward(controllerData.right_yAxis);
  } else if (controllerData.right_yAxis < -axisThreshold) {
    RightBackward(abs(controllerData.right_yAxis));
  } else {
    RightStop();
  }

  //  //Turn on LEDs
  //  if (controllerData.left_button == 1) {
  //    digitalWrite(greenLed, HIGH);
  //  } else {
  //    digitalWrite(greenLed, LOW);
  //  }
  //
  //  if (controllerData.right_button == 1) {
  //    digitalWrite(redLed, HIGH);
  //  } else {
  //    digitalWrite(redLed, LOW);
  //  }

}

void TestController() {

  tankRadio.readData(&controllerData);

  //PrintData();

}

void PrintData() {

  Serial.print(controllerData.left_xAxis);
  Serial.print("  :  ");
  Serial.print(controllerData.left_yAxis);
  Serial.print("  :  ");
  Serial.print(controllerData.left_button);
  Serial.print("  :  ");

  Serial.print(controllerData.right_xAxis);
  Serial.print("  :  ");
  Serial.print(controllerData.right_yAxis);
  Serial.print("  :  ");
  Serial.print(controllerData.right_button);
  Serial.println();

}
