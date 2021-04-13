//f-energy

//PIN definition
int chargingpin=2;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
 pinMode(chargingpin,INPUT);
}

void loop() {
 
 // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading to bar levels 
  uint8_t voltage = map(sensorValue,0,1023,0,5);

//add 2 for graphing purpose in matlab
voltage=voltage+2 ;

  // print out the value you read:
  
int charging=digitalRead(chargingpin);

  byte matlabreading;

  matlabreading = voltage+(1-charging)*128;
  
  Serial.print(matlabreading);
  Serial.println();
  delay(100);

}
