#include <SPI.h>

FlightSimFloat alpha;
FlightSimInteger onGround;
FlightSimInteger stall;
FlightSimFloat acf_stall_warn_alpha;

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW (RED|GREEN)

// setup runs once
void setup() {

  //Serial.begin(57600);
  initializeWS2803();
  clearAOA();

  alpha = XPlaneRef("sim/flightmodel/position/alpha");
  alpha.onChange(updateAlpha);
  onGround = XPlaneRef("sim/flightmodel/failures/onground_any");
  stall = XPlaneRef("sim/flightmodel/failures/stallwarning");
  acf_stall_warn_alpha = XPlaneRef("sim/aircraft/overflow/acf_stall_warn_alpha");
  
}

// loop runs repetitively, as long as power is on
void loop() {
 FlightSim.update(); // causes X-Plane's changes to be received
}


void updateAlpha(float a) {
  
  // acf_stall_warn_alpha is 80% of range (GUESTIMATE)
  // acf_stall_warn_alpha / 0.8 = MAX STALL
  // 
  float max_alpha = acf_stall_warn_alpha / 0.80; 
  float percent_alpha;
  
  percent_alpha = (a / max_alpha);
  if (!onGround) {
    if (percent_alpha > 0.9) {
      setLedColor(3, RED);
      setLedColor(4, RED);
      setLedColor(5, RED);
    } else if (percent_alpha > 0.8) {
      setLedColor(3, RED);
      setLedColor(4, RED);
      setLedColor(5, YELLOW);
    } else if (percent_alpha > 0.7) {
      setLedColor(3, RED);
      setLedColor(4, YELLOW);
      setLedColor(5, YELLOW);
    } else if (percent_alpha > 0.6) {
      setLedColor(3, YELLOW);
      setLedColor(4, GREEN);
      setLedColor(5, GREEN);
    } else if (percent_alpha > -0.6) {
      setLedColor(3, GREEN);
      setLedColor(4, GREEN);
      setLedColor(5, GREEN);
    } else {
      setLedColor(3, RED);
      setLedColor(4, RED);
      setLedColor(5, RED);
    }
  } else {
      setLedBar(3, 0x00,0x00,0x00);
      setLedBar(4, 0x00,0x00,0x00);
      setLedBar(5, 0x00,0x00,0x00);

  }
  updateWS2803();
  
}


