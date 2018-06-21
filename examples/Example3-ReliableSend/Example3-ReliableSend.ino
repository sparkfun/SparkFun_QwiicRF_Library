/******************************************************************************
  Example3-ReliableSend
  QwiicRF Library Reliable Packet Sending Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example transmits the contents of the message String to the broadcast
  channel (0xFF) and waits for an Ack before attempting to send a new packet.

  Reliable send using the .sendReliable() function provides confirmation of delivery
  by requesting an acknowldgement from the recipient. The recipient calculates a
  simple checksum from the payload and returns it to the sender. The sender will
  repeat transmission of the same packet once per second until it detects an ack.
  During this time, system status bit 2 (Waiting on Reliable Ack) will be set and
  system status bit 0 (Ready) will be cleared.
  If the sender does not receive a valid delivery receipt before the reliable send
  timeout, the radio will stop repeating and flag the last reliable send as failed
  by setting system status bit 3 (Previous Reliable Send Timed Out).

  The function will return false if the radio is busy.

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

  Radio.begin(0x35); // Default I2C Address for the QwiicRF

  Radio.setReliableSendTimeout(5); // Change the reliable send timeout to 5 seconds

}

void loop() {

  Radio.sendReliable(0xFF, message);

  while (Radio.waitingForAck()) {
    delay(1000);
  }

}
