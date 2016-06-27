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

byte* alphabet[] = { a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z };
byte* text[] = { b, e, n, space, w, a, s, space, h, e, r, e };

int spaceWidth = 4;
int gapPerChar = 2;

long timeTilOffset = 250;

int offset = 5;
int paddingAfterMessage = 5;

int charWidth = 5 + gapPerChar; // Total width of character, including trailing gap

// These guys get assigned in `setup`, don't mess with these
int textWidth = 0;
int minOffset = 0;
long startTime = 0;

void setup() {
    Serial.begin(115200);

    strip.begin();
    strip.show();

    // Calculate width of text
    for (auto ch : text) {
        if (ch == space) {
            textWidth += spaceWidth;
        } else {
            textWidth += charWidth;
        }
    }
    textWidth += 5; // The last character has no trailing whitespace and therefore is just 5 pixels wide

    minOffset = -textWidth - paddingAfterMessage; // Since we're scrolling to the left, we negate the width and additional padding
}

void loop() {
    auto time = abs(sin(millis() * 0.001)) * 255;

    auto curOffset = offset;
    for (auto i = 0; i < COUNT(text); i++) {
        if (text[i] == space) {
            curOffset += spaceWidth - gapPerChar; // Undoes the gap added by the previous offset
            continue;
        } else {
            showChar(text[i], hue(time), curOffset);
            curOffset += charWidth;
        }
    }

    strip.setBrightness(abs(sin(millis() * 0.001)) * 80 + 10);
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
