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

#pragma once
#include <ostream>

namespace sf {

	//RGBL 0-1 to color code
	unsigned char ascol(bool r, bool g, bool b, bool light);

	//Set color from color code byte
	void csetcolb(unsigned char col);

	//Set color from components
	void csetcolc(bool r, bool g, bool b, bool light);

	class TextStyle {
	private:
		bool r;
		bool g;
		bool b;
		bool light;

		unsigned char stylecode;

		void regenStylecode();

	public:
		TextStyle();
		TextStyle(const bool& r, const bool& g, const bool& b, const bool& light);

		void setR(const bool& r);
		void setG(const bool& g);
		void setB(const bool& b);
		void setLight(const bool& light);

		void applyStyle() const;

		friend std::ostream& operator<<(std::ostream& out, const TextStyle& style);
	};

	class StyledChar {
	public:
		char character;
		TextStyle style;

		StyledChar();
		StyledChar(const char& c);
		StyledChar(const char& c, const TextStyle& s);

		friend std::ostream& operator<<(std::ostream& out, const StyledChar& c);
	};

	class StyledTextBlock {
	private:
		StyledChar** textBlock;

	public:
		int width, height;

		StyledTextBlock(const int& w, const int& h);
		StyledTextBlock(const std::string& src);
		StyledTextBlock(const StyledTextBlock& src);
		~StyledTextBlock();

		void setStyledChar(const StyledChar& sc, const int& x, const int& y);
		void setStyle(const  TextStyle& style, const int& x, const int& y);
		void setChar(const       char& chars, const int& x, const int& y);

		void fillStyledChar(const StyledChar& styledChar, const int& x1, const int& y1, const int& x2, const int& y2);
		void fillStyle(const  TextStyle& style, const int& x1, const int& y1, const int& x2, const int& y2);
		void fillChar(const       char& chars, const int& x1, const int& y1, const int& x2, const int& y2);

		void putStr(const  std::string& str, const int& x, const int& y);
		//void putSstr(const StyledString& sstr, const int& x, const int& y);

		void drawBox(const TextStyle& style, int x1, int y1, int x2, int y2);

		void blit(const int& x, const int& y);
		void blit(StyledTextBlock& target, const int& x, const int& y);
	};

}