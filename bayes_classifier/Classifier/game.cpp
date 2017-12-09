#include "game.h"

game::game(std::string info) {
	int index = info.find(',', 0);
	index = info.find(',', index + 1);
	int end = info.find(',', index + 1);
	awayTeam = info.substr(index + 1, end - index - 1);
	index = end;
	end = info.find(',', index + 1);
	int awayScore = std::stoi(info.substr(index + 1, index - end - 1));
	index = end;
	end = info.find(',', index + 1);
	homeTeam = info.substr(index + 1, end - index - 1);
	index = end;
	end = info.find(',', index + 1);
	int homeScore = std::stoi(info.substr(index + 1, index - end - 1));
	if (homeScore - awayScore > 0)
		winner = true;
	else
		winner = false;
}

game::game() {}