#ifndef PrimaryGame_H
#define PrimaryGame_H

#include <vector>
#include "FigureB.h"
#include "FigureManager.h"

#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
#include "BasicInterface.h"
#include "GUIFigures.h"
#include "Basic2DDraw.h"
#include "Files.h"
#include "Grid.h"
#include "Turns.h"


class PrimaryGame {
public:
	PrimaryGame();
	~PrimaryGame();

	virtual void Update(BasicInterface* super);
	void init(BasicInterface* super);
	void setBoard(BasicInterface* super);

protected:
private:
	Grid* grid;
	Turns* turns;


};

#endif