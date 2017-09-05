#ifndef INPUT_LINE_H
#define INPUT_LINE_H

#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct input_line
{
    char* a_line;

    int a_length;
    int a_capacity;
    int a_cursor;
    int a_last_rendered;
} input_line;

void init_screen();

void make_input_line(struct input_line* p_input_line_to_init);

void render_line(struct input_line* p_buffer);

int get_line_non_blocking(struct input_line *p_buffer, char *target, int max_len);

void print_textarea();

#endif
