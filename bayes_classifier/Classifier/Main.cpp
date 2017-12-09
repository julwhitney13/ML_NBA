#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include "team.h"
#include "game.h"
#include "naiveBayes.h"

void combineStats(team *league1, team *league2, int size)
{	
	for (int i = 0; i < 30; i++) {
		int count = 0;
		for (int j = 0; j < 30; j++) {
			if (league2[j].name == league1[i].name)
				for (int k = 0; k < size; k++) {
					if (league1[i].stats[k] <= 0) {
						league1[i].stats[k] = league2[j].stats[count];
						count++;
					}
				}
		}
	}
}

void fillStats(std::string file, team *league) {
	std::ifstream instream;
	std::string line;
	instream.open(file);
	std::getline(instream, line);
	for (int i = 0; i < 30; i++) {
		std::getline(instream, line);
		league[i].fillTeam(line);
	}
	instream.close();
}

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
	team league[30];
	team leagueOpp[30];
	team leagueMisc[30];
	game games[2000];
	//fillStats("TeamStats_16-17.csv", league);
	//fillStats("OpponentStats_16-17.csv", leagueOpp);
	fillStats("MiscStats_16-17.csv", leagueMisc);
	//combineStats(league, leagueOpp, sizeof(league[0].stats)/sizeof(float));
	//combineStats(league, leagueMisc, sizeof(league[0].stats) / sizeof(float));

	fillGames("GameResults_16-17.csv", games);
	naiveBayes b(sizeof(league[0].stats) / sizeof(float));
	b.train(leagueMisc, games, sizeof(league[0].stats) / sizeof(float));
	
	team league2[30];
	team league2Opp[30];
	team league2Misc[30];
	//fillStats("TeamStats_15-16.csv", league2);
	//fillStats("OpponentStats_15-16.csv", league2Opp);
	fillStats("MiscStats_14-15.csv", league2Misc);
	//combineStats(league2, league2Opp, sizeof(league[0].stats) / sizeof(float));
	//combineStats(league2, league2Misc, sizeof(league[0].stats) / sizeof(float));

	game games2[2000];
	fillGames("GameResults_14-15.csv", games2);
	b.train(league2Misc, games2, sizeof(league[0].stats) / sizeof(float));
	//b.finalizeTraining(sizeof(league[0].stats) / sizeof(float));

	team league3[30];
	team league3Opp[30];
	team league3Misc[30];
	//fillStats("TeamStats_14-15.csv", league3);
	//fillStats("OpponentStats_14-15.csv", league3Opp);
	fillStats("MiscStats_15-16.csv", league3Misc);
	//combineStats(league3, league3Opp, sizeof(league[0].stats) / sizeof(float));
	//combineStats(league3, league3Misc, sizeof(league[0].stats) / sizeof(float));

	game games3[2000];
	fillGames("GameResults_15-16.csv", games3);
	//b.train(league3, games3, sizeof(league[0].stats) / sizeof(float));
	b.finalizeTraining(sizeof(league[0].stats) / sizeof(float));
	b.validate(league3Misc, games3, sizeof(league[0].stats) / sizeof(float));
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