/*
  Tank Bot Basic
  Justin C Kirk 2020

  justin.c.kirk@gmail.com
  https://www.makerinchief.com/
  https://github.com/makerinchief/TankBot

  Tank Bot uses:

  4 micro geared dc motors
  2 L9110S DC Motor Drivers
  1 Arduino Nano with Expansion board
  1 NRF24l01 2.4GHz RF Transceiver
  1 Breadboard
  1 6 volt LiPo Battery

  The motor drivers take PWM input but using the SoftPWM library,
  I was able to make use of a combination of analog and digital pins
  to control the motors speed and directions.

  Analog Pins 0 - 3 are used to control the right side motors

  Digital Pins 5 - 8 are used to control the left side motors

  Digital Pins 9 - 13 are used by the RF Transceiver

  While this leaves 5 pins unused, there are ways to make use of a small number of pins to control multiple outputs.

  Analog Pins 4 and 5 can be used for I2C communication to control multiple PWM values using PCA9685 breakbout boards.

  Digital Pins 2, 3 and 4 can be used with shift registers to expand the number of digital outputs.

  The Arduino's 5 Volt output is wired to a rail of the breadboard for use by any additional sensors.

  The motor driver breakout boards get their power directly from the battery.

*/

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

RECEIVE_DATA gotData;

const int dataCount = 6;
int gotDataArray[dataCount] = {};

unsigned long tankCurrent;
unsigned long tankPrevious;
unsigned long tankReadPrevious;
const long tankInterval = 10;

void setup() {

  Serial.begin(9600);

  tankRadio.begin();
  tankRadio.openReadingPipe(0, tankBotAddress); // 00001
  tankRadio.setPALevel(RF24_PA_MIN);
  tankRadio.startListening();

  SETUP_MOTORS();

}

void loop() {

  /*
    Use the testTank() function to test the DC motors.

    Make sure the direction of the motors follow what is
    being printed to the Serial monitor.

    You can adjust the speed as well.
    Use values 0 - 255.
  */

  // testTank(100);

  tankCurrent = millis();

  if (tankCurrent - tankPrevious >= tankInterval) {

    if (tankRadio.available()) {
      tankRadio.read(&gotData, sizeof(RECEIVE_DATA));
      tankReadPrevious = tankCurrent;
    }

    //Is the remote out of range?
    if (tankCurrent - tankReadPrevious > 500) {
      Serial.println("Remote Not Found");
      gotDataArray[0] = 0;
      gotDataArray[1] = 0;
      gotDataArray[2] = 0;
      gotDataArray[3] = 0;
      gotDataArray[4] = 0;
      gotDataArray[5] = 0;
    }

    else {
      
      gotDataArray[0] = gotData.left_xAxis;
      gotDataArray[1] = gotData.left_yAxis;
      gotDataArray[2] = gotData.left_button;
      gotDataArray[3] = gotData.right_xAxis;
      gotDataArray[4] = gotData.right_yAxis;
      gotDataArray[5] = gotData.right_button;

      //Print the raw values coming from the controller.
      printDataArray();

      //Print the values we will use
      //Serial.print(gotDataArray[1]);
      //Serial.print(" : ");
      //Serial.print(gotDataArray[4]);
      //Serial.println();

      //Set the range between -5 and 5 as a dead zone.

      if (gotDataArray[1] > 5) {
        left_Forward(gotDataArray[1]);
      } else if (gotDataArray[1] < -5) {
        left_Backward(abs(gotDataArray[1]));
      } else {
        left_Stop();
      }

      if (gotDataArray[4] > 5) {
        right_Forward(gotDataArray[4]);
      } else if (gotDataArray[4] < -5) {
        right_Backward(abs(gotDataArray[4]));
      } else {
        right_Stop();
      }
      

    }
    tankPrevious = tankCurrent;
  }

}

void printDataArray() {

  for (int i = 0; i < dataCount; i ++)
  {
    Serial.print(gotDataArray[i]);
    if (i == dataCount - 1) {
      Serial.println();
    } else {
      Serial.print("  :  ");
    }
  }

}
