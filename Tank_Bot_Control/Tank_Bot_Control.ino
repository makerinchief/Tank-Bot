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
  1 x Nano Breakout Board with NRF Headers
  1 x NRF24l01 2.4GHz RF Transceiver
  1 x 6 volt NiMh Battery
  1 x 5 AA Battery Holder
  5 x 1.2 Volt NiMh AA Batteries
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

struct RECEIVE_DATA {

  int16_t left_xAxis;
  int16_t left_yAxis;
  int16_t left_button;

  int16_t right_xAxis;
  int16_t right_yAxis;
  int16_t right_button;

};

RECEIVE_DATA dataGot;

const int16_t dataCount = 6;

int16_t dataThreshold = 55;
int16_t dataMax = 255;

unsigned long tankCurrent;
unsigned long tankPrevious;
unsigned long tankReadPrevious;
const long tankInterval = 100;

int greenLed = 3;
int redLed = 4;


void setup() {

  Serial.begin(9600);

  tankRadio.begin();

  tankRadio.openReadingPipe(0, tankBotAddress); // 00001
  tankRadio.setPALevel(RF24_PA_MIN);
  tankRadio.startListening();

  SETUP_MOTORS();

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

}

void loop() {

  //testTank(100);
  //testRadio_Recieve();
  getController();

}

void testRadio_Recieve() {

  if (tankRadio.available()) {
    char receiveText[32] = "";
    tankRadio.read(&receiveText, sizeof(receiveText));
    Serial.print("TankBot Reads: ");
    Serial.println(receiveText);
  }

}

void getController() {

  if (tankRadio.available()) {


    tankRadio.read(&dataGot, sizeof(dataGot));

    //print raw
    //printData();

    //remap
    dataGot.left_yAxis = map(dataGot.left_yAxis, 0, 1023, -255, 255);
    dataGot.right_yAxis = map(dataGot.right_yAxis, 0, 1023, -255, 255);

    //print adjusted
    //printData();

    //Control Left Side
    if (dataGot.left_yAxis > dataThreshold) {
      left_Forward(dataGot.left_yAxis/2);
    } else if (dataGot.left_yAxis < -dataThreshold) {
      left_Backward(abs(dataGot.left_yAxis/2));
    } else {
      left_Stop();
    }

    //Control Right Side

    if (dataGot.right_yAxis > dataThreshold) {
      right_Forward(dataGot.right_yAxis/2);
    } else if (dataGot.right_yAxis < -dataThreshold) {
      right_Backward(abs(dataGot.right_yAxis/2));
    } else {
      right_Stop();
    }

    //Turn on LEDs

    if (dataGot.left_button == 1) {
      digitalWrite(greenLed, HIGH);
    } else {
      digitalWrite(greenLed, LOW);
    }

    if (dataGot.right_button == 1) {
      digitalWrite(redLed, HIGH);
    } else {
      digitalWrite(redLed, LOW);
    }

  }

}



void printData() {

  Serial.print(dataGot.left_xAxis);
  Serial.print("  ");
  Serial.print(dataGot.left_yAxis);
  Serial.print("  ");
  Serial.print(dataGot.left_button);
  Serial.print("  ");

  Serial.print(dataGot.right_xAxis);
  Serial.print("  ");
  Serial.print(dataGot.right_yAxis);
  Serial.print("  ");
  Serial.print(dataGot.right_button);
  Serial.println();

}
