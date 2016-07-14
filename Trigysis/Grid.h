#ifndef Grid_H
#define Grid_H

#include <vector>
#include "FigureB.h"
#include "FigureDrop.h"

#define GRID_FIGURE_WIDTH 9
#define GRID_FIGURE_HEIGHT 9
#define BOARD_SIZE 240
#define BOARD_INTERVAL 60


class Grid {
public:
	Grid();
	~Grid();

protected:
private:
	std::vector<std::vector<int> > net;
	FigureB *figure0;
	FigureB *figure1;
	FigureB *figure2;
	FigureB *figure3;
	FigureB *figure4;
	FigureB *figure5;
};

#endif