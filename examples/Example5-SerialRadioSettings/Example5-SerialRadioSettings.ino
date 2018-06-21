/******************************************************************************
  Example5-SerialRadioSettings
  QwiicRF Library Radio Settings Manipulation Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example provides a Serial Terminal interface for reading and writing the
  three identifying addresses of a QwiicRF Radio: The Sync Word, RF Address, and
  Paired Address.

  The Sync Word is essentially a network address. Radios with different
  Sync Words will not be able to communicate with eachother.

  The RF Address is a one byte identifier that should be unique
  to each radio in the system.

  The Paired Address is the one byte identifier of another radio
  that this radio is 'paired' to. Paired radios will assume that
  their partner is the destination address of a packet whenever
  a recipient is not specified, i.e. when using the .send() or
  .sendReliable() functions without a recipient address.

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

byte i2c_addr = 0x35; // Default I2C Address for QwiicRF

QwiicRF Radio;

void setup() {

  Serial.begin(9600);
  Radio.begin(i2c_addr);

}

void loop() {

  mainMenu();

}

int mainMenu() {

  Serial.println();
  Serial.println();
  Serial.print(F("The Radio at I2C address 0x"));
  Serial.print(i2c_addr, HEX);
  Serial.println(F(" now has the following settings:"));
  Serial.println();

  Serial.print(F("1) Sync Word: "));
  Serial.println(Radio.getSyncWord());

  Serial.print(F("2) RF Address: "));
  Serial.println(Radio.getRFAddress());

  Serial.print(F("3) Paired to Address: "));
  Serial.println(Radio.getPairedAddress());

  Serial.println();
  Serial.println(F("To change any of this radio's settings, press the corresponding number:"));
  Serial.println();

  switch (prompt().charAt(0)) {

    case '1':
      syncChange();
      break;

    case '2':
      addrChange();
      break;

    case '3':
      pairChange();
      break;

    default:
      Serial.println(F("I'm sorry, I don't understand"));
      break;

  }

}

String prompt() {

  String in = "";
  while (!Serial.available()) {}
  delay(100);
  while (Serial.available() > 0) {
    in += char(Serial.read());
  }
  Serial.println(in);
  return in;

}

void syncChange() {

  Serial.println(F("The Sync Word is essentially a network address. Radios with different"));
  Serial.println(F("Sync Words will not be able to communicate with eachother."));
  Serial.println();
  Serial.print(F("The current Sync Word for the radio at I2C address 0x"));
  Serial.print(i2c_addr, HEX);
  Serial.print(F(" is "));
  Serial.print(Radio.getSyncWord());
  Serial.println();
  Serial.println();
  Serial.println(F("What would you like to change it to? (press x to cancel)"));

  while (1) {

    String input = prompt();

    if (input.charAt(0) == 'x') {
      return 0;
    } else {

      int inputInt = input.toInt();

      if (inputInt == NULL || inputInt > 255 || inputInt < 0) {
        Serial.println(F("You must select a number between 0 and 255"));
      } else {
        Serial.print(F("Changing Sync Word to "));
        Serial.println(input);
        Radio.setSyncWord(inputInt);
        return 1;
      }
    }
  }
}

void addrChange() {

  Serial.println(F("The RF Address is a one byte identifier that should be unique"));
  Serial.println(F("to each radio in the system."));
  Serial.println();
  Serial.print(F("The current RF Address for the radio at I2C address 0x"));
  Serial.print(i2c_addr, HEX);
  Serial.print(F(" is "));
  Serial.print(Radio.getRFAddress());
  Serial.println();
  Serial.println();
  Serial.println(F("What would you like to change it to? (press x to cancel)"));

  while (1) {

    String input = prompt();

    if (input.charAt(0) == 'x') {
      return 0;
    } else {

      int inputInt = input.toInt();

      if (inputInt == NULL || inputInt > 255 || inputInt < 0) {
        Serial.println(F("You must select a number between 0 and 255"));
      } else {
        Serial.print(F("Changing RF Address to "));
        Serial.println(input);
        Radio.setRFAddress(inputInt);
        return 1;
      }
    }
  }
}

void pairChange() {

  Serial.println(F("The Paired Address is the one byte identifier of another radio"));
  Serial.println(F("that this radio is 'paired' to. Paired radios will assume that"));
  Serial.println(F("their partner is the destination address of a packet whenever"));
  Serial.println(F("a recipient is not specified."));
  Serial.println();
  Serial.print(F("The current Paired Address for the radio at I2C address 0x"));
  Serial.print(i2c_addr, HEX);
  Serial.print(F(" is "));
  Serial.print(Radio.getPairedAddress());
  Serial.println();
  Serial.println();
  Serial.println(F("What would you like to change it to? (press x to cancel)"));

  while (1) {

    String input = prompt();

    if (input.charAt(0) == 'x') {
      return 0;
    } else {

      int inputInt = input.toInt();

      if (inputInt == NULL || inputInt > 255 || inputInt < 0) {
        Serial.println(F("You must select a number between 0 and 255"));
      } else {
        Serial.print(F("Changing Paired Address to "));
        Serial.println(input);
        Radio.setPairedAddress(inputInt);
        return 1;
      }
    }
  }
}


