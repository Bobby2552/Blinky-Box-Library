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

byte a[5] = {0x04, 0x0A, 0x1F, 0x11, 0x11};
byte b[5] = {0x1E, 0x11, 0x1E, 0x11, 0x1E};
byte c[5] = {0x1E, 0x11, 0x10, 0x11, 0x1E};
byte d[5] = {0x1E, 0x11, 0x11, 0x11, 0x1E};
byte e[5] = {0x1F, 0x10, 0x1E, 0x10, 0x1F};
byte f[5] = {0x1F, 0x10, 0x1F, 0x10, 0x10};
byte h[5] = {0x11, 0x11, 0x1F, 0x11, 0x11};
byte i[5] = {0x1F, 0x04, 0x04, 0x04, 0x1F};
byte j[5] = {0x1F, 0x04, 0x04, 0x14, 0x1C};
byte k[5] = {0x11, 0x12, 0x1C, 0x12, 0x11};
byte l[5] = {0x10, 0x10, 0x10, 0x10, 0x1F};
byte m[5] = {0x1B, 0x15, 0x15, 0x11, 0x11};
byte n[5] = {0x11, 0x19, 0x15, 0x13, 0x11};
byte o[5] = {0x0E, 0x11, 0x11, 0x11, 0x0E};
byte p[5] = {0x1F, 0x11, 0x1F, 0x10, 0x10};
byte q[5] = {0x0E, 0x11, 0x15, 0x12, 0x0D};
byte r[5] = {0x1E, 0x11, 0x1E, 0x11, 0x11};
byte s[5] = {0x0F, 0x10, 0x0E, 0x01, 0x1E};
byte t[5] = {0x1F, 0x04, 0x04, 0x04, 0x04};
byte u[5] = {0x11, 0x11, 0x11, 0x11, 0x0E};
byte v[5] = {0x11, 0x11, 0x11, 0x0A, 0x04};
byte y[5] = {0x11, 0x0A, 0x04, 0x04, 0x04};
byte space[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

void setup() {
    strip.begin();
    strip.show();
    strip.setBrightness(100);
}

void loop() {
    show_char(a);
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

void show_char(byte character[]) {
    for (int r = 0; r < 5; r++) {
        byte curRow = character[r];

        for (int c = 0; c < 5; c++) {
            boolean curPixel = curRow & (1 << c);
            if (curPixel) {
                strip.setPixelColor(index[r][c], Wheel(0));
            }
        }
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