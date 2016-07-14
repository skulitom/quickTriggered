#ifndef FigureDrop_H
#define FigureDrop_H

#include <exception>
#include <array>
#include <time.h> 
#include <stdlib.h>
#include "FigureB.h"


#define HOLOCAUST 0
#define FEMINIST 1
#define I_HAVE_A_DREAM 2
#define CHILD_POLICY 3
#define JIHAD 4

#define HOLOCAUST_PROB 50
#define FEMINIST_PROB 200
#define I_HAVE_A_DREAM_PROB 50
#define CHILD_POLICY_PROB 50
#define JIHAD_PROB 50

class FigureDrop{

public:
	FigureDrop();
	~FigureDrop();

	int FigureToDrop(FigureB *figure0, FigureB *figure1, FigureB *figure2, FigureB *figure3, FigureB *figure4, FigureB *figure5);

	void analyseAction(FigureB *figure, int action);

protected:
private:
	void holocaust(FigureB *figure);
	void femWave(FigureB *figure);
	void iHaveADream(FigureB *figure);
	void ChildPolicy(FigureB *figure);
	void Jihad(FigureB *figure);


};

#endif