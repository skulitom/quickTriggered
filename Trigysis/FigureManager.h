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

class FigureManager {

public:
	FigureManager();
	~FigureManager();

	int FigureToDrop(std::vector<FigureB*> list);

	void analyseAction(FigureB *figure, int action);

protected:
private:
	void holocaust(FigureB *figure);
	void femWave(FigureB *figure);
	void iHaveADream(FigureB *figure);
	void ChildPolicy(FigureB *figure);
	void Jihad(FigureB *figure);

	int process;


};

#endif
