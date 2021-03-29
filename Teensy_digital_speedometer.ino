/*
 * This project will determine speed by measureing frequency with a hall effect sensor
 * and calculating velocity based off of that measurement and the known size of the wheel
 * of whatever vehicle is used. A magnet will be placed on a point of the rim of the vehicle
 * and a hall effect sensor will be mounted on the frame of the vehicle. The value of the 
 * trigger is variable and depends on the gauss of the magnet and the proximity to the sensor 
 * in its final installation. An LCD display will be implemented to display the speed measurement
*/

//long timeToPulse; 

void setup() {
pinMode(15, INPUT); // set pin 15 = input, where signal out of sensor is plugged in
pinMode(13, OUTPUT); // LED to output
digitalWrite(13, LOW);
attachInterrupt(digitalPinToInterrupt(15),speed,RISING); //Run speed function only when hall effect signal is pulled low to high
Serial.begin(9600);
}
long previousMillis = 0;


void speed(){ // this function will only calculate speed
  long diff = millis() - previousMillis;
  previousMillis = millis();
  digitalWrite(13, HIGH);
  Serial.println(diff);
  
}

void loop() {
  //use loop to take care of time between pulses
digitalWrite(13, LOW); // turn off LED if interrupt is not called
}
