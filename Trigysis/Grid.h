#ifndef Grid_H
#define Grid_H

#include <vector>

#define GRID_FIGURE_WIDTH 9
#define GRID_FIGURE_HEIGHT 9
#define BOARD_SIZE 240
#define BOARD_INTERVAL 60


/*
Abstract Class that could be used to retrieve
data from either current game or saved game
*/

class Grid {
public:
	Grid();
	~Grid();

protected:
private:
	std::vector<std::vector<int> > net;
};

#endif