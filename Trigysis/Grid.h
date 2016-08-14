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
#include "TestPipeline.h"

#define GRID_FIGURE_WIDTH 9
#define GRID_FIGURE_HEIGHT 9
#define BOARD_SIZE 240
#define BOARD_INTERVAL 60

#define INITIAL_PROB 100
#define INITIAL_MORALE 100


class Grid {
public:
	Grid(BasicInterface* super);
	~Grid();

	void setBoard(BasicInterface* super);

protected:
private:
	inline void generateFig(BasicInterface* super,int i, int j){ list.at(fmanager->FigureToDrop(list))->createFigure(super, i, j); };


	
	FigureManager *fmanager;

	std::vector<std::vector<int> > net;
	std::vector<FigureB*> list;
	FigureB *figure0;
	FigureB *figure1;
	FigureB *figure2;
	FigureB *figure3;
	FigureB *figure4;
	FigureB *figure5;

};

#endif