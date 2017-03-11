// MIT License
//
// Copyright (c) 2017 Andrea Di Saverio
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "color_utils.h"

float hue_to_rgb(float p, float q, float t) {

    if(t < 0) t += 1;
    if(t > 1) t -= 1;
    if(t < (float)1/6) {
        return p + (q - p) * 6 * t;
    }
    if(t < (float)1/2) {
        return q;
    }
    if(t < (float)2/3) {
        return p + (q - p) * ((float)2/3 - t) * 6;
    }

    return p;
}

void hsl_to_rgb(float h, float s, float l, float *r, float *g, float *b) {

    if (s == 0) {
        *r = *g = *b = l;
    } else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;
        *r = hue_to_rgb(p, q, h + (float) 1 / 3);
        *g = hue_to_rgb(p, q, h);
        *b = hue_to_rgb(p, q, h - (float) 1 / 3);
    }
}