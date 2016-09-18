#ifndef GameProgress_H
#define GameProgress_H

#include "Progress.h"
#include "Crypter.h"
#include <string>

class GameProgress : Progress{

public:
	GameProgress(int storyPoint=0, int location=0);
	~GameProgress();
	void Update();
	void setLocation(int location);
	int getLocation();
	void setStoryPoint(int storyPoint);
	int getStoryPoint();
protected:
private:
	int location;
	int storyPoint;
	std::size_t getFound(std::string& name);

	Crypter *crypt;
	std::string saveFile;

	// string names{
	std::string locationS;
	std::string storyPointS;
	//}

};

#endif