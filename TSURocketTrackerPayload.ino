#include <string.h>
#include <ctype.h>

void setup() {
  Serial.begin(11200);
  Serial1.begin(4800);
  Serial2.begin(9600);
}

void loop(){
  if(Serial1.available()){
    Serial.write(Serial1.read());
  }
}