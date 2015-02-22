#include <SPI.h>

#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define TURQUOISE (BLUE|GREEN)
#define VIOLET (RED|BLUE)
#define YELLOW (RED|GREEN)
#define OFF 0


// setup runs once
void setup() {

  //Serial.begin(57600);
  initializeWS2803();
  
  // Initialize LEDs in sequence to verify LED activity
  for(int i=0;i<6;i++) {
    setLedColor(i,RED);
  }
  updateWS2803();
  delay(250);
  for(int i=0;i<6;i++) {
    setLedColor(i,GREEN);
  }
  updateWS2803();
  delay(250);
  for(int i=0;i<6;i++) {
    setLedColor(i,BLUE);
  }
  updateWS2803();
  delay(250);  
  for(int i=0;i<6;i++) {
    setLedColor(i,OFF);
  }
  updateWS2803();
  delay(250);  
}

// loop runs repetitively, as long as power is on
void loop() {
 FlightSim.update(); // causes X-Plane's changes to be received
}




