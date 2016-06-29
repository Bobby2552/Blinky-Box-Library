#pragma once

#include <Adafruit_NeoPixel.h>

/*
 * Simple vector struct, modelled after GLSL
 */
struct vec {
    double x, y, z;
    double &r = x, &g = y, &b = z;
    double &h = r, &s = g, &v = b;

    vec(double x=0, double y=0, double z=0);
    void set(double x=0, double y=0, double z=0);

    vec operator+(vec rhs);
    vec operator-(vec rhs);
    vec operator*(vec rhs);
    vec operator/(vec rhs);

    vec operator*(double rhs);
    vec operator/(double rhs);

    vec operator-();

    double len();
    vec normalize();

    //vec dot(vec rhs);
};

// Strip coloring
void rgb(Adafruit_NeoPixel& strip, int i, vec rgb);
void rgb(Adafruit_NeoPixel& strip, int x, int y, vec rgb);
void rgb(Adafruit_NeoPixel& strip, vec pos, vec rgb);

void hsv(Adafruit_NeoPixel& strip, int i, vec hsv);
void hsv(Adafruit_NeoPixel& strip, int x, int y, vec hsv);
void hsv(Adafruit_NeoPixel& strip, vec pos, vec hsv);

void print(vec v);

const int index[5][5] = {
    {0, 9, 10, 19, 20},
    {1, 8, 11, 18, 21},
    {2, 7, 12, 17, 22},
    {3, 6, 13, 16, 23},
    {4, 5, 14, 15, 24}
};
