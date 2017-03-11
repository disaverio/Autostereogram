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

#include "autostereogram.h"
#include "color_utils.h"

void create_pixbuf(int width, int height, GdkPixbuf **output) {
    *output = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, width, height);

    if (*output == NULL) {
        printf("Error creating GdkPixbuf: not enough memory.\n");
        exit(EXIT_FAILURE);
    }
}

void create_random_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board) {
    int n_ch = gdk_pixbuf_get_n_channels(board);
    int row = gdk_pixbuf_get_rowstride(board);

    guchar *pixels;
    float r, g, b;
    float min = 0;
    float max = 1;
    for (int h = 0; h < pattern_height; h++) {
        for (int w = 0; w < pattern_width; w ++) {
            hsl_to_rgb(((float)rand() / RAND_MAX)*(max-min)+min, 1, 0.5, &r, &g, &b);
            for (int i = 0; i < pattern_repetitions; i++) {
                pixels = gdk_pixbuf_get_pixels(board) + h * row + (w+i*pattern_width) * n_ch;

                pixels[0] = r*255;
                pixels[1] = g*255;
                pixels[2] = b*255;
            }
        }
    }
}

void create_striped_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board) {
    int n_ch = gdk_pixbuf_get_n_channels(board);
    int row = gdk_pixbuf_get_rowstride(board);

    guchar *pixels;
    float r, g, b;
    for (int h = 0; h < pattern_height; h++) {
        for (int w = 0; w < pattern_width; w ++) {
            hsl_to_rgb(w/(float)pattern_width, 1, 0.5, &r, &g, &b);
            for (int i = 0; i < pattern_repetitions; i++) {
                pixels = gdk_pixbuf_get_pixels(board) + h * row + (w+i*pattern_width) * n_ch;
                pixels[0] = r*255;
                pixels[1] = g*255;
                pixels[2] = b*255;
            }
        }
    }
}

void create_stereogram_board(int board_type, int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf **board) {
    create_pixbuf(pattern_width * pattern_repetitions, pattern_height, board);

    if (board_type == RANDOM_BOARD_T) {
        create_random_board(pattern_width, pattern_height, pattern_repetitions, *board);
    } else if (board_type == STRIPED_BOARD_T) {
        create_striped_board(pattern_width, pattern_height, pattern_repetitions, *board);
    }
}

void create_stereogram(GdkPixbuf *depth_map, GdkPixbuf *board, int depth_map_width, int depth_map_height, int pattern_width) {
    int dm_n_ch = gdk_pixbuf_get_n_channels(depth_map);
    int dm_row = gdk_pixbuf_get_rowstride(depth_map);
    int as_n_ch = gdk_pixbuf_get_n_channels(board);
    int as_row = gdk_pixbuf_get_rowstride(board);

    for (int h = depth_map_height-1; h >= 0; h--) {
        for (int w = depth_map_width-1; w >= 0; w--) {

            guchar *dm_pixel = gdk_pixbuf_get_pixels(depth_map) + h * dm_row + w * dm_n_ch;
            int deviation = (int) ((dm_pixel[0]/(float)255)*MAX_PIXEL_DEVIATION);

            if (deviation > 0) {
                guchar *stereogram_source_pixel = gdk_pixbuf_get_pixels(board) + h * as_row + w * as_n_ch;
                int current_pattern = w / pattern_width;

                for (int i = 0; i <= MIN(2,current_pattern); i++) { // play with stop condition of this cycle to try
                    guchar *stereogram_destination_pixel = gdk_pixbuf_get_pixels(board) + h * as_row + ((w-i*pattern_width)+deviation) * as_n_ch;
                    stereogram_destination_pixel[0] = stereogram_source_pixel[0];
                    stereogram_destination_pixel[1] = stereogram_source_pixel[1];
                    stereogram_destination_pixel[2] = stereogram_source_pixel[2];
                }
            }
        }
    }
}