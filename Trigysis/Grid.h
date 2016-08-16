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

protected:
private:
	void generateFig(BasicInterface* super, int i, int j);


	
	FigureManager *fmanager;

	std::vector<std::vector<FigureB*> > *net;
	std::vector<FigureB*> listB;
	FigureB *figure0;
	FigureB *figure1;
	FigureB *figure2;
	FigureB *figure3;
	FigureB *figure4;
	FigureB *figure5;


};

#endif