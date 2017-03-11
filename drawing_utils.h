
#ifndef DRAWING_UTILS_H
    #define DRAWING_UTILS_H

    void create_random_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board);
    void create_striped_board(int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf *board);
    void create_pixbuf(int width, int height, GdkPixbuf **output);
    void create_stereogram_board(int board_type, int pattern_width, int pattern_height, int pattern_repetitions, GdkPixbuf **board);
    void create_stereogram(GdkPixbuf *depth_map, GdkPixbuf *board, int depth_map_width, int depth_map_height, int pattern_width);

#endif