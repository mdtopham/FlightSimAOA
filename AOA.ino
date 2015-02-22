
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define TURQUOISE (BLUE|GREEN)
#define VIOLET (RED|BLUE)
#define YELLOW (RED|GREEN)
#define OFF 0

#define BRIGHTNESS 128

FlightSimFloat   alpha;
FlightSimInteger onGround;
FlightSimInteger acf_stall_warn_alpha;
unsigned int led[3];

void initializeAOA(unsigned int led_1, unsigned int led_2, unsigned int led_3) {
  led[0] = led_1;
  led[1] = led_2;
  led[2] = led_3;

  clearAOA();

  alpha = XPlaneRef("sim/flightmodel/position/alpha");
  alpha.onChange(updateAlpha);
  onGround = XPlaneRef("sim/flightmodel/failures/onground_any");
  acf_stall_warn_alpha = XPlaneRef("sim/aircraft/overflow/acf_stall_warn_alpha");
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
      setLedColor(led[0], RED);
      setLedColor(led[1], RED);
      setLedColor(led[2], RED);
    } else if (percent_alpha > 0.85) {
      setLedColor(led[0], RED);
      setLedColor(led[1], RED);
      setLedColor(led[2], YELLOW);
    } else if (percent_alpha > 0.8) {
      setLedColor(led[0], RED);
      setLedColor(led[1], YELLOW);
      setLedColor(led[2], YELLOW);
    } else if (percent_alpha > 0.7) {
      setLedColor(led[0], YELLOW);
      setLedColor(led[1], YELLOW);
      setLedColor(led[2], YELLOW);
    } else if (percent_alpha > 0.65) {
      setLedColor(led[0], YELLOW);
      setLedColor(led[1], YELLOW);
      setLedColor(led[2], GREEN);
    } else if (percent_alpha > 0.6) {
      setLedColor(led[0], YELLOW);
      setLedColor(led[1], GREEN);
      setLedColor(led[2], GREEN);
    } else if (percent_alpha > -0.6) {
      setLedColor(led[0], GREEN);
      setLedColor(led[1], GREEN);
      setLedColor(led[2], GREEN);
    } else {
      setLedColor(led[0], RED);
      setLedColor(led[1], RED);
      setLedColor(led[2], RED);
    }
  } else {
      setLedColor(led[0], OFF);
      setLedColor(led[1], OFF);
      setLedColor(led[2], OFF);

  }
  updateWS2803();
  
}

void clearAOA() {
      setLedColor(led[0], OFF);
      setLedColor(led[1], OFF);
      setLedColor(led[2], OFF);
      updateWS2803();
}



