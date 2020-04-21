/*

SpitFire advanced graphics module
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

#include "sfgr.h"
#include "sfio.h"

#include <ostream>

#include <Windows.h> //For console text coloration, at the cost of portability

namespace sf {

#pragma region Coloration utils

	unsigned char ascol(bool r, bool g, bool b, bool light) {
		return 	r * 0b0100 +
			g * 0b0010 +
			b * 0b0001 +
			light * 0b1000;
	}

	void csetcolb(unsigned char col) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, col);
	}

	void csetcolc(bool r, bool g, bool b, bool light) {
		csetcolb(ascol(r, g, b, light));
	}

	#pragma endregion

	#pragma region TextStyle

	void TextStyle::regenStylecode()
	{
		stylecode = ascol(r, g, b, light);
	}

	TextStyle::TextStyle() : TextStyle(1, 1, 1, 1) {}

	TextStyle::TextStyle(const bool& r, const bool& g, const bool& b, const bool& light)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->light = light;

		stylecode = 0; //To suppress compiler error

		regenStylecode();
	}

	void TextStyle::setR(const bool& r) { this->r = r;     regenStylecode(); }
	void TextStyle::setG(const bool& g) { this->g = g;     regenStylecode(); }
	void TextStyle::setB(const bool& b) { this->b = b;     regenStylecode(); }
	void TextStyle::setLight(const bool& light) { this->light = light; regenStylecode(); }

	void TextStyle::applyStyle() const
	{
		csetcolb(stylecode);
	}

	std::ostream& operator<<(std::ostream& out, const TextStyle& style)
	{
		style.applyStyle();
		return out;
	}

	#pragma endregion

	#pragma region StyledChar

	std::ostream& operator<<(std::ostream& out, const StyledChar& c)
	{
		c.style.applyStyle();
		out << c.character;
		return out;
	}

	StyledChar::StyledChar()
	{
		character = '\0';
		style = TextStyle();
	}

	StyledChar::StyledChar(const char& c)
	{
		character = c;
		style = TextStyle();
	}

	StyledChar::StyledChar(const char& c, const TextStyle& s)
	{
		character = c;
		style = s;
	}

	#pragma endregion

	#pragma region StyledTextBlock

	StyledTextBlock::StyledTextBlock(const int& w, const int& h) {
		width = w;
		height = h;

		textBlock = new StyledChar * [w];
		for (int i = 0; i < w; i++) {
			textBlock[i] = new StyledChar[h];
			for (int j = 0; j < h; j++) textBlock[i][j] = StyledChar();
		}
	}

	StyledTextBlock::StyledTextBlock(const std::string& src) {
		width = 0;
		height = 1;

		//Detect size
		int thisLineWidth = 0;
		for (int i = 0; i < src.length(); i++) {

			if (src.at(i) == '\n') {
				height++;
				if (width < thisLineWidth) width = thisLineWidth;
			}
			else {
				thisLineWidth++;
			}

		}
		if (width < thisLineWidth) width = thisLineWidth;

		//Init textblock
		textBlock = new StyledChar * [width];
		for (int i = 0; i < width; i++) {
			textBlock[i] = new StyledChar[height];
			for (int j = 0; j < height; j++) textBlock[i][j] = StyledChar();
		}

		//Populate textblock
		int x = 0, y = 0;
		for (int i = 0; i < src.length(); i++) {

			setChar(src.at(i), x, y);

			if (src.at(i) == '\n') {
				y++;
				x = 0;
			}
			else {
				x++;
			}
		}
	}

	//Cpy ctor
	StyledTextBlock::StyledTextBlock(const StyledTextBlock& src) {
		this->width = src.width;
		this->height = src.height;

		//Init textblock
		textBlock = new StyledChar * [width];
		for (int i = 0; i < width; i++) {
			textBlock[i] = new StyledChar[height];
			for (int j = 0; j < height; j++) textBlock[i][j] = src.textBlock[i][j];
		}
	}

	StyledTextBlock::~StyledTextBlock() {
		for (int i = 0; i < width; i++) delete[] textBlock[i];
		delete[] textBlock;
	}

	void StyledTextBlock::setStyledChar(const StyledChar& sc, const int& x, const int& y)
	{
		if (x >= width || y >= height || x < 0 || y < 0) {
			return;
		}

		setStyle(sc.style, x, y);
		setChar(sc.character, x, y);
	}

	void StyledTextBlock::setStyle(const TextStyle& style, const int& x, const int& y)
	{
		if (x >= width || y >= height || x < 0 || y < 0) {
			return;
		}

		textBlock[x][y].style = style;
	}

	void StyledTextBlock::setChar(const char& chars, const int& x, const int& y)
	{
		if (x >= width || y >= height || x < 0 || y < 0) {
			return;
		}

		textBlock[x][y].character = chars;
	}

	void StyledTextBlock::fillStyledChar(const StyledChar& sc, const int& x1, const int& y1, const int& x2, const int& y2)
	{
		for (int ix = x1; ix <= x2; ix++) {
			for (int iy = y1; iy <= y2; iy++) {
				setStyledChar(sc, ix, iy);
			}
		}
	}

	void StyledTextBlock::fillStyle(const TextStyle& style, const int& x1, const int& y1, const int& x2, const int& y2)
	{
		for (int ix = x1; ix <= x2; ix++) {
			for (int iy = y1; iy <= y2; iy++) {
				setStyle(style, ix, iy);
			}
		}
	}

	void StyledTextBlock::fillChar(const char& chars, const int& x1, const int& y1, const int& x2, const int& y2)
	{
		for (int ix = x1; ix <= x2; ix++) {
			for (int iy = y1; iy <= y2; iy++) {
				setChar(chars, ix, iy);
			}
		}
	}

	void StyledTextBlock::putStr(const std::string& str, const int& x, const int& y)
	{
		for (int i = 0; i < str.length() && i + x < width; i++) {
			setChar(str.at(i), i + x, y);
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

	void StyledTextBlock::drawBox(const TextStyle& style, int x1, int y1, int x2, int y2)
	{
		setStyledChar(StyledChar(border_nw, style), x1, y1);
		setStyledChar(StyledChar(border_sw, style), x1, y2);
		setStyledChar(StyledChar(border_se, style), x2, y2);
		setStyledChar(StyledChar(border_ne, style), x2, y1);

		fillStyledChar(StyledChar(border_s, style), x1 + 1, y2, x2 - 1, y2);
		fillStyledChar(StyledChar(border_n, style), x1 + 1, y1, x2 - 1, y1);
		fillStyledChar(StyledChar(border_w, style), x1, y1 + 1, x1, y2 - 1);
		fillStyledChar(StyledChar(border_e, style), x2, y1 + 1, x2, y2 - 1);
	}

	void StyledTextBlock::blit(const int& x, const int& y)
	{
		for (int iy = 0; iy < height; iy++) {
			csetcurpos(x, y + iy);
			for (int ix = 0; ix < width; ix++) {
				if (textBlock[ix][iy].character > 32 || textBlock[ix][iy].character < 0) {
					std::cout << textBlock[ix][iy];
				}
				else {
					std::cout << " ";
				}
			}
		}
	}

	void StyledTextBlock::blit(StyledTextBlock& target, const int& x, const int& y)
	{
		for (int iy = 0; iy < height; iy++) {
			for (int ix = 0; ix < width; ix++) {
				//If within bounds, blit
				if(0 < x+ix && x+ix < target.width && 0 < y+iy && y+iy < target.height) target.textBlock[x+ix][y+iy] = textBlock[ix][iy];
			}
		}
	}
#pragma endregion

}

