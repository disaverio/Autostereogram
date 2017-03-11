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
#include "drawing_utils.h"

typedef struct {
    GdkPixbuf *depth_map;

    int depth_map_height;
    int depth_map_width;

    int board_type;
    int board_pattern_repetitions;

    int pattern_width;
    int pattern_height;
} Params;

static cairo_surface_t *surface = NULL;

static gboolean init_drawing_area(GtkWidget *widget, GdkEventConfigure *event, gpointer data) {

    if (surface) {
        return TRUE;
    }

    Params params = *((Params *) data);
    GdkPixbuf *autostereogram;

    create_stereogram_board(params.board_type, params.pattern_width, params.pattern_height, params.board_pattern_repetitions, &autostereogram);

    create_stereogram(params.depth_map, autostereogram, params.depth_map_width, params.depth_map_height, params.pattern_width);

    surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, params.pattern_width * params.board_pattern_repetitions, params.pattern_height);
    cairo_t *cr = cairo_create(surface);

    gdk_cairo_set_source_pixbuf(cr, autostereogram, 0, 0);
    cairo_paint(cr);
    cairo_destroy(cr);

    return TRUE;
}

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data) {

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    return FALSE;
}

static void close_window(void) {

    if (surface)
        cairo_surface_destroy(surface);

    gtk_main_quit ();
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    // user input
    char *img_name;
    char *board_type_input = NULL;
    int k = 0;

    if (argc < 2) {
        printf("Use: autostereogram -f filname [-b random | striped]\n");
        exit(EXIT_FAILURE);
    }
    while ((k = getopt(argc, argv, "b:f:")) != -1) {
        switch (k) {
            case 'b':
                board_type_input = optarg;
                break;
            case 'f':
                img_name = optarg;
                break;
            default:
                printf("Use: autostereogram -f filename [-b random | striped]\n");
                exit(EXIT_FAILURE);
        }
    }

    Params params;

    if (!(params.depth_map = gdk_pixbuf_new_from_file(img_name, NULL))) {
        printf("Error: invalid file '%s'\n", img_name);
        exit(EXIT_FAILURE);
    }

    if ((board_type_input == NULL) || (strcmp(board_type_input, RANDOM_BOARD) == 0)) {
        params.board_type = RANDOM_BOARD_T;
    } else if (strcmp(board_type_input, STRIPED_BOARD) == 0) {
        params.board_type = STRIPED_BOARD_T;
    } else {
        printf("Error: Unknown board type '%s'\n", board_type_input);
        exit(EXIT_FAILURE);
    }

    // size calc
    params.depth_map_width = gdk_pixbuf_get_width(params.depth_map);
    params.depth_map_height = gdk_pixbuf_get_height(params.depth_map);

    params.pattern_height = params.depth_map_height;
    params.pattern_width = PATTERN_WIDTH;

    int img_pattern_repetitions = params.depth_map_width/PATTERN_WIDTH + 1; // number of patterns to cover input image
    if (img_pattern_repetitions < MIN_PATTERN_REPETITIONS) {
        printf("Image too small. Min width: %dpx\n", PATTERN_WIDTH*MIN_PATTERN_REPETITIONS);
        exit(EXIT_FAILURE);
    }
    params.board_pattern_repetitions = img_pattern_repetitions + 1;

    // init gtk
    gtk_init(&argc, &argv);

    // window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Autostereogram");
    gtk_container_set_border_width(GTK_CONTAINER(window), 8);
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    // frame
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // drawing area
    GtkWidget *da = gtk_drawing_area_new();
    gtk_widget_set_size_request(da, PATTERN_WIDTH * params.board_pattern_repetitions, params.pattern_height); // min size
    gtk_container_add(GTK_CONTAINER(frame), da);

    // events
    g_signal_connect(da, "draw", G_CALLBACK(draw_cb), NULL);
    g_signal_connect(da, "configure-event", G_CALLBACK(init_drawing_area), &params);
    gtk_widget_set_events(da, gtk_widget_get_events(da));

    // start
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}