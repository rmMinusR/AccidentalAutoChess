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
