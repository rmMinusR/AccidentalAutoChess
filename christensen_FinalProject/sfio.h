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

#pragma once

#include "sfgr.h"


#include <iostream>
#include <string>

namespace sf {

	char cquerych();
	char cquerycht(float timeout);

	void csetcurpos(unsigned int x, unsigned int y);
	int cgetw();
	int cgeth();

	void csetcurvis(bool visiblity);

	void cfill(char c, int x1, int y1, int x2, int y2);
	void cdrawbox(int x1, int y1, int x2, int y2);

	void cclear();

	void showDialog(std::string str, int x, int y);

}