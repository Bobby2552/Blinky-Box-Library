#include <Adafruit_NeoPixel.h>
#include <math.h>

#include "vec.h"

#define COUNT(arr) (sizeof(arr) / sizeof(*arr))

int buttonPin = 4;
int pin = 6;
int numLEDs = 25;

Adafruit_NeoPixel strip(numLEDs, pin, NEO_RGB + NEO_KHZ800);

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
byte m[5] = {0x0A, 0x0A, 0x15, 0x15, 0x11};
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

byte* text[] = { h, e, l, l, o, space, c, i, n, n, i, e };

int spaceWidth = 4;
int gapPerChar = 1;

long timeTilOffset = 250;

int offset = 5;
int paddingAfterMessage = 5;

// These guys eitherget assigned in `setup` or are dependent on the previous variables, don't mess with these
int charWidth = 5 + gapPerChar; // Total width of character, including trailing gap
int textWidth = 0;

int minOffset = 0;
long startTime = 0;

void setup() {
    pinMode(buttonPin, INPUT);
    Serial.begin(115200);

    strip.begin();
    strip.show();
    strip.setBrightness(10);

    // Calculate width of text
    for (auto i = 0; i < COUNT(text) - 1; i++) {
        if (text[i] == space) {
            textWidth += spaceWidth - gapPerChar; // If the subtraction by the `gapPerChar` is confusing, see the comment in `loop` where this operation occurs again
        } else {
            textWidth += charWidth;
        }
    }
    textWidth += 5; // The last character has no trailing whitespace and therefore is just 5 pixels wide

    minOffset = -textWidth - paddingAfterMessage; // Since we're scrolling to the left, we negate the width and additional padding
}

void loopText() {
    auto curOffset = offset;

    for (auto i = 0; i < COUNT(text); i++) {
        if (text[i] == space) {
            curOffset += spaceWidth - gapPerChar; // We subtract by the `gapPerChar` to undo the gap added by the previous iteration
            continue;
        } else {
            showCharRainbow(text[i], curOffset, i);
            curOffset += charWidth;
        }
    }

    strip.setBrightness(abs(sin(millis() * 0.001)) * 10 + 5);
    strip.show();
    delay(10);

    wipe();

    if (millis() - startTime > timeTilOffset) {
        offset--;

        if (offset < minOffset) {
            offset = 5;
        }

        startTime = millis();
    }
}

void rotate(double* vec, double ang) {
    vec[0] = vec[0] * cos(ang) - vec[1] * sin(ang);
    vec[1] = vec[0] * sin(ang) - vec[1] * cos(ang);
}

// Normalized device coordinate converter, takes [0, 5] and turns it into [-1, 1]
void NDC(double* vec, int x, int y) {
    vec[0] = (x / 4.0) * 2 - 1;
    vec[1] = (y / 4.0) * 2 - 1;
}

void loopColor() {
    for (auto r = 0; r < 5; r++) {
        for (auto c = 0; c < 5; c++) {
            strip.setPixelColor(index[r][c], hue(rainbowHue(r, c)));
        }
    }

    strip.show();
    delay(10);
}

void loopCircle() {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {

        }
    }

    strip.show();
    delay(10);
}

void loop() {
    loopCircle();
}

uint32_t hue(double wheelPos) {
    wheelPos = 255 - wheelPos;
    if(wheelPos < 85) {
        return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
    }
    if(wheelPos < 170) {
        wheelPos -= 85;
        return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
    }
    wheelPos -= 170;
    return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}

void wipe() {
    for (int i = 0; i < numLEDs; i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
}

uint32_t rainbowHue(int r, int c) {
    double vec[2];
    NDC(vec, c, r);

    rotate(vec, millis() * 0.005);

    auto ang = (atan2(vec[1], vec[0]) + PI) / (2 * PI);
    return ang * 255;
}

bool isPixelOn(byte character[], int r, int c) {
    if (r < 0 || c < 0 || r >= 5 || c >= 5) {
        return false;
    }

    byte curRow = character[r];
    return curRow & (0x10 >> c);
}

void showChar(byte character[], uint32_t color, int offset) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (isPixelOn(character, r, c - offset)) {
                strip.setPixelColor(index[r][c], color);
            }
        }
    }
}

void showCharRainbow(byte character[], int offset, int colorOffset) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (isPixelOn(character, r, c - offset)) {
                auto ang = rainbowHue(r, c) * 0.25 + 20 * colorOffset;
                strip.setPixelColor(index[r][c], hue(fmod(ang, 255)));
            }
        }
    }
}

void theaterChaseRainbow(uint8_t wait) {
    for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
        for (int q=0; q < 3; q++) {
            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, hue( (i+j) % 255));    //turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
                strip.setPixelColor(i+q, 0);        //turn every third pixel off
            }
        }
    }
}
