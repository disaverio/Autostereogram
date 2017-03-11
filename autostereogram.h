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

#ifndef AUTOSTEREOGRAM_H
    #define AUTOSTEREOGRAM_H

    #include <gtk/gtk.h>
    #include <stdlib.h>
    #include <time.h>
    #include <unistd.h>
    #include <string.h>

    #define PATTERN_WIDTH           120
    #define MIN_PATTERN_REPETITIONS 5 // min horizontal repetitions of pattern to cover input depth map
    #define MAX_RELATIVE_DEVIATION  0.5 // relative to pattern_width
    #define MAX_PIXEL_DEVIATION     (PATTERN_WIDTH*MAX_RELATIVE_DEVIATION)

    #define RANDOM_BOARD_T  1
    #define STRIPED_BOARD_T 2

    #define RANDOM_BOARD  "random"
    #define STRIPED_BOARD "striped"

#endif