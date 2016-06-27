#include <Adafruit_NeoPixel.h>
#include <math.h>

#define COUNT(arr) (sizeof(arr) / sizeof(*arr))

int pin = 6;
int numLEDs = 25;
int index[5][5] = {
    {0, 9, 10, 19, 20},
    {1, 8, 11, 18, 21},
    {2, 7, 12, 17, 22},
    {3, 6, 13, 16, 23},
    {4, 5, 14, 15, 24}
};

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLEDs, pin, NEO_RGB + NEO_KHZ800);

byte a[5] = {0x04, 0x0A, 0x1F, 0x11, 0x11};
byte b[5] = {0x1E, 0x11, 0x1E, 0x11, 0x1E};
byte c[5] = {0x1F, 0x10, 0x10, 0x10, 0x1F};
byte d[5] = {0x1E, 0x11, 0x11, 0x11, 0x1E};
byte e[5] = {0x1F, 0x10, 0x1E, 0x10, 0x1F};
byte f[5] = {0x1F, 0x10, 0x1F, 0x10, 0x10};
byte g[5] = {0x1F, 0x10, 0x13, 0x11, 0x1F};
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
byte w[5] = {0x11, 0x15, 0x15, 0x0A, 0x0A};
byte x[5] = {0x11, 0x0A, 0x04, 0x0A, 0x11};
byte y[5] = {0x11, 0x0A, 0x04, 0x04, 0x04};
byte z[5] = {0x1F, 0x02, 0x04, 0x08, 0x01F};
byte space[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

byte* alphabet[] = { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z };
byte* text[] = { b, e, n, space, w, a, s, space, h, e, r, e };

void setup() {
    Serial.begin(115200);

    strip.begin();
    strip.show();
    strip.setBrightness(100);
}

int curIndex = 0;
long startTime = 0;
long timePerChar = 2000;

void loop() {
    showCharRainbow(text[curIndex]);
    strip.show();
    delay(10);

    wipe();

    if (millis() - startTime > timePerChar) {
        ++curIndex %= COUNT(text);
        startTime = millis();
    }
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

boolean isPixelOn(byte character[], int r, int c) {
    byte curRow = character[r];
    return curRow & (0x10 >> c);
}

void showChar(byte character[], uint32_t color) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (isPixelOn(character, r, c)) {
                strip.setPixelColor(index[r][c], color);
            }
        }
    }
}

void showCharRainbow(byte character[]) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (isPixelOn(character, r, c)) {
                auto time = abs(sin(millis() * 0.0001)) * 255;

                strip.setPixelColor(index[r][c], Wheel(time));
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
