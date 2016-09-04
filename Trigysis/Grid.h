#ifndef Grid_H
#define Grid_H

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

#define GRID_FIGURE_WIDTH 9
#define GRID_FIGURE_HEIGHT GRID_FIGURE_WIDTH

#define INITIAL_PROB 100
#define INITIAL_MORALE 100

#define BOARD_INTERVAL 60
#define BOARD_SIZE ((GRID_FIGURE_WIDTH-1)*BOARD_INTERVAL)/2

//((GRID_FIGURE_WIDTH - 1)*BOARD_INTERVAL) / 2


class Grid {
public:
	Grid();
	~Grid();

	void setBoard(BasicInterface* super);

	void insertAt(int x, int y, FigureB* fig);
	void smartInsertAt(int x, int y,Vector2d originalPos, FigureB* fig);
	void deleteAt(int x, int y);
	bool compareAt(int x1, int y1, int x2, int y2);
	virtual void Update(BasicInterface* super);
	void SecondRoundLogic(BasicInterface* super);
	void FirstRoundLogic(BasicInterface* super);

protected:
private:
	void generateFig(BasicInterface* super, int i, int j);
	void generateFig(BasicInterface* super, int i, int j, bool round);
	void breakIt(int i, int j);
	void moveFig(int i, int j, BasicInterface* super);
	FigureManager *fmanager;

	std::vector<std::vector<FigureB*> > *net;
	FigureB *fig;



};

#endif