#include "vec.h"
#include <math.h>

vec::vec(double x, double y, double z) : x(x), y(y), z(z) { }

void vec::set(double x, double y, double z) {
    this->x = x; this->y = y; this->z = z;
}

vec vec::operator+(vec rhs) {
    return vec(x + rhs.x, y + rhs.y, z + rhs.z);
}

vec vec::operator-(vec rhs) {
    return *this + -rhs;
}

vec vec::operator*(vec rhs) {
    return vec(x * rhs.x, y * rhs.y, z * rhs.z);
}

vec vec::operator/(vec rhs) {
    return vec(x / rhs.x, y / rhs.y, z / rhs.z);
}

vec vec::operator*(double rhs) {
    return vec(x * rhs, y * rhs, z * rhs);
}

vec vec::operator/(double rhs) {
    return vec(x / rhs, y / rhs, z / rhs);
}

vec vec::operator-() {
    return vec(-x, -y, -z);
}

double vec::len() {
    return sqrt(square(x) + square(y) + square(z));
}

vec vec::normalize() {
    return *this / len();
}

void rgb(Adafruit_NeoPixel& strip, int i, vec rgb_) {
    strip.setPixelColor(i, strip.Color(rgb_.r, rgb_.g, rgb_.b));
}

void rgb(Adafruit_NeoPixel& strip, int x, int y, vec rgb_) {
    rgb(strip, index[y][x], rgb_);
}

void rgb(Adafruit_NeoPixel& strip, vec pos, vec rgb_) {
    rgb(strip, pos.x, pos.y, rgb_);
}

// https://en.wikipedia.org/wiki/HSL_and_HSV#Converting_to_RGB
void hsv(Adafruit_NeoPixel& strip, int i, vec hsv_) {
    double chroma = hsv_.s * hsv_.v;
    double hPrime = hsv_.h / 60;
    double x = chroma * (1 - fabs(fmod(hPrime, 2) - 1));

    vec rgbCube(0, 0, 0);
    switch (int(hPrime)) {
    case 5:
        rgbCube.set(chroma, 0, x);
        break;
    case 4:
        rgbCube.set(x, 0, chroma);
        break;
    case 3:
        rgbCube.set(0, x, chroma);
        break;
    case 2:
        rgbCube.set(0, chroma, x);
        break;
    case 1:
        rgbCube.set(x, chroma, 0);
        break;
    case 0:
        rgbCube.set(chroma, x, 0);
        break;
    }

    double valueMatch = hsv_.v - chroma;
    vec rgbConverted = rgbCube + vec(valueMatch, valueMatch, valueMatch);
    vec rgbScaled = rgbConverted * 255;

    rgb(strip, i, rgbScaled);
}

void hsv(Adafruit_NeoPixel& strip, int x, int y, vec hsv_) {
    hsv(strip, index[y][x], hsv_);
}

void hsv(Adafruit_NeoPixel& strip, vec pos, vec hsv_) {
    hsv(strip, pos.x, pos.y, hsv_);
}

void print(vec v) {
    Serial.print("<");
    Serial.print(v.x);
    Serial.print(", ");

    Serial.print(v.y);
    Serial.print(", ");

    Serial.print(v.z);
    Serial.print(">");
}
