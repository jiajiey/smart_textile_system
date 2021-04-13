// F-touch sensor
#include <Wire.h>
#include <MPR121.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

// mapping constrains
#define LOW_DIFF 0
#define HIGH_DIFF 31

//Global variables
int reading[11] = {0};
int row = 0;
int col = 0;
int brightness = 0;

int  gain[11] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//threshold
#define THRESHOLD 3

/*********************         SETUP     *************************************/
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }

  // Serial.println("MPR121 Touch sensor");

  //Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!MPR121.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  // Serial.println("MPR121 found!");

  // slow down some of the MPR121 baseline filtering to avoid
  // filtering out slow hand movements
  MPR121.setRegister(MPR121_NHDF, 0x01); //noise half delta (falling)
  MPR121.setRegister(MPR121_FDLF, 0x3F); //filter delay limit (falling)

  matrix.begin(0x70);  // pass in the address
  // Serial.println("8x8 LED Matrix found!");
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(3, HIGH);    // turn the LED off by making the voltage LOW

}

/*********************          MAIN     *************************************/
void loop() {
  readingtouch();
  process();
  LED();
  matlab();
}

void readingtouch() {
  //Get reading of each electrode
  // update all of the data from the MPR121
  MPR121.updateAll();
  // read the difference between the measured baseline and the measured continuous data
  for (int i = 0; i < 12; i++) {

    reading[i] = MPR121.getBaselineData(i) - MPR121.getFilteredData(i);
    //print out the reading value for debug
    //Serial.println(reading[i]);

    // map the LOW_DIFF..HIGH_DIFF range to 0..255 (8-bit resolution for analogWrite)
    reading[i] = constrain(reading[i], LOW_DIFF, HIGH_DIFF);
    //reading[i] = map(reading[i], LOW_DIFF, HIGH_DIFF, 0, 1023);

  }

  //Serial.println();
  // delay(500);

}
void process() {

  int max_rowreading = 0;
  int max_colreading = 0;
  row = 0;
  col = 0;

  for (int i = 0; i < 12; i++) {
    reading[i] = gain[i] * reading[i];
    //print out the reading value for debug
    //  Serial.println(reading[i]);
  }
  //Serial.println();
  //delay(300);

  //Extract the index of the max reading from E0 to E5

  for (int i = 0; i < 6; i++) {
    if ( max_rowreading < reading[i]) {
      max_rowreading = reading[i];
      row = i + 1;
    }
  }

  //Extract the index of the max reading from E6 to E11
  for (int i = 6; i < 12; i++) {
    if ( max_colreading < reading[i]) {
      max_colreading = reading[i];
      col = i - 5;
    }
  }

  //Check if the max_colreading and max_rowreading are valid
  if (max_rowreading < THRESHOLD || max_colreading < THRESHOLD) {
    max_rowreading = 0;
    max_colreading = 0;
    row = 0;
    col = 0;
  }

  // map the signal strength to brightness
  brightness = map(max_colreading, LOW_DIFF, HIGH_DIFF, 0, 15);

}
void LED() {

  matrix.clear();      // clear display
  matrix.setBrightness(brightness);
  matrix.drawPixel(col - 1, row - 1, LED_RED);
  matrix.writeDisplay();  // write the changes we just made to the display

}

void matlab() {
  byte matlabreading;

  matlabreading = char(row) << 4;
  matlabreading = matlabreading + char(col);

  Serial.print(matlabreading);
  Serial.println();
  delay(10);

  if (row == 1 && col == 4) {
    digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(10);                       // wait for a second

  }

  else if (row == 2 && col == 4) {
    digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)
    delay(10);                       // wait for a second
  }
  else {
    digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(3, HIGH);   // turn the LED on (HIGH is the voltage level)
  }

}
