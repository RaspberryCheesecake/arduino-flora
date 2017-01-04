#include <Adafruit_NeoPixel.h>
#include <CapacitiveSensor.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

CapacitiveSensor   cs_10_9 = CapacitiveSensor(10,9);        
// 10M resistor between pins 9 & 10, pin 9 is sensor pin

void setup() {
  cs_10_9.set_CS_AutocaL_Millis(0xFFFFFFFF);     
  // turn off autocalibrate on this channel
  Serial.begin(9600);
  
  strip.begin();
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:
  long start = millis();
  long total1 =  cs_10_9.capacitiveSensor(30);

  if (total1 > 4000){
  digitalWrite(7, HIGH);
  strip.setPixelColor(0, 0, 255, 0);  
  strip.show();
  } else {
  strip.setPixelColor(0, 0, 0, 0); 
  strip.show();
  }
  
  Serial.print(millis() - start);        // check on performance in milliseconds
  Serial.print("\t");
  Serial.print(total1);                  // print sensor output 1
  Serial.print("\n");

  delay(500); // so we don't just spam the serial port

}
