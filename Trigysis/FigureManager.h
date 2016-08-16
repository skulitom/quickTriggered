#ifndef FigureManager_H
#define FigureManager_H

#include <exception>
#include <array>
#include <time.h> 
#include <stdlib.h>
#include "FigureB.h"

#define HOLOCAUST_PROB 1.5
#define FEMINIST_PROB 3
#define I_HAVE_A_DREAM_PROB 1.5
#define CHILD_POLICY_PROB 1.5
#define JIHAD_PROB -1.5

#define HOLOCAUST_MORALE 1.2
#define FEMINIST_MORALE 2
#define I_HAVE_A_DREAM_MORALE 4
#define JIHAD_MORALE -1.5

#define NUM_TYPES 6

class FigureManager {

public:
	FigureManager();
	~FigureManager();

	int FigureToDrop();
	void analyseAction(int type, int action);

	inline void setProb(int type, int prob){ this->prob.at(type) = prob; }
	inline void setMorale(int type, int morale){ this->morale.at(type) = morale; }

protected:
private:
	void holocaust(int type);
	void femWave(int type);
	void iHaveADream(int type);
	void ChildPolicy(int type);
	void Jihad(int type);

	std::vector<int> prob;
	std::vector<int> morale;

};

#endif
