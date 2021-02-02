#include <ncurses.h>

int main()
{
    initscr();
    WINDOW* header = newwin(LINES/5,COLS,0,0);
    box(header,0,0);
    wrefresh(header);
    
    int x,y;
    getmaxyx(header,y,x);
    mvwaddstr(header,y/2,(x-11)/2,"hello world");
    wrefresh(header);
    getchar();
    delwin(header);
    endwin();
    return 0;
}
