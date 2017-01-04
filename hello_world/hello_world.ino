// Pin D7 has an LED connected on FLORA
// Let's be creative and call it onboard_led
int onboard_led = 7;

void setup() {
  // initialise the digital pin as output:
  pinMode(onboard_led, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // LED on
  digitalWrite(onboard_led, HIGH);
  // Wait a sec
  delay(1000);
  //LED off
  digitalWrite(onboard_led, LOW);
  // Wait half a sec
  delay(500);
  
  //and so on...

}
