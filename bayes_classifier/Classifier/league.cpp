#include "league.h"

league::league() {
	for (int i = 0; i < 100; i++) {
		avg.stats[i] = 0;
		standardDev.stats[i] = 0;
	}
	deviationFactor = 2;
}

void league::fillLeague(std::string file)
{
	std::ifstream instream;
	std::string line;
	instream.open(file);
	std::getline(instream, line);
	for (int i = 0; i < 30; i++) {
		std::getline(instream, line);
		teams[i].fillTeam(line);
	}
	instream.close();
}

void league::combineStats(league league2) {
	for (int i = 0; i < 30; i++) {
		int count = 0;
		for (int j = 0; j < 30; j++) {
			if (league2.teams[j].name == teams[i].name)
				for (int k = 0; k < 100; k++) {
					if (teams[i].stats[k] <= 0) {
						teams[i].stats[k] = league2.teams[j].stats[count];
						count++;
					}
				}
		}
	}
}

void league::calculateAvg() {
	for (int i = 0; i < 100; i++) {
		for (int k = 0; k < 30; k++) {
			avg.stats[i] += teams[k].stats[i];
		}
		avg.stats[i] /= 30;
	}
}

void league::calculateStdDev() {
	for (int i = 0; i < 100; i++) {
		for (int k = 0; k < 30; k++) {
			standardDev.stats[i] += pow(teams[k].stats[i] - avg.stats[i], 2);
		}
		standardDev.stats[i] /= 30;
		standardDev.stats[i] = sqrt(standardDev.stats[i]);
	}
}

