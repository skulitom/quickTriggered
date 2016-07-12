#ifndef Turns_H
#define Turns_H


/*
Abstract Class that could be used to retrieve
data from either current game or saved game
*/

class Turns {
public:
	Turns(int maxTurns=0);
	~Turns();
protected:
private:
	int numberOfTurns;
	int maxTurns;
};

#endif
