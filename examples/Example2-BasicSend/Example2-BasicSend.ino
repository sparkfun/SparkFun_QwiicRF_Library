/******************************************************************************
  Example2-BasicSend
  QwiicRF Library Basic Packet Sending Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example transmits the contents of the message String to the broadcast
  channel (0xFF) once per second.

  Basic send using the .send() function provides no confirmation of delivery.
  The function will return false if the radio is busy.

  The maximum payload size is limited by the size of the I2C buffer of the
  QwiicRF (32 bytes)

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

QwiicRF Radio;
String message = "Hello";

void setup() {

  Radio.begin(0x35); // Default I2C Address of the QwiicRF

}

void loop() {

  Radio.send(0xFF, message);
  delay(1000);

}
