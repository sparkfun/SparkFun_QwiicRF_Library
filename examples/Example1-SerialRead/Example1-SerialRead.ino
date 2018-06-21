/******************************************************************************
  Example1-SerialRead
  QwiicRF Library Serial Read Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example checks once per second to see if the attached QwiicRF has received
  any payload. If it has, the payload is written to the Serial terminal.

  Hardware Resources:
  - SparkFun BlackBoard (https://www.sparkfun.com/products/14669)
  - QwiicRF Board (https://www.sparkfun.com/products/14788)
  - Qwiic Cable (https://www.sparkfun.com/products/14426)

  Development environment specifics:
  Arduino 1.8.5
  QwiicRF Board
  SparkFun BlackBoard (any 'duino should do)
******************************************************************************/

#include <QwiicRF.h>

String incoming = "";

QwiicRF Radio;

void setup() {

  Serial.begin(9600);
  Radio.begin(0x35); //Default I2C Address for QwiicRF

}

void loop() {

  while ( Radio.hasPayload() == false ) {
    delay(1000);
  }

  Serial.println(Radio.read());

}
