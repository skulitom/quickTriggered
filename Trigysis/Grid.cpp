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
//	net->resize((2 * BOARD_SIZE) / BOARD_INTERVAL).resize((2 * BOARD_SIZE) / BOARD_INTERVAL);
	this->net = new std::vector<std::vector<FigureB*>>(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	for (int t = 0; t <= (2 * BOARD_SIZE) / BOARD_INTERVAL; t++)
	{
		this->net->at(t).resize(((2 * BOARD_SIZE) / BOARD_INTERVAL)+1);
	}

	figure0 = new FigureB(MEXICANS, INITIAL_PROB, INITIAL_MORALE);
	figure1 = new FigureB(JEWS, INITIAL_PROB, INITIAL_MORALE);
	figure2 = new FigureB(WOMEN, INITIAL_PROB, INITIAL_MORALE);
	figure3 = new FigureB(BLACK, INITIAL_PROB, INITIAL_MORALE);
	figure4 = new FigureB(ASIAN, INITIAL_PROB, INITIAL_MORALE);
	figure5 = new FigureB(WHITE_SUPREME, INITIAL_PROB, INITIAL_MORALE);

	listB.push_back(figure0);
	listB.push_back(figure1);
	listB.push_back(figure2);
	listB.push_back(figure3);
	listB.push_back(figure4);
	listB.push_back(figure5);

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
	int drop = fmanager->FigureToDrop(listB);
	listB.at(drop)->createFigure(super, i, j); 
	net->at((i + BOARD_SIZE) / BOARD_INTERVAL).at((j + BOARD_SIZE) / BOARD_INTERVAL) = listB.at(drop);
}

void Grid::deleteAt(int x, int y)
{

	net->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((y + BOARD_SIZE) / BOARD_INTERVAL)->deleteFigAt(x,y);
	net->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((y + BOARD_SIZE) / BOARD_INTERVAL) = nullptr;

}





Grid::~Grid()
{
	D3DDelete(figure0);
	D3DDelete(figure1);
	D3DDelete(figure2);
	D3DDelete(figure3);
	D3DDelete(figure4);
	D3DDelete(figure5);
	D3DDelete(net);
	listB.clear();
	listB.shrink_to_fit();
}