#ifndef Turns_H
#define Turns_H

#include <conio.h>
#include <time.h>

#define SD_MAX_TURNS 10
#define SD_MAX_TIME 40


/*
Turns keeps track of the time and the current
Turn in game
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
	inline bool isEndGame(){ return this->endGame; }
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
	bool endGame;
};

#endif
