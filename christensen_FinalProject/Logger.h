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