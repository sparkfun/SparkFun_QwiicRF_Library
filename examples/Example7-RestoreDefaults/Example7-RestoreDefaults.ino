/******************************************************************************
  Example7-RestoreDefaults
  QwiicRF Library Default Settings Restore Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example attempts to restore the attached QwiicRF Board to factory default.

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

void setup() {

  Serial.begin(9600);
  Radio.begin(0x35); // Default I2C Address for QwiicRF

}

void loop() {

  Serial.println(F("Press any key to reset the radio to factory defaults"));
  pause();

  Radio.setRFAddress(0xBB);
  Radio.setSyncWord(0x34);
  Radio.setSpreadFactor(0x07);
  Radio.setReliableSendTimeout(0x0A);
  Radio.setTXPower(0x11);
  Radio.setPairedAddress(0xBB);
  Radio.setI2CAddress(0x35);

  Serial.println(F("Default settings written to radio"));

  while (1) {};

}

void pause() {
  while (!Serial.available()) {}
  delay(100);
  while (Serial.available()) {
    Serial.read();
  };
}
