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


struct  R_G_B {
  int R;
  int G;
  int B;
};

//damn, can't make structs be return type in Arduino, or not easily...
R_G_B sensorReadingsTo255Range(float red_meas, float green_meas, float blue_meas, float clear_meas) {
  uint8_t sum = red_meas + green_meas + blue_meas + clear_meas;
  float r, g, b;
  r = red_meas/sum;
  g = green_meas/sum;
  b = blue_meas/sum;
  r = r*256;
  g = g*256;
  b = b*256;

  struct R_G_B Values = {(int)r, (int)g, (int)b};
  return Values;
}

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

  R_G_B shown = sensorReadingsTo255Range(red, green, blue, clearness);

  Serial.print("\tR 255:\t"); Serial.print(shown.R);
  Serial.print("\tG 255:\t"); Serial.print(shown.G);
  Serial.print("\tB 255:\t"); Serial.print(shown.B);   Serial.print("\n");

  //strip.setPixelColor(0, r_show, g_show, b_show);

  delay(5000);
  
}
