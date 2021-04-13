//F-photodetector

const int numreadings = 40; //number of readings per sampling cycle

int readings[8][numreadings];      // the readings[i] from the analog input
int readIndex = 0;              // the index of the current reading
int total[8] = {0};                  // the running total[i]
int average[8] = {0};                // the average[i]
int average_map[8] = {0};
int readings_min[8] = {0, 0, 0, 1, 0, 0, 0, 0};
int readings_max[8] = {410, 410, 410, 410, 410, 410, 410, 410};
int average_map_last[8] = {0};
int threshold_on = 9; //mapped (0-1024 to 0-32 threshold voltage 1.5v)
int threshold_off = 3; //mapped (0-1024 to 0-32 threshold voltage 0.5v)
int uv[8] = {0};
int count = 0;
void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings[i] to 0:
  for (int i = 0; i < 7; i++) {
    for (int thisReading = 0; thisReading < numreadings; thisReading++) {
      readings[i][thisReading] = 0;
    }
    total[i] = 0;
    average[i] = 0;
    average_map[i] = 0;
    average_map_last[i] = 0;
    uv[i] = {0};
  }
}

void loop() {
  //runing average of each pin
  for (readIndex = 0; readIndex < numreadings; readIndex++) {
    for (int i = 0; i < 7; i++) {
      // subtract the last reading:
      total[i] = total[i] - readings[i][readIndex];
      // read from the sensor:
      readings[i][readIndex] = analogRead(i);
      // add the reading to the total[i]:
      total[i] = total[i] + readings[i][readIndex];
      // calculate the average[i]:
      average[i] = total[i] / numreadings;
      //average[i] = constrain(average[i], readings_min[i], readings_max[i]);
      average_map[i] = map(average[i], readings_min[i], readings_max[i], 0, 32);
    }
    //For debug only
    //Serial.print(millis());
    //Serial.print(",");
    //Serial.print(readings[5][readIndex]);
    //Serial.print(",");
    // Serial.println(average[5]);




  }
  for (int i = 0; i < 7; i++) {
    if (average_map[i] > threshold_on)  {
      uv[i] = 1;
    }
    else if (average_map[i] < threshold_off) {
      uv[i] = 0;
    }
  }


  count++;
  if (count == 5) {
    for (int i = 0; i < 7; i++) {
      average_map_last[i] = average_map[i];
    }
    count = 0;
  }

  //Serial.print(uv[0]);
  byte matlabreading;
  matlabreading = uv[0] + uv[1] * 2 + uv[2] * 4 + uv[3] * 8 + uv[4] * 16 + uv[5] * 32 + uv[6] * 64 + uv[7] * 128;
  Serial.print(matlabreading);
  Serial.println();
  delay(10);
  matlabreading = 0;


}
