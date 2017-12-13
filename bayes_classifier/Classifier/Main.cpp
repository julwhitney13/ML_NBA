#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include "team.h"
#include "game.h"
#include "naiveBayes.h"
#include "league.h"

void fillGames(std::string file, game *games) {
	std::ifstream instream;
	std::string line;
	instream.open(file);
	std::getline(instream, line);
	int count = 0;
	while (std::getline(instream, line)) {
		games[count] = game(line);
		count++;
	}
	instream.close();
}

int main()
{
	league league1;
	league league1Opp;
	league league1Misc;
	game games[2000];
	league1.fillLeague("TeamStats_14-15.csv");
	league1Opp.fillLeague("OpponentStats_14-15.csv");
	league1Misc.fillLeague("MiscStats_14-15.csv");
	league1.combineStats(league1Opp);
	league1.combineStats(league1Misc);
	league1.calculateAvg();
	league1.calculateStdDev();

	fillGames("GameResults_14-15.csv", games);
	naiveBayes b(100);
	b.train(league1, games, 100);
	
	league league2;
	league league2Opp;
	league league2Misc;
	league2.fillLeague("TeamStats_16-17.csv");
	league2Opp.fillLeague("OpponentStats_16-17.csv");
	league2Misc.fillLeague("MiscStats_16-17.csv");
	league2.combineStats(league2Opp);
	league2.combineStats(league2Misc);
	league2.calculateAvg();
	league2.calculateStdDev();

	game games2[2000];
	fillGames("GameResults_16-17.csv", games2);
	b.train(league2, games2, 100);

	league league3;
	league league3Opp;
	league league3Misc;
	league3.fillLeague("TeamStats_15-16.csv");
	league3Opp.fillLeague("OpponentStats_15-16.csv");
	league3Misc.fillLeague("MiscStats_15-16.csv");
	league3.combineStats(league3Opp);
	league3.combineStats(league3Misc);
	league3.calculateAvg();
	league3.calculateStdDev();

	game games3[2000];
	fillGames("GameResults_15-16.csv", games3);
	//b.train(league3, games3, sizeof(league[0].stats) / sizeof(float));
	b.finalizeTraining(100);
	b.validate(league3, games3, 100);
	//b.findBest(league3, games3);

	/*team league4[30];
	team league4Opp[30];
	team league4Misc[30];
	fillStats("TeamStats_17-18.csv", league4);
	fillStats("OpponentStats_17-18.csv", league4Opp);
	//fillStats("MiscStats_17-18.csv", league4Misc);
	combineStats(league4, league4Opp, sizeof(league[0].stats) / sizeof(float));
	combineStats(league4, league4Misc, sizeof(league[0].stats) / sizeof(float));

	//std::vector<game> games4;
	//fillGames("GameResults_16-17.csv", games4);
	b.predict(league4, sizeof(league[0].stats) / sizeof(float));*/

	return 0;
}