/*

SpitFire console input and misc functions module
Written by Robert Christensen as part of the Spitfire Framework

Certification of Authenticity: This code is mine, written solely by me,
without assistance from any other individuals.

Copyright 2020. You may use and modify this code as you please,
but I must recieve authorship credit. Furthermore you may redistribute
this code only as part of a project--this cannot be redistributed as
a standalone file.

By running or compiling this code or including it in a project, you fully and
irrevocably accept responsibility for any and all damage or other
liabilities that may arise while or after using it. You waive any and
all right to sue me using these code files as a basis.

*/

#include "sfio.h"

#include <Windows.h> //For console manipulation, at the cost of portability
#include <conio.h>
#include <string>
#include <ctime> //For cquerych with timeout

namespace sf {

	char cquerych() {
		return _getch();
	}

	char cquerycht(float timeout) {
		char c = '\0';
		bool didRecieveInput = false;

		clock_t start = clock();
		while (!(didRecieveInput = _kbhit()) && (clock() <= start + timeout)) {
			Sleep(50);
		}

		if (didRecieveInput) c = _getch();

		return c;
	}

	void csetcurpos(unsigned int x, unsigned int y) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(hConsole, coord);
	}

	int cgetw()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left;
	}

	int cgeth()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top;
	}

	void csetcurvis(bool visiblity)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;
		cursorInfo.bVisible = visiblity;
		cursorInfo.dwSize = visiblity ? 20 : 1;
		SetConsoleCursorInfo(hConsole, &cursorInfo);
	}

	void cfill(char c, int x1, int y1, int x2, int y2) {
		for (int x = x1; x <= x2; x++) {
			for (int y = y1; y <= y2; y++) {
				csetcurpos(x, y); std::cout << c;
			}
		}
	}

#pragma warning (push)
#pragma warning (disable: 4309)
	const char border_n = 196;
	const char border_w = 179;
	const char border_s = 196;
	const char border_e = 179;

	const char border_nw = 218;
	const char border_sw = 192;
	const char border_se = 217;
	const char border_ne = 191;
#pragma warning (pop)

	void cdrawbox(int x1, int y1, int x2, int y2) {
		csetcurpos(x1, y1); std::cout << border_nw;
		csetcurpos(x1, y2); std::cout << border_sw;
		csetcurpos(x2, y2); std::cout << border_se;
		csetcurpos(x2, y1); std::cout << border_ne;

		cfill(border_n, x1 + 1, y1, x2 - 1, y1);
		cfill(border_s, x1 + 1, y2, x2 - 1, y2);
		cfill(border_w, x1, y1 + 1, x1, y2 - 1);
		cfill(border_e, x2, y1 + 1, x2, y2 - 1);
	}

	void cclear()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD cwritten;
		DWORD csize;
		CONSOLE_SCREEN_BUFFER_INFO cinfo;
		COORD ccoords = { 0, 0 };

		GetConsoleScreenBufferInfo(hConsole, &cinfo) &&
			(csize = cinfo.dwSize.X * cinfo.dwSize.Y) &&
			FillConsoleOutputCharacter(hConsole, (TCHAR)' ', csize, ccoords, &cwritten) &&
			GetConsoleScreenBufferInfo(hConsole, &cinfo) &&
			FillConsoleOutputAttribute(hConsole, cinfo.wAttributes, csize, ccoords, &cwritten) &&
			SetConsoleCursorPosition(hConsole, { 0,0 });
	}

	void showDialog(std::string str, int x, int y) {
		StyledTextBlock dialog((int)str.length() + 2, 3);
		dialog.drawBox(TextStyle(), 0, 0, dialog.width - 1, dialog.height - 1);
		dialog.putStr(str, 1, 1);
		dialog.blit(x - dialog.width / 2, y - dialog.height / 2);
	}

}