#ifndef Turns_H
#define Turns_H

#include <conio.h>
#include <time.h>


/*
Abstract Class that could be used to retrieve
data from either current game or saved game
*/

class Turns {
public:
	Turns(unsigned int maxTurns=0, unsigned long maxTime=0);
	~Turns();
	virtual void Update();
	void setMaxTurns(int turns);
	void startClock();
	void stopClock();
	void resetClock();
	inline bool runningClock(){ return this->running; };
	bool endTime(unsigned long seconds);
	void endTurn();
	unsigned long getTime();

protected:
private:
	unsigned int numberOfTurns;
	unsigned int maxTurns;
	bool reset;
	bool running;
	unsigned long sTime;
	unsigned long eTime;
	unsigned long maxTime;
	bool isEndTurn;
};

#endif
