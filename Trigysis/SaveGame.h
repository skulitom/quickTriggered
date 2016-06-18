#ifndef SaveGame_H
#define SaveGame_H

#include "Progress.h"
#include "GameProgress.h"
#include <string>
#include <fstream>
#include "Files.h"

class SaveGame : Progress{
public:
	SaveGame(GameProgress *currentProgress, std::string fileName);
	~SaveGame();
	int getLocation();
	int getStoryPoint();
protected:
private:
	void saveAll(GameProgress *currentProgress, std::string fileName);
	void saveStoryPoint(int storyPoint, std::string fileName);
	void saveLocation(int location, std::string fileName);
	const std::string fileType = ".txt";
};

#endif