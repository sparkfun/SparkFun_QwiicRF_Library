#include <QwiicRF.h>

String incoming = "";

QwiicRF Radio;

void setup() {

  Serial.begin(9600);
  Radio.begin(0x35);
  
}

void loop() {

  Serial.print("Sync Word: ");
  Serial.println(Radio.getSyncWord());

  Serial.print("RF Address: ");
  Serial.println(Radio.getRFAddress());

  Serial.print("Paired to Address: ");
  Serial.println(Radio.getPairedAddress());

  Serial.println();
  Serial.println();

}
