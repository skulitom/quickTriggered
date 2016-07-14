#ifndef Grid_H
#define Grid_H

#include <vector>
#include "FigureB.h"
#include "FigureDrop.h"

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

protected:
private:

	void setBoard(BasicInterface* super);
	void createFigure(BasicInterface* super,Figure *fig, int x, int y);
	Figure getGUIfigure(FigureB *figureB);

	
	FigureDrop *drop = new FigureDrop();

	std::vector<std::vector<int> > net;
	FigureB *figure0 = new FigureB(MEXICANS,INITIAL_PROB,INITIAL_MORALE);
	FigureB *figure1 = new FigureB(JEWS, INITIAL_PROB, INITIAL_MORALE);
	FigureB *figure2 = new FigureB(WOMEN, INITIAL_PROB, INITIAL_MORALE);
	FigureB *figure3 = new FigureB(BLACK, INITIAL_PROB, INITIAL_MORALE);
	FigureB *figure4 = new FigureB(ASIAN, INITIAL_PROB, INITIAL_MORALE);
	FigureB *figure5 = new FigureB(WHITE_SUPREME, INITIAL_PROB, INITIAL_MORALE);

	Figure *fig0;
	Figure *fig1;
	Figure *fig2;
	Figure *fig3;
	Figure *fig4;
	Figure *fig5;
};

#endif