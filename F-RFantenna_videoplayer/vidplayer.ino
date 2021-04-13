#include <Wire.h>
#include <SPI.h>

int rfreading=0;
int rfPin=A0;
int reading=0;
int rf=0;

void setup() {
  
Serial.begin(9600);

}

void loop() {
rfreading= analogRead(rfPin);
//Serial.print(rfreading);
//map rfreading to voltage classification 2.5, 2, 1.5, 1, 0.7, 0.4, 0.2 V
if (rfreading>512){
rf=7;
}
else if (rfreading>409){
  rf=6;
}
else if (rfreading>307){
  rf=5;
}
else if (rfreading>204){
  rf=4;
}
else if (rfreading>143){
  rf=3;
}
else if (rfreading>81){
  rf=2;
}
else if (rfreading>40){
  rf=1;
}
else rf=0;

//use the higher 4 bits
 reading=(rf<<5)：
  Serial.print(reading);
  Serial.println();
 // reading = 0;
  delay(20);
}
