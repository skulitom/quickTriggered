#include "Turns.h"

Turns::Turns(unsigned int maxTurns, unsigned long maxTime)
{
	this->maxTurns = maxTurns;
	this->maxTime = maxTime;
	this->numberOfTurns = 0;
	this->reset = true;
	this->running = false;
	this->sTime = 0;
	this->eTime = 0;
	this->isEndTurn = false;
	this->endGame = false;

	startClock();
}

void Turns::Update()
{
	if (isEndTurn)
	{
		if (numberOfTurns >= maxTurns)
		{
			this->endGame = true;
		}
		else
		{
			this->numberOfTurns++;
			this->isEndTurn = false;
			resetClock();
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
	this->numberOfTurns++;
}

void Turns::startClock()
{
	if (!running)
	{
		if (this->reset)
		{
			this->sTime = (unsigned long)clock();
		}
		else
		{
			this->sTime -= this->eTime - (unsigned long)clock();
		}
		this->running = true;
		this->reset = false;
	}

}

void Turns::stopClock()
{
	if (running)
	{
		eTime = (unsigned long)clock();
		running = false;
	}
}

void Turns::resetClock()
{
	bool wasRunning = running;
	if (wasRunning)
		stopClock();
	this->reset = true;
	this->sTime = 0;
	this->eTime = 0;
	if (wasRunning)
		startClock();

}

unsigned long Turns::getTime()
{
	if (this->running)
		return ((unsigned long)clock() - this->sTime) / CLOCKS_PER_SEC;
	else
		return this->eTime - this->sTime;
}

Turns::~Turns()
{
	stopClock();
}