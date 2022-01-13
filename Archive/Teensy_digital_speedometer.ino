/*
 * This project will determine speed by measureing frequency with a hall effect sensor
 * and calculating velocity based off of that measurement and the known size of the wheel
 * of the vehicle used. A magnet will be placed on a point of the rim of the vehicle
 * and a hall effect sensor will be mounted on the frame of the vehicle. The value of the 
 * trigger is variable and depends on the gauss of the magnet and the proximity to the sensor 
 * in its final installation. An LCD display will be implemented to display the speed measurement
*/

//10-8-21: working on adding display functions

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

long sensor = analogRead(15); // Hall sensor attached to pin 15
long previousMillis = 0; // Use with counting time between pulses

void setup() {
 // initialize display, draw speedo parts, create number for display, update display every time interupt? or every few times display updated. consider averaging function.
tft.begin();// start display
pinMode(15, INPUT); // set pin 15 = input, where signal out of sensor is plugged in
pinMode(13, OUTPUT); // LED to output
digitalWrite(13, LOW);
SPI.setSCK(14); // set SCK to 14 so that LED on pin 13 can still be used.
attachInterrupt(digitalPinToInterrupt(15),speed,RISING); //Run speed function only when hall effect signal is pulled low to high
tft.begin();
tft.setRotation(3); // Rotate to landscape
tft.fillScreen(ILI9341_BLUE); // Set BKG to Blue
Serial.begin(9600);
}



void speed(){ // this function will only calculate speed
  long diff = millis() - previousMillis; // Calculate time between hall effect trigger i.e. magnet rotating around the rim
  previousMillis = millis(); // previous value becomes current value
   //front wheel is 18" in diameter
  digitalWrite(13, HIGH); // LED is triggered to signal this function has been called
  tft.setTextColor(ILI9341_WHITE, 0); //For output font
  tft.setTextSize(5);
  tft.setCursor(140,120); // print text in middle of screen
  tft.print(diff); 
  Serial.println(diff); // FOR TESTING - display the diff value on serial 
  
}

void loop() {
  //use loop to take care of time between pulses
digitalWrite(13, LOW); // turn off LED if interrupt is not called
Serial.println(sensor); // print output of sensor
}
