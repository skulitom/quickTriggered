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

#define INDEX_OF_VP 2


class PrimaryGame {
public:
	PrimaryGame(BasicInterface* super);
	~PrimaryGame();

	virtual void Update();
	void init();
	void setBoard();

protected:
private:
	void continueGame();

	BasicInterface* super;
	Grid* grid;
	Turns* turns;
	float localTime;
	bool gameWon;

};

#endif