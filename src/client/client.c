#include "client.h"

#define DEFAULT_PORT            6666
#define DEFAULT_IP                  "127.0.0.1"
#define DEFAULT_DIRECTORY ".test"

#define ERROR_MESSAGE_SOCKET     "socket"
#define ERROR_MESSAGE_CONNECT "connect"
#define ERROR_MESSAGE_FOPEN       "Error : fopen\n"

#define MESSAGE_REMAINING                "%d remaining\n"
#define MESSAGE_FILE_DOWNLOADED "%s downloaded\n"

#define PROMPT_MESSAGE "> "

#define OPTION_IP                  "-i ip_address\n"
#define OPTION_DIRECTORY "-d directory\n"
#define OPTION_PORT            "-p port\n"

#define EXIT_MESSAGE "exit"

int g_socket;

pthread_t g_read_thread;
pthread_t g_write_thread;

int  g_port = DEFAULT_PORT;
char g_ip[BUFSIZ]        = {DEFAULT_IP};
char g_directory[BUFSIZ] = {DEFAULT_DIRECTORY};

char g_file_name[BUFSIZ];

FILE* g_downloaded_file;

WINDOW* g_window_textarea;
WINDOW* g_window_form;

struct LIST_STRING* g_list_string;

pthread_mutex_t g_mutex;

void* read_handler()
{
    char t_buffer[BUFSIZ];

    while(1)
    {
        ssize_t read_size = recv(g_socket, t_buffer, BUFSIZ, 0);

        if(read_size == 0)
        {
            fprintf(stdout, "Connection lost\n");

            exit_program();
        }
        else if(read_size == -1)
        {
            fprintf(stdout, "Connection lost\n");

            exit_program();
        }
        else
        {
            pthread_mutex_lock(&g_mutex);
            add_element_list_string(g_list_string, t_buffer);

            if(size_list_string(g_list_string) > 10)
                remove_first_element_list_string(g_list_string);
            pthread_mutex_unlock(&g_mutex);

            print_textarea();

            memset(t_buffer, 0, BUFSIZ);

            move(46, 1);
            clrtoeol();
        }
    }
}

void* write_handler()
{
    struct input_line linep_bufferfer;
    make_input_line(&linep_bufferfer);

    int lines_read = 0;
    while(1)
    {
        move(46, 1);
        mvwprintw(g_window_form, 1, 1, PROMPT_MESSAGE);
        char line[BUFSIZ];
        int len = get_line_non_blocking(&linep_bufferfer, line, BUFSIZ);
        if(len > 0)
        {
            if(strcmp(line, "exit") == 0)
                exit_program();

            pthread_mutex_init(&g_mutex, NULL);

            pthread_mutex_lock(&g_mutex);
            add_element_list_string(g_list_string, line);

            if(size_list_string(g_list_string) > 10)
                remove_first_element_list_string(g_list_string);
            pthread_mutex_unlock(&g_mutex);

            if(send(g_socket, line, strlen(line), 0) == -1)
            {
                perror("send");

                exit_program();
            }

            print_textarea();

            lines_read ++;

            move(46, 1);
            clrtoeol();
        }

        render_line(&linep_bufferfer);

        pthread_mutex_lock(&g_mutex);
        wrefresh(g_window_textarea);
        wrefresh(g_window_form);
        refresh();
        pthread_mutex_unlock(&g_mutex);
    }
}

void exit_program()
{
    endwin();

    free(g_window_textarea);
    free(g_window_form);

    close(g_socket);

    exit(0);
}

void foo()
{
    init_screen();

    g_window_textarea = subwin(stdscr, LINES / 3, COLS, 0, 0);        // Créé une fenêtre de 'LINES / 2' lignes et de COLS colonnes en 0, 0
    g_window_form = subwin(stdscr, LINES / 16, COLS,  45, 0); // Créé la même fenêtre que ci-dessus sauf que les coordonnées changent


    box(g_window_textarea, ACS_VLINE, ACS_HLINE);
    box(g_window_form, ACS_VLINE, ACS_HLINE);

    wrefresh(g_window_textarea);
    wrefresh(g_window_form);
    refresh();

    wmove(g_window_form, 1, 1);
    mvwprintw(g_window_form, 1, 1, PROMPT_MESSAGE);

    g_list_string = create_list_string();

    struct sockaddr_in t_sockaddr_in_client;

     g_socket = socket(AF_INET , SOCK_STREAM , 0);

     if (g_socket == -1)
     {
          perror("socket");
          exit_program();
     }

     t_sockaddr_in_client.sin_addr.s_addr = inet_addr(g_ip);
     t_sockaddr_in_client.sin_family            = AF_INET;
     t_sockaddr_in_client.sin_port               = htons(g_port);

     if(connect(g_socket , (struct sockaddr *)&t_sockaddr_in_client, sizeof(t_sockaddr_in_client)) < 0)
     {
          perror("connect");
          exit_program();
     }

     box(g_window_textarea, ACS_VLINE, ACS_HLINE);
     box(g_window_form, ACS_VLINE, ACS_HLINE);

    if(pthread_create(&g_read_thread, NULL, (void*) read_handler, NULL) == -1)
        exit_program();

    if(pthread_create(&g_write_thread, NULL, (void*) write_handler, NULL) == -1)
        exit_program();

    //pthread_join(g_write_thread, NULL);
    pthread_join(g_read_thread, NULL);
}

void help()
{
     fprintf(stdout, OPTION_IP);
     fprintf(stdout, OPTION_PORT);
     fprintf(stdout, OPTION_DIRECTORY);

     exit_program();
}

void print_textarea()
{
    char** t_buffer;
    t_buffer = alloca(10 * sizeof(char*));

    for(int t_index; t_index < 10; t_index++)
         t_buffer[t_index] = alloca(50 * sizeof(char));

    pthread_mutex_init(&g_mutex, NULL);

    pthread_mutex_lock(&g_mutex);

    list_string_to_array(g_list_string, t_buffer, 0, 10);

     for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
     {
         move(1 + t_index, 1);
         clrtoeol();
     }

     for(int t_index = 0; t_index < size_list_string(g_list_string); t_index++)
         mvwprintw(g_window_textarea,1 + t_index, 1, t_buffer[t_index]);

     box(g_window_textarea, ACS_VLINE, ACS_HLINE);
     box(g_window_form, ACS_VLINE, ACS_HLINE);


    wrefresh(g_window_textarea);
    pthread_mutex_unlock(&g_mutex);
}

void init_screen()
{
    initscr();

    cbreak();
    nonl();
    timeout(0);
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    intrflush(stdscr, 0);
    leaveok(stdscr, 1);
}

int main(int argc , char** argv)
{
     foo();
}
