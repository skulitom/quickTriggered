#ifndef Progress_H
#define Progress_H


/*
Abstract Class that could be used to retrieve 
data from either current game or saved game
*/

class Progress{
public:
	virtual int getLocation() = 0;
	virtual int getStoryPoint() = 0;
};

#endif