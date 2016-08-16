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
	this->net = new std::vector<std::vector<FigureB*>>(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	for (int t = 0; t <= (2 * BOARD_SIZE) / BOARD_INTERVAL; t++)
	{
		this->net->at(t).resize(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	}


}

void Grid::update()
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (net->at(i).at(j)->isClicked())
			{
				net->at(i).at(j)->Delete();
			}
		}
	}
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

void Grid::generateFig(BasicInterface* super, int i, int j)
{
	int drop = fmanager->FigureToDrop();
	fig = new FigureB(super, drop);
	

	fig->Spawn(Vector2d(i,j),1); 
	net->at((i + BOARD_SIZE) / BOARD_INTERVAL).at((j + BOARD_SIZE) / BOARD_INTERVAL) = fig;
}

void Grid::deleteAt(int x, int y)
{

	net->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((y + BOARD_SIZE) / BOARD_INTERVAL)->Delete();
	net->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((y + BOARD_SIZE) / BOARD_INTERVAL) = nullptr;

}





Grid::~Grid()
{
	D3DDelete(fig);
	D3DDelete(net);
}