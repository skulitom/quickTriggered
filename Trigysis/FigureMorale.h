#ifndef FigureMorale_H
#define FigureMorale_H

#include "FigureB.h"

#define HOLOCAUST_MORALE 1.2
#define FEMINIST_MORALE 2
#define I_HAVE_A_DREAM_MORALE 4
#define JIHAD_MORALE 1.5

class FigureMorale{

public:
	FigureMorale();
	~FigureMorale();

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