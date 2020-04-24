/*

Logging module
Written by Robert Christensen

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

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Logger
{
private:
	std::vector<std::string> buffer;

public:
	Logger& operator<<(const std::string& in);
	friend std::ostream& operator<<(std::ostream& out, const Logger& logger);

	void flush(std::ostream& out);
	void writeTo(const std::string& path);

	sf::StyledTextBlock renderTail(const int& w, const int& h) const;
};