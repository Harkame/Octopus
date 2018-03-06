#ifndef INPUT_LINE_H
#define INPUT_LINE_H

#include "../../header.h"

extern pthread_mutex_t g_mutex;
extern struct LIST_STRING g_list_string;

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

void refresh_windows();

void exit_program();

void re_initialize_windows();

#endif
