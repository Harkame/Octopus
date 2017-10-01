#include "./input_line.h"

void make_input_line(struct input_line* p_input_line_to_init)
{
    p_input_line_to_init->a_line = NULL;
    p_input_line_to_init->a_length = 0;
    p_input_line_to_init->a_capacity = 0;
    p_input_line_to_init->a_cursor = 0;
    p_input_line_to_init->a_last_rendered = 0;
}

void free_input_line(struct input_line* p_input_line_to_free)
{
    free(p_input_line_to_free->a_line);
}

void render_line(struct input_line* p_buffer)
{
    int t_index;

    for(t_index = 0; t_index < p_buffer->a_length; t_index++)
    {
        chtype t_chtype = p_buffer->a_line[t_index];

        if(t_index == p_buffer->a_cursor)
            t_chtype |= A_REVERSE;

        addch(t_chtype);
    }

    if(p_buffer->a_cursor == p_buffer->a_length)
    {
        addch(' ' | A_REVERSE);
        t_index++;
    }

    int t_rendered = t_index;

    for(t_index = t_index; t_index < p_buffer->a_last_rendered; t_index++)
        addch(' ');

    p_buffer->a_last_rendered = t_rendered;
}

int retrieve_content(struct input_line* p_buffer, char* target, int max_len)
{
    int len = p_buffer->a_length < (max_len - 1) ? p_buffer->a_length : (max_len - 1);
    memcpy(target, p_buffer->a_line, len);
    target[len] = '\0';
    p_buffer->a_cursor = 0;
    p_buffer->a_length = 0;
    return len + 1;
}

void add_char(struct input_line* p_buffer, char p_char_to_add)
{
    // Ensure enough space for new character
    if(p_buffer->a_length == p_buffer->a_capacity)
    {
        int ncap = p_buffer->a_capacity + 128;
        char *nline = (char*) realloc(p_buffer->a_line, ncap);

        if(!nline)
            return;

        p_buffer->a_line = nline;
        p_buffer->a_capacity = ncap;
    }

    memmove(&p_buffer->a_line[p_buffer->a_cursor+1],&p_buffer->a_line[p_buffer->a_cursor],p_buffer->a_length - p_buffer->a_cursor);

    p_buffer->a_line[p_buffer->a_cursor] = p_char_to_add;

    ++p_buffer->a_cursor;
    ++p_buffer->a_length;
}

int handle_input(struct input_line* p_buffer, char* target, int max_len, int p_key)
{
    if(!(p_key & KEY_CODE_YES) && isprint(p_key))
    {
        add_char(p_buffer, p_key);

        return 0;
    }

    switch(p_key)
    {
        case KEY_RESIZE:
            re_initialize_windows();

            print_textarea();

            refresh_windows();
        break;

        case ERR:
            exit_program();
        break;

        case KEY_LEFT:
            if(p_buffer->a_cursor > 0)
                p_buffer->a_cursor --;
        break;

        case KEY_RIGHT:
            if(p_buffer->a_cursor < p_buffer->a_length)
                p_buffer->a_cursor ++;
        break;

        case KEY_HOME:
            p_buffer->a_cursor = 0;
        break;

        case KEY_END:
            p_buffer->a_cursor = p_buffer->a_length;
        break;

        case '\t':
            add_char(p_buffer, '\t');
            break;

        case KEY_BACKSPACE:
        case 127:
        case 8:
            if(p_buffer->a_cursor <= 0)
                break;

            p_buffer->a_length --;
            p_buffer->a_cursor--;

            return 0;

        case KEY_DC:
            if(p_buffer->a_cursor < p_buffer->a_length)
            {
                memmove(&p_buffer->a_line[p_buffer->a_cursor], &p_buffer->a_line[p_buffer->a_cursor+1], p_buffer->a_length - p_buffer->a_cursor - 1);
                p_buffer->a_length --;
            }

        break;

        case KEY_ENTER:
        case '\r':
        case '\n':
            return retrieve_content(p_buffer, target, max_len);
    }
    return 0;
}

int get_line_non_blocking(struct input_line *p_buffer, char *target, int max_len)
{
    while(1)
    {
        int p_key = getch();
        if(p_key == ERR)
            return 0;

        int n = handle_input(p_buffer, target, max_len, p_key);

        if(n)
            return n;
    }
}
