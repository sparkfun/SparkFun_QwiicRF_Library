#include <QwiicRF.h>

QwiicRF Radio;
String message = "Hello";

void setup() {

  Radio.begin(0x35);
  
}

void loop() {

  Radio.send(0xFF, message);
  delay(1000);  

}
