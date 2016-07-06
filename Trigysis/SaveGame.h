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
	inline void saveStoryPoint(int storyPoint, std::string fileName){ save(storyPoint, fileName, "stroryPoint"); }
	inline void saveLocation(int location, std::string fileName){ save(location,fileName,"location"); }
	void save(int num, std::string fileName, std::string name);
	const std::string fileType = ".txt";
	FileManager *FM;
};

#endif