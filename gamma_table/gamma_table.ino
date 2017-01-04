byte gammatable[256];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //open serial port to PC at 9600 baud
  while(!Serial) ;
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    gammatable[i] = x;      
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i=0; i<256; i++) {
    Serial.println(gammatable[i]);
  }

}
