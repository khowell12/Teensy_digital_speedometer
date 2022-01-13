#include "SPI.h"
#include "ILI9341_t3.h"
#include "font_Arial.h" 

//from PJRC
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 255
#define TFT_MOSI 11
#define TFT_SCLK 14
#define TFT_MISO 12
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC, TFT_RST, TFT_MOSI, TFT_SCLK, TFT_MISO);

long previousMillis = 0; // Use with counter
boolean hallTrigger = false;
const float tireCirc = 0.000812; // circumference of scooter tire in miles
void setup() {
  // put your setup code here, to run once.
pinMode(15, INPUT); // set pin 15 = input, where signal out of sensor is plugged in
pinMode(13, OUTPUT); // LED to output pull high when hall sensor is triggered
digitalWrite(13, LOW);
SPI.setSCK(14); // set SCK to pin 14 so that pin 13 can be the output (LED) pin.
tft.begin();
tft.setRotation(3); //roatate to landscape?
tft.fillScreen(ILI9341_BLUE); // paint screen blue
tft.setTextColor(ILI9341_WHITE, 0);
tft.setTextSize(5);
//tft.setCursor(140,120); // print text in middle of screen
Serial.begin(9600);
}

void speed(){
  int diff = millis()- previousMillis; // time between function triggers in ms
  previousMillis = millis(); // update previousMillis value
  float spd = 3600 * 1000 * tireCirc / (float)diff; // (mi / ms) * 1000 ms/s * 3600 s/hr = mi/hr
  if (spd < 1.0){
    spd = 0; // No need to worry about low speeds
  }
  tft.setCursor(140,120);
  tft.print(spd); // send value to display
  Serial.println("spd = " + (String)spd); // show output for troublshooting
  Serial.println(diff);// see if calculating properly
}

void loop() {
  // put your main code here, to run repeatedly:
  //use loop to take care of time between pulses
long sensor = analogRead(15);
if (sensor > 600) { //if hall is "triggered" i.e. detects magnetic field. 
  digitalWrite(13, HIGH); // turn on LED
  while (hallTrigger == false){
    speed(); //Call speed function
    hallTrigger = true; // call speed function once per trigger.
  }
}
else {
  digitalWrite(13, LOW); // Turn off LED
  hallTrigger = false; // reset trigger
}
//Serial.println(sensor); // print output of sensor
delay(10);
}
