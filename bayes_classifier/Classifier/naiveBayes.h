#include "team.h"
#include "game.h"
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
	double avgDifference[100];
	double noPosStats[100];
	double noAboveStats[100];
	double noBelowStats[100];
	double noNegStats[100];
	int yesCount, noCount;
	double pYes, pNo;

	naiveBayes(int size);
	void train(team *, game *, int size);
	void validate(team *, game *, int size);
	void finalizeTraining(int size);
	bool predict(team *, int size);
	void findBest(team *, game *);
	void findTeam(std::string homeName, std::string awayName, team *league, int &home, int &away);
	bool yesNO(team *league, int size, int homeStats, int awayStats);
};
