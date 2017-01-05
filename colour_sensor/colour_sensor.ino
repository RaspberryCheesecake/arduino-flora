#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

byte gammatable[256];

void setup() {
  strip.begin(); //setup neopixels
  strip.show(); // initialise all neopixels to off

  // set up the Gamma table
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2); // I think 2 actually works a bit better than 2.5
    x *= 255;
      
    gammatable[i] = x;      
  }

  tcs.setInterrupt(true);  // now turn off the sensor's white LED

}

uint16_t red, green, blue, clearness; // make some global variables to store measured data

void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
    }
  }

void loop() {
  tcs.setInterrupt(false); // turn on the sensor's white LED, for consistent readings
  delay(60); // takes some time to read the data
  
  tcs.getRawData(&red, &green, &blue, &clearness); //change value of variables
  // by emulating pass by reference, yesss
  tcs.setInterrupt(true);  // now turn off the sensor's white LED

  // code to turn the measured values into 0 - 255 range
  // NOT in a separate function def because returning got messy...
  float r, g, b;
  r = red;      g = green;    b = blue;
  r = r*0.755;       g = g*1.049;     b = b*1.196; // code I worked out to adjust
  // to make it more like the human eye's perception of colour (see notebook)

  uint32_t sum = r + g + b + clearness;
  r /= sum;         g /= sum;         b /= sum; 
  r = r*256;        g = g*256;        b = b*256;
  int r_show, g_show, b_show;
  r_show = (int)r;  g_show = (int)g;  b_show = (int)b;

  colorWipe(strip.Color(gammatable[r_show], gammatable[g_show], gammatable[b_show]), 500);
  strip.show();

  delay(5000);
  
}
