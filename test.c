#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    WINDOW *ventana1;
    system("resize -s 30 80");
    initscr();
    start_color();
    ventana1 = newwin(15, 50, 0, 0);
    init_pair(1,COLOR_YELLOW,COLOR_BLUE);
    init_pair(2,COLOR_BLUE, COLOR_YELLOW);
    wbkgd(ventana1,COLOR_PAIR(1));
    wprintw(ventana1, "POLLO");
    wrefresh(ventana1);
    wgetch(ventana1);
    wgetch(ventana1);
    system("resize -s 20 60");
    wbkgd(ventana1,COLOR_PAIR(2));
    wprintw(ventana1, "POLLO");
    wrefresh(ventana1);
    wgetch(ventana1);
    wgetch(ventana1);
    system("resize -s 35 85");
    system("clear");
    wbkgd(ventana1,COLOR_PAIR(1));
    wprintw(ventana1, "POLLO");
    wrefresh(ventana1);
    wgetch(ventana1);
    wgetch(ventana1);
    delwin(ventana1);
    endwin();
    system("resize -s 25 75");
}
