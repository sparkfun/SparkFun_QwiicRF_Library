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

  Serial.println(Radio.read());

}
