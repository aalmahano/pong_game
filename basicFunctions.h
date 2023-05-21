#include <windows.h>

// mueve el cursor a un posicion x y
void Gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(h, c);
}

// oculta el cursor
void HideCursor()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO c;

	c.bVisible = false;
	SetConsoleCursorInfo(h, &c);
}
