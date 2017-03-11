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

#ifndef DRAWING_UTILS_H
    #define DRAWING_UTILS_H

    void create_random_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board);
    void create_striped_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board);
    void create_pixbuf(int width, int height, GdkPixbuf **output);
    void create_stereogram_board(int board_type, int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf **board);
    void create_stereogram(GdkPixbuf *depth_map, GdkPixbuf *board, int depth_map_width, int depth_map_height, int pattern_width);

#endif