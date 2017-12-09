#ifndef GAME_H
#define GAME_H

#include<string>
#include "team.h"

class game 
{
public:
	game(std::string);
	game();
	std::string homeTeam;
	std::string awayTeam;
	bool winner; //true = home, false = away
};

#endif