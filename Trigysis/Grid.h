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


class Grid {
public:
	Grid(BasicInterface* super);
	~Grid();

	void setBoard(BasicInterface* super);

	void deleteAt(int x, int y);
	void update();

protected:
private:
	void generateFig(BasicInterface* super, int i, int j);	
	FigureManager *fmanager;

	std::vector<std::vector<FigureB*> > *net;
	FigureB *fig;



};

#endif