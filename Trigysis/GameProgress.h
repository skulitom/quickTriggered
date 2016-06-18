#ifndef GameProgress_H
#define GameProgress_H

#include "Progress.h"

class GameProgress : Progress{

public:
	GameProgress(int storyPoint=0, int location=0);
	~GameProgress();
	void setLocation(int location);
	int getLocation();
	void setStoryPoint(int storyPoint);
	int getStoryPoint();
protected:
private:
	int location;
	int storyPoint;

};

#endif