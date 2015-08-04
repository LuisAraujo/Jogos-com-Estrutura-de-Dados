#include<windows.h>
#include<conio.h>

void gotoxy(int cord_x, int cord_y) {

COORD c;

   c.X = cord_x;
   c.Y = cord_y;

   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
