
#include <curses.h>


int main(int argc, char **argv) {
  initscr();
  printw("Hello world!!!!");
  refresh();
  getch();
  endwin();

  return 0;

}
