#include "naiveBayes.h"

naiveBayes::naiveBayes(int size) {
	yesCount = 0;
	noCount = 0;
	for (int k = 0; k < size; k++) {
		yesPosStats[k] = 0;
		noPosStats[k] = 0;
		avgDifference[k] = 0;
		yesAboveStats[k] = 0;
		noAboveStats[k] = 0;
		noBelowStats[k] = 0;
		noNegStats[k] = 0;
		yesBelowStast[k] = 0;
		yesNegStats[k] = 0;
	}
}

void naiveBayes::finalizeTraining(int size) {
	for (int k = 0; k < size; k++) {
		yesPosStats[k] = yesPosStats[k] / yesCount;
		noPosStats[k] = noPosStats[k] / noCount;
		yesAboveStats[k] = yesAboveStats[k] / yesCount;
		yesBelowStast[k] = yesBelowStast[k] / yesCount;
		yesNegStats[k] = yesNegStats[k] / yesCount;
		noNegStats[k] = noNegStats[k] / noCount;
		noBelowStats[k] = noBelowStats[k] / noCount;
		noAboveStats[k] = noAboveStats[k] / noCount;
		avgDifference[k] = avgDifference[k] / (yesCount + noCount);
	}
}

void naiveBayes::findTeam(std::string homeName, std::string awayName, team *league, int &home, int &away) {
	for (int j = 0; j < 30; j++) {
		if (league[j].name == homeName)
			home = j;
		else if (league[j].name == awayName)
			away = j;
	}
}

void naiveBayes::train(team *league, game *games, int size) {
	int homeStats;
	int awayStats;
	int count = 0;
	float tempAvgDiff[2000];
	for (int i = 0; i < 2000; i++) {
		if (games[i].awayTeam == "")
			break;
		findTeam(games[i].homeTeam, games[i].awayTeam, league, homeStats, awayStats);
		count++;
		for (int k = 0; k < size; k++) {
			avgDifference[k] += abs(league[homeStats].stats[k] - league[awayStats].stats[k]);
		}
	}
	for (int i = 0; i < 2000; i++) {
		tempAvgDiff[i] = avgDifference[i] / (count + yesCount + noCount);
	}
	for (int i = 0; i < 2000; i++) {
		if (games[i].awayTeam == "")
			break;
		findTeam(games[i].homeTeam, games[i].awayTeam, league, homeStats, awayStats);
		if (games[i].winner) {
			yesCount++;
			for (int k = 0; k < size; k++) {
				if (league[homeStats].stats[k] - league[awayStats].stats[k] > tempAvgDiff[k])
					yesAboveStats[k]++;
				else if (league[homeStats].stats[k] - league[awayStats].stats[k] > 0)
					yesPosStats[k]++;
				else if (league[homeStats].stats[k] - league[awayStats].stats[k] < -1 * tempAvgDiff[k])
					yesBelowStast[k]++;
				else
					yesNegStats[k]++;
			}
		}
		else {
			noCount++;
			for (int k = 0; k < size; k++) {
				if (league[awayStats].stats[k] - league[homeStats].stats[k] > tempAvgDiff[k])
					noAboveStats[k]++;
				else if (league[awayStats].stats[k] - league[homeStats].stats[k] > 0)
					noPosStats[k]++;
				else if (league[awayStats].stats[k] - league[homeStats].stats[k] < -1 * tempAvgDiff[k])
					noBelowStats[k]++;
				else
					noNegStats[k]++;
			}
		}
	}
	pYes = yesCount;
	pYes = pYes / (yesCount + noCount);
	pNo = 1 - pYes;
}

void naiveBayes::validate(team *league, game *games, int size) {
	int homeStats;
	int awayStats;
	int right = 0, wrong = 0;
	for (int i = 0; i < 2000; i++) {
		if (games[i].awayTeam == "")
			break;
		findTeam(games[i].homeTeam, games[i].awayTeam, league, homeStats, awayStats);
		bool yes = yesNO(league, size, homeStats, awayStats);
		if ((games[i].winner && yes) || (!games[i].winner && !yes))
			right++;
		else
			wrong++;
	}
}

bool naiveBayes::yesNO(team *league, int size, int home, int away) {
	double probYes = 1, probNo = 1;
	for (int j = 0; j < size; j++) {
		if (league[home].stats[j] - league[away].stats[j] > avgDifference[j]) {
			if (yesAboveStats[j] > 0)
				probYes = probYes * yesAboveStats[j];
			if (noBelowStats[j] > 0)
				probNo = probNo * noBelowStats[j];
		}
		else if (league[away].stats[j] - league[home].stats[j] > avgDifference[j]) {
			if (yesBelowStast[j] > 0)
				probYes = probYes * yesBelowStast[j];
			if (noAboveStats[j] > 0)
				probNo = probNo * noAboveStats[j];
		}
		else if (league[home].stats[j] - league[away].stats[j] > 0) {
			if (yesPosStats[j] > 0)
				probYes = probYes * yesPosStats[j];
			if (noNegStats[j] > 0)
				probNo = probNo * noNegStats[j];
		}
		else {
			if (yesNegStats[j] > 0)
				probYes = probYes * yesNegStats[j];
			if (noPosStats[j] > 0)
				probNo = probNo * noPosStats[j];
		}
	}
	probYes = probYes * pYes;
	probNo = probNo * pNo;
	probYes = probYes / (probYes + probNo);
	probNo = 1 - probYes;
	if (probYes > probNo)
		return true;
	else
		return false;
}

bool naiveBayes::predict(team *league, int size) {
	float probYes = 1, probNo = 1;
	int home, away;
	std::string homeTeam;
	std::string awayTeam;
	std::cout << "Enter Home Team: ";
	std::getline (std::cin, homeTeam);
	std::cout << "Enter Away Team: ";
	std::getline (std::cin, awayTeam); 
	findTeam(homeTeam, awayTeam, league, home, away);
	if (yesNO(league, size, home, away))
		return true;
	else return false;
}

void naiveBayes::findBest(team *league, game* games) {
	float statPercent[100];
	float right, wrong;
	for (int i = 0; i < 100; i++) {
		int homeStats;
		int awayStats;
		right = 0, wrong = 0;
		for (int j = 0; j < 2000; j++) {
			if (games[j].awayTeam == "")
				break;
			findTeam(games[j].homeTeam, games[j].awayTeam, league, homeStats, awayStats);
			if ((games[j].winner && league[homeStats].stats[i] > league[awayStats].stats[i]) 
				|| (!games[j].winner && league[awayStats].stats[i] > league[homeStats].stats[i]))
				right++;
			else
				wrong++;
		}
		statPercent[i] = right / (right + wrong);
		if (statPercent[i] < 0.5 && statPercent[i] > 0)
			statPercent[i] = 1 - statPercent[i];
	}
	float max = 0, maxIndex = 0;
	for (int i = 0; i < 100; i++) {
		if (statPercent[i] > max) {
			max = statPercent[i];
			maxIndex = i;
		}
	}
}