#include <QwiicRF.h>

String incoming = "";

QwiicRF Radio;

void setup() {

  Serial.begin(9600);
  Radio.begin(0x35);
  
}

void loop() {

  while( Radio.hasPayload() == false ) {
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
