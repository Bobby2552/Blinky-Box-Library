#include <Adafruit_NeoPixel.h>

int pin = 6;
int numLEDs = 25;
int index[5][5] = {
  {0, 1, 2, 3, 4},
  {9, 8, 7, 6, 5},
  {10, 11, 12, 13, 14},
  {19, 18, 17, 16, 15},
  {20, 21, 22, 23, 24}
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, pin, NEO_RGB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(100);
}

void loop() {
  theaterChaseRainbow(1);
  for (int x = 0; x < 60; x++) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      for (int c = 0; c < 255; c++) {
      strip.setPixelColor(index[i][j], Wheel(c));   
   strip.show();
delay(5);
wipe();
      }
    }
  }  
  strip.show();
  delay(0);
  wipe();
    }
  strip.show();
}

uint32_t Wheel(double WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void wipe() {
  for (int i = 0; i < numLEDs; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
