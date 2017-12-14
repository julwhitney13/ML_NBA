#include "team.h"

bool team::isFloat(std::string myString) {
	std::istringstream iss(myString);
	float f;
	iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
						  // Check the entire string was consumed and if either failbit or badbit is set
	return iss.eof() && !iss.fail();
}

void team::fillTeam(std::string info) {
	int index = info.find(',', 0);
	int end = info.find(',', index + 1);
	name = info.substr(index + 1, end - index - 1);
	if (name.back() == '*')
		name = name.substr(0, name.size() - 1);
	index = info.find(',', end);
	std::string line;
	for (int i = 0; i < sizeof(stats)/sizeof(float); i++) {
		end = info.find(',', index + 1);
		line = info.substr(index + 1, end - index - 1);
		if(isFloat(line))
			stats[i] = std::stof(line);
		index = end;
		if (end == -1)
			break;
	}
}
