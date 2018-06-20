#include <QwiicRF.h>

QwiicRF Radio;
String message = "Hello";

void setup() {

  Radio.begin(0x35);

  Radio.setReliableSendTimeout(5);
  
}

void loop() {

  Radio.sendReliable(0xFF, message);

  while(Radio.waitingForAck()){
    delay(1000);
  }

}
