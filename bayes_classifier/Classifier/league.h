#ifndef LEAGUE_H
#define LEAGUE_H

#include "team.h"
#include <string>
#include <fstream>

class league {
public:
	team teams[30];
	team avg;
	team standardDev;
	int deviationFactor;
	league();
	void fillLeague(std::string);
	void combineStats(league);
	void calculateAvg();
	void calculateStdDev();
};

#endif // !LEAGUE_H
