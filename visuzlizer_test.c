#include <ncurses.h>

int main()
{
	initscr();

	move(10, 20);
	addstr("Hello World");
	getch();

	endwin();
	return (0);
}
