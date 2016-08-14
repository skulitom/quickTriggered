#include "Grid.h"

struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

Grid::Grid(BasicInterface* super)
{
	this->fmanager = new FigureManager();

	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		std::vector<int> hold;
		hold.push_back(0);
		for(int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			this->net.push_back(hold);
		}
		hold.clear();
	}

	figure0 = new FigureB(MEXICANS, INITIAL_PROB, INITIAL_MORALE);
	figure1 = new FigureB(JEWS, INITIAL_PROB, INITIAL_MORALE);
	figure2 = new FigureB(WOMEN, INITIAL_PROB, INITIAL_MORALE);
	figure3 = new FigureB(BLACK, INITIAL_PROB, INITIAL_MORALE);
	figure4 = new FigureB(ASIAN, INITIAL_PROB, INITIAL_MORALE);
	figure5 = new FigureB(WHITE_SUPREME, INITIAL_PROB, INITIAL_MORALE);

	list.push_back(figure0);
	list.push_back(figure1);
	list.push_back(figure2);
	list.push_back(figure3);
	list.push_back(figure4);
	list.push_back(figure5);

}

void Grid::setBoard(BasicInterface* super)
{
	for (int i = -BOARD_SIZE; i <= BOARD_SIZE; i += BOARD_INTERVAL)
	{
		for (int j = -BOARD_SIZE; j <= BOARD_SIZE; j += BOARD_INTERVAL)
		{
			generateFig(super, i, j);
		}
	}
}



Grid::~Grid()
{
	delete figure0;
	delete figure1;
	delete figure2;
	delete figure3;
	delete figure4;
	delete figure5;
	net.clear();
	net.shrink_to_fit();
	list.clear();
	list.shrink_to_fit();
}