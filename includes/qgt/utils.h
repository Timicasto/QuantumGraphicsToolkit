#ifndef QUANTUMGRAPHICSTOOLKIT_UTILS_H
#define QUANTUMGRAPHICSTOOLKIT_UTILS_H

#include <string>
#include <vector>
#include <regex>

std::vector<std::string> split(const std::string& str, const std::string& splitter) {
	std::regex re(splitter);
	std::sregex_token_iterator first {str.begin(), str.end(), re, -1}, last;
	return {first, last};
}

#endif //QUANTUMGRAPHICSTOOLKIT_UTILS_H
