/******************************************************************************
  Example4-SerialReadWithPacketInfo
  QwiicRF Library Packet Reading with Metadata Example

  Nick Poole @ SparkFun Electronics
  June 21, 2018
  https://github.com/sparkfun/SparkFun_QwiicRF_Library

  This example checks once per second to see if the attached QwiicRF has received
  any payload. If it has, the payload is written to the Serial terminal along
  with the following packet metadata:
  - Sequential Packet ID
  - Packet Origin
  - Packet Destination
  - Packet RSSI
  - Packet SNR

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
  Radio.begin(0x36);

}

void loop() {

  while ( Radio.hasPayload() == false ) {
    delay(1000);
  }

  Serial.println("Received Packet!");
  Serial.println("--------------------------");
  Serial.print("ID: ");
  Serial.println(Radio.getPacketID());

  Serial.print("SENT FROM: ");
  Serial.println(Radio.getPacketOrigin());

  Serial.print("SENT TO: ");
  Serial.println(Radio.getPacketDestination());

  Serial.print("RSSI: ");
  Serial.println(Radio.getPacketRSSI());

  Serial.print("SNR: ");
  Serial.println(Radio.getPacketSNR());

  Serial.print("PAYLOAD: ");
  Serial.println(Radio.read());

  Serial.println();
  Serial.println();

}
