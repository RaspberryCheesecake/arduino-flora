#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
// 'strip' is just one pixel here, connected to Digital 6
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

void setup() {
  strip.begin();
  strip.show(); // initialise all pixels to off

}

void loop() {
  // here's a small example of colour changing:
  colorWipe(strip.Color(255,0,0), 500); //Red
  colorWipe(strip.Color(0,255,0), 500); //Green
  colorWipe(strip.Color(0,0,255), 500); //Blue

}

// Fill the pixels one after the other with a colour:
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i,c);
    strip.show();
    delay(wait);
  }
}

