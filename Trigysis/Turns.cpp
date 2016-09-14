#include "Turns.h"
/*
	Turns uses timer to manage in game turns
*/

Turns::Turns(float maxTurns, float maxTime)
{
	this->maxTurns = maxTurns;
	this->maxTime = maxTime;
	this->numberOfTurns = 0;
	this->sTime = 0;
	this->eTime = 0;
	this->endedTurn = false;
	this->endGame = false;
	this->timer = new D3DAPPTIMER(SD_TIMESCALE);
	this->timer->Reset();
	this->running = false;

}

void Turns::Update()
{
	timer->Tick();
	if (!running)
	{
		startClock();
		running = true;
	}
	if (endedTurn)
	{
		if (numberOfTurns >= maxTurns)
		{
			this->endGame = true;
		}
		else
		{
			startClock();
			this->endedTurn = false;
		}
	}
	else if (getTime() >= this->maxTime)
	{
		// if run out of time, end turn
		endTurn();
	}
}

void Turns::endTurn()
{
	this->endedTurn = true;
	this->numberOfTurns++;
}

void Turns::startClock()
{
	this->sTime = this->timer->GetTotalTime();
}

void Turns::stopClock()
{
	this->eTime = this->timer->GetTotalTime();
}

int Turns::getTime()
{
	stopClock();
	int currentTime = int(this->eTime - this->sTime + 0.5);
	return currentTime;
}

Turns::~Turns()
{
	delete timer;
}