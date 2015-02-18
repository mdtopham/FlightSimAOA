
#define nLEDs 6
uint32_t ledBar[nLEDs];

SPISettings ws2803s;

void initializeWS2803() {
    ws2803s = SPISettings(12000000,MSBFIRST,SPI_MODE0);
    SPI.begin();
}

void clearWS2803() {
  for(unsigned int i = 0; i< nLEDs; i++) {
    ledBar[i] = 0x00;
  }
}

void setLedBar(unsigned int i, uint8_t r,uint8_t g,uint8_t b) {
  if (i < nLEDs) {
    ledBar[i] = (r<<16)|(g<<8)|(b);
  } // Out of range? Do Nothing
}

void setLedColor(unsigned int i, uint32_t rgb) {
  if (i < nLEDs) {
    ledBar[i] = rgb;
  } // Out of range? Do Nothing
}


void updateWS2803() {
  uint8_t r,g,b;
  
  SPI.beginTransaction(ws2803s);
  for (int x=0; x<nLEDs;x++) {
    r = (ledBar[x]>>16) & 0xFF;
    g = (ledBar[x]>>8) & 0xFF;
    b = (ledBar[x]) & 0xFF;

    SPI.transfer(r);
    SPI.transfer(g);
    SPI.transfer(b);
  }
  delayMicroseconds(600); // 600 microsecond delay required to latch new LEDs
  SPI.endTransaction();
}

