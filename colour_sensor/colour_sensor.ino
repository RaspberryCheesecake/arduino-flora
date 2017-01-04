#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600); //open serial port to PC at 9600 baud
  while(!Serial) ; // while serial port isn't open yet, wait
  // this is important otherwise the Serial will print
  // before our monitor is ready!
  Serial.println("Colour viewing test!");

  strip.begin(); //setup neopixels
  strip.show(); // initialise all neopixels to off
  
  if (Serial == true) {
    Serial.println("Found colour sensor TCS34725!");
  } else {
    Serial.println("No TCS34725 found... check connections :(");
    while(1); // 'halt'
  }

}

uint16_t red, green, blue, clearness; // make some global variables to store measured data


void loop() {
  tcs.setInterrupt(false); // turn on the sensor's white LED, for consistent readings
  delay(60); // takes some time to read the data
  
  tcs.getRawData(&red, &green, &blue, &clearness); //change value of variables
  // by emulating pass by reference, yesss
  tcs.setInterrupt(true);  // now turn off the sensor's white LED

  Serial.print("C:\t"); Serial.print(clearness);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);   Serial.print("\n");

  // code to turn the measured values into 0 - 255 range
  // NOT in a separate function def because returning got messy...
  uint32_t sum = red + green + blue + clearness;
  float r, g, b;
  r = red;      g = green;    b = blue;
  r /= sum;         g /= sum;         b /= sum;
  r = r*256;        g = g*256;        b = b*256;
  int r_show, g_show, b_show;
  r_show = (int)r;  g_show = (int)g;  b_show = (int)b;

  Serial.print("\t\tR:\t"); Serial.print(r_show);
  Serial.print("\tG:\t"); Serial.print(g_show);
  Serial.print("\tB:\t"); Serial.print(b_show);   Serial.print("\n");

  strip.setPixelColor(0, r_show, g_show, b_show);
  strip.show();

  delay(5000);
  
}
