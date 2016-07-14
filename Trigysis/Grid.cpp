#include "Grid.h"

struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

Grid::Grid(BasicInterface* super)
{
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
}

void Grid::setBoard(BasicInterface* super)
{
	for (int i = -BOARD_SIZE; i <= BOARD_SIZE; i += BOARD_INTERVAL)
	{
		for (int j = -BOARD_SIZE; j <= BOARD_SIZE; j += BOARD_INTERVAL)
		{
//			createFigure(super,drop->FigureToDrop(figure0,figure1,figure2,figure3,figure4,figure5), i, j);
		}
	}
}

Figure Grid::getGUIfigure(FigureB *figureB)
{

}



void Grid::createFigure(BasicInterface* super,Figure *fig, int x, int y)
{
	fig = new Figure(super);
	fig->SetFigureSuperType(0);
	fig->SetFigureType(0);
	fig->Spawn(Vector2d(x, y), 1);
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
}