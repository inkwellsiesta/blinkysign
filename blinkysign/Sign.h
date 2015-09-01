#include <Adafruit_NeoPixel.h>


const uint8_t gamma[] PROGMEM = { // Gamma correction table for LED brightness
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };
  
  
const uint8_t BOTTOMRIGHT[] = {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
const uint8_t TOPRIGHT[] = {24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13};
const uint8_t TOPLEFT[] = {36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25};
const uint8_t BOTTOMLEFT[] = {0, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37};


class Sign {
  public:
    enum StartupPattern {CWWAVE, CELLCYCLE, CCWWAVE};
    
    void initialize();
    void startupSequence(StartupPattern);
    void cwWave(uint8_t, uint8_t, uint8_t);
    void ccwWave(uint8_t, uint8_t, uint8_t);
    void setCellColor(const uint8_t *, uint8_t, uint8_t, uint8_t);
    
  private:
    static const int PIN = 0;
    static const int LIGHTSPERCELL = 12;
    static const int NUMCELLS = 4;
    static const int NUMLIGHTS = NUMCELLS*LIGHTSPERCELL;
    
    Adafruit_NeoPixel pixels;
    
    void initialize(int, int);
    void cwCellWave(const uint8_t *, uint8_t, uint8_t, uint8_t);
    void ccwCellWave(const uint8_t *, uint8_t, uint8_t, uint8_t);
};


void Sign::initialize() {
  initialize(PIN, NUMLIGHTS);
}

void Sign::initialize(int pin, int numLights) {
  pixels.setPin(pin);
  pixels.updateLength(numLights);
  pixels.updateType(NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.setBrightness(100); // FORJOHN: change brightness from 0 to 100
  pixels.clear();
  pixels.show();
}

void Sign::startupSequence(StartupPattern pattern) {
  switch (pattern) {
    case CWWAVE :
      cwWave(255, 255, 255); // FORJOHN: change the color of the startup wave
      break;
    case CELLCYCLE :
      pixels.clear();
      setCellColor(TOPLEFT, 255, 255, 255);
      delay(1000);
      pixels.clear();
      setCellColor(TOPRIGHT, 255, 255, 255);
      delay(1000);
      pixels.clear();
      setCellColor(BOTTOMLEFT, 255, 255, 255);
      delay(1000);
      pixels.clear();
      setCellColor(BOTTOMRIGHT, 255, 255, 255);
      delay(1000);
      break;
    case CCWWAVE : 
      ccwWave(255, 255, 255);
      break;
  };
}

void Sign::cwWave( uint8_t r, uint8_t g, uint8_t b) {
      cwCellWave(TOPLEFT, r, g, b); 
      cwCellWave(TOPRIGHT, r, g, b);
      cwCellWave(BOTTOMRIGHT, r, g, b);
      cwCellWave(BOTTOMLEFT, r, g, b);
}

void Sign::ccwWave( uint8_t r, uint8_t g, uint8_t b) {
      ccwCellWave(TOPLEFT, r, g, b); 
      ccwCellWave(BOTTOMLEFT, r, g, b);
      ccwCellWave(BOTTOMRIGHT, r, g, b);
      ccwCellWave(TOPRIGHT, r, g, b);
}

void Sign::cwCellWave(const uint8_t * cellIdx, uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < LIGHTSPERCELL; ++i) {
    pixels.clear();
    pixels.setPixelColor(*(cellIdx+i), pgm_read_byte(&gamma[r]), pgm_read_byte(&gamma[g]), pgm_read_byte(&gamma[b]));
    pixels.show();
    delay(30);
  }
};

void Sign::ccwCellWave(const uint8_t * cellIdx, uint8_t r, uint8_t g, uint8_t b) {
  for (int i = LIGHTSPERCELL; i > 0; --i) {
    pixels.clear();
    pixels.setPixelColor(*(cellIdx+i-1), pgm_read_byte(&gamma[r]), pgm_read_byte(&gamma[g]), pgm_read_byte(&gamma[b]));
    pixels.show();
    delay(30);
  }
};
  
void Sign::setCellColor(const uint8_t * cellIdx, uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < LIGHTSPERCELL; ++i) {
     pixels.setPixelColor(*(cellIdx+i), pgm_read_byte(&gamma[r]), pgm_read_byte(&gamma[g]), pgm_read_byte(&gamma[b]));
  }
  pixels.show();
}
