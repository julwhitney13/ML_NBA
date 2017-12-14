#include "team.h"
#include "game.h"
#include "league.h"
#include <vector>
#include<cmath>
#include<iostream>

class naiveBayes 
{
public:
	double yesPosStats[100];
	double yesAboveStats[100];
	double yesBelowStast[100];
	double yesNegStats[100];
	double noPosStats[100];
	double noAboveStats[100];
	double noBelowStats[100];
	double noNegStats[100];
	int yesCount, noCount;
	double pYes, pNo;

	naiveBayes(int size);
	void train(league, game *, int size);
	void validate(league, game *, int size);
	void finalizeTraining(int size);
	bool predict(league, int size);
	void findBest(league, game *);
	void findTeam(std::string homeName, std::string awayName, league, int &home, int &away);
	bool yesNO(league, int size, int homeStats, int awayStats);
};
