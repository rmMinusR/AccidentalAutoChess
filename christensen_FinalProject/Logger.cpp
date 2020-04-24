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

#include "Logger.h"

Logger& Logger::operator<<(const std::string& in)
{
	std::string line = "";
	for (int i = 0; i < in.length(); i++) {
		char c = in.at(i);
		if (c != '\n') {
			line = line + in.at(i);
		}
		else {
			buffer.push_back(line);
			line = "";
		}
	}
	if (line.length() != 0) buffer.push_back(line);

	return *this;
}

void Logger::flush(std::ostream& out)
{
	for (std::string line : buffer) out << line << std::endl;
}

void Logger::writeTo(const std::string& path)
{
	std::ofstream fout(path);

	flush(fout);

	fout.flush();
	fout.close();
}

sf::StyledTextBlock Logger::renderTail(const int& w, const int& h) const
{
	sf::StyledTextBlock out(w, h);

	for (int i = 0; i < 50 && buffer.size() > i; i++) {
		out.putStr(buffer[buffer.size()-1-i], 0, h-1-i);
	}

	return out;
}

std::ostream& operator<<(std::ostream& out, const Logger& logger)
{
	for (std::string line : logger.buffer) {
		out << line << std::endl;
	}
	return out;
}
