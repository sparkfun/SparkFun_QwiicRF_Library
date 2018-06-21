/******************************************************************************
  Example6-PairingExample
  QwiicRF Library I2C Pairing Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example demonstrates and explains the process of pairing two QwiicRF Boards.
  In order for this example to work, you must connect two QwiicRF Boards to the
  same Qwiic Bus.

  Hardware Resources:
  - SparkFun BlackBoard (https://www.sparkfun.com/products/14669)
  - Two QwiicRF Boards (https://www.sparkfun.com/products/14788)
  - Two Qwiic Cables (https://www.sparkfun.com/products/14426)

  Development environment specifics:
  Arduino 1.8.5
  Two QwiicRF Boards
  SparkFun BlackBoard (any 'duino should do)
******************************************************************************/

#include <QwiicRF.h>
#include <Wire.h>

// This command is not exposed to the library, it is intended mainly
// for QwiicRF Boards to identify eachother on the bus. We'll define
// it here to do our bus scanning trick.
#define COMMAND_GET_SKU 0x15

// Multiple instances of the QwiicRF class are no problem!
QwiicRF Radio1;
QwiicRF Radio2;

// Instead of explicitly defining our I2C Addresses, we'll scan the bus for them
byte i2c_addr[2];

void setup() {

  Wire.begin();
  Serial.begin(9600);

}

void loop() {

  Serial.println(F("QwiicRF Pairing Demonstration"));
  Serial.println();
  Serial.println(F("Connect two QwiicRF boards to the Qwiic bus and press any key"));
  Serial.println(F("Make sure that the two radios have different I2C addresses"));
  Serial.println(F("You can use the solder jumper on the board to change its address"));
  Serial.println();

  pause();

  scanForRadios();

}

void pause() {
  while (!Serial.available()) {}
  delay(100);
  while (Serial.available()) {
    Serial.read();
  };
}

void scanForRadios() {

  int addr_cnt = 0;
  String incoming = "";

  for ( byte addr = 0x08 ; addr < 0x7F ; addr++ ) {

    Wire.beginTransmission(addr);
    Wire.write(COMMAND_GET_SKU);
    Wire.endTransmission(false);
    Wire.requestFrom(addr, 5);

    while ( Wire.available() ) {
      incoming += char( Wire.read() );
    }


    if ( incoming == "14788" ) {
      i2c_addr[addr_cnt] = addr;
      incoming = "";
      addr_cnt++;
    } else {
      incoming = "";
    }
  }


  Wire.end();
  Radio1.begin(i2c_addr[0]);
  Radio2.begin(i2c_addr[1]);

  if ( Radio1.isReady() && Radio2.isReady() ) {

    Serial.print(F("Found two radios at 0x"));
    Serial.print(i2c_addr[0], HEX);
    Serial.print(F(" and 0x"));
    Serial.println(i2c_addr[1], HEX);
  } else {
    Serial.println(F("Unable to connect to two radios! Check your connections and try again!"));
    return 0;
  }

  while (1) {

    showStats();
    Serial.println();
    Serial.println(F("Press and hold the Pairing button on either of the radios"));
    Serial.println(F("The blue pairing light should turn on and then off again."));
    Serial.println(F("When the light turns off, press any key to see how the"));
    Serial.println(F("radio settings changed. You can pair two radios any time that"));
    Serial.println(F("they're sharing a Qwiic bus. But be sure that the bus isn't"));
    Serial.println(F("busy because that may cause contention."));
    pause();

  }
}

void showStats() {

  Serial.println();
  Serial.print(F("Radio 1 | "));
  Serial.print(F("I2C Address 0x"));
  Serial.print(i2c_addr[0], HEX);
  Serial.print(F(" | RF Address "));
  Serial.print(Radio1.getRFAddress());
  Serial.print(F(" | Paired Address "));
  Serial.print(Radio1.getPairedAddress());
  Serial.print(F(" | Sync Word "));
  Serial.println(Radio1.getSyncWord());

  Serial.println();
  Serial.print(F("Radio 2 | "));
  Serial.print(F("I2C Address 0x"));
  Serial.print(i2c_addr[1], HEX);
  Serial.print(F(" | RF Address "));
  Serial.print(Radio2.getRFAddress());
  Serial.print(F(" | Paired Address "));
  Serial.print(Radio2.getPairedAddress());
  Serial.print(F(" | Sync Word "));
  Serial.println(Radio2.getSyncWord());

}

