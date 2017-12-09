#include<string>
#include <sstream>

#ifndef TEAM_H
#define TEAM_H

class team 
{
public:
	void fillTeam(std::string);
	bool isFloat(std::string);
	std::string name;
	float stats[100];
};

#endif
