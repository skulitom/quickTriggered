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
#define GRID_FIGURE_HEIGHT 9

#define INITIAL_PROB 100
#define INITIAL_MORALE 100

#define BOARD_INTERVAL 60
#define BOARD_SIZE 240


class Grid {
public:
	Grid(BasicInterface* super);
	~Grid();

	void setBoard(BasicInterface* super);

	void insertAt(int x, int y, FigureB* fig);
	void deleteAt(int x, int y);
	bool compareAt(int x1, int y1, int x2, int y2);
	virtual void Update(BasicInterface* super);
	void updatePositions(BasicInterface* super);

protected:
private:
	void generateFig(BasicInterface* super, int i, int j);
	void generateFig(BasicInterface* super, int i, int j, bool round);
	FigureManager *fmanager;

	std::vector<std::vector<FigureB*> > *net;
	FigureB *fig;



};

#endif