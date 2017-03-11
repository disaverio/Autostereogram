//
// Created by andrea on 10/03/17.
//

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