#ifndef Turns_H
#define Turns_H

#include <conio.h>
#include <time.h>
#include "Timer.h"

#define SD_MAX_TURNS 10
#define SD_MAX_TIME 40
#define SD_TIMESCALE 1


/*
Turns keeps track of the time and the current
Turn in game
*/

class Turns {
public:
	Turns(float maxTurns=0, float maxTime=0);
	~Turns();												
	virtual void Update();									
	void setMaxTurns(float turns);		
	inline bool isEndGame(){ return this->endGame; }
	inline bool isEndTurn(){ return this->endedTurn; }
	inline int getTurn(){ return this->numberOfTurns; }
	int getTime();								
															
protected:													
private:													
	void startClock();										
	void stopClock();											
	bool endTime(float seconds);					
	void endTurn();											
															
	int numberOfTurns;									
	int maxTurns;											
	float sTime;											
	float eTime;											
	float maxTime;											
	bool endedTurn;											
	bool endGame;	
	bool running;
	D3DAPPTIMER *timer;										
};															

#endif
