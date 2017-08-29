#include <TinyGPS.h>

String sendData;
long lat,lon; // create variable for latitude and longitude object
TinyGPS gps; // create gps object
 
void setup() {
  Serial.begin(19200); // connect serial
  Serial1.begin(4800); // connect gps sensor
  Serial2.begin(9600);
}
 
void loop() {
  if(Serial1.available()){ // check for gps data
   if(gps.encode(Serial1.read())){ // encode gps data
    gps.get_position(&lat,&lon); // get latitude and longitude
    // display position
    sendData = "#," + String(lat) + "," + String(lon) + ",#$\n";
    Serial.print(sendData);
    Serial2.print(sendData);
   }
  }
}