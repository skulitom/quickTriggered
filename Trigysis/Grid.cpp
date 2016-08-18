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
	for (int i = 0; i <= (2 * BOARD_SIZE) / BOARD_INTERVAL; i++)
	{
		for (int j = 0; j <= (2 * BOARD_SIZE) / BOARD_INTERVAL; j++)
		{
			this->net->at(i).at(j) = nullptr;
		}
	}


}

void Grid::Update(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (!(this->net->at(i).at(j) == nullptr))
			{
				if (this->net->at(i).at(j)->isClicked())
				{
					deleteAt(i,j);
				}
				if (j-1>= 0)
				{
					if (this->net->at(i).at(j-1)==nullptr)
					{
						int counter = 1;
						while (this->net->at(i).at(j - counter) == nullptr)
						{
							this->net->at(i).at(j - counter) = this->net->at(i).at(j - counter + 1);
							this->net->at(i).at(j - counter + 1) = nullptr;
							counter++;
							if (counter > j)
								break;
						}
					}
				}
			}
		}
	}
	updatePositions(super);
}

void Grid::updatePositions(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		if (this->net->at(i).at(GRID_FIGURE_WIDTH-1) == nullptr)
		{
			generateFig(super, (i*BOARD_INTERVAL) - BOARD_SIZE, BOARD_SIZE);
		}
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j)!=nullptr)
				this->net->at(i).at(j)->SetPosition(Vector2d((i*BOARD_INTERVAL) - BOARD_SIZE, (j*BOARD_INTERVAL) - BOARD_SIZE));
		}
	}
}

void Grid::setBoard(BasicInterface* super)
{
	bool round = fmanager->getRandomBool();
	for (int i = -BOARD_SIZE; i <= BOARD_SIZE; i += BOARD_INTERVAL)
	{
		for (int j = -BOARD_SIZE; j <= BOARD_SIZE; j += BOARD_INTERVAL)
		{
			if (j%3==0)
			{
				generateFig(super, i, j, round);
				round = !round;
			}
			else
			{
				generateFig(super, i, j);
			}

		}
	}
}

bool Grid::compareAt(int x1, int y1, int x2, int y2)
{
	if (x1 >= GRID_FIGURE_WIDTH || x2 >= GRID_FIGURE_WIDTH || x1 < 0 || x2 < 0)
	{
		return false;
	}
	else if (y1 >= GRID_FIGURE_HEIGHT || y2 >= GRID_FIGURE_HEIGHT || y1 < 0 || y2 < 0)
	{
		return false;
	}
	else if (net->at(x1).at(y1) == nullptr || net->at(x2).at(y2)== nullptr)
	{
		return false;
	}
	if (net->at(x1).at(y1)->getType() == net->at(x2).at(y2)->getType())
	{
		return true;
	}
	return false;
}

void Grid::generateFig(BasicInterface* super, int i, int j)
{
	int drop = fmanager->FigureToDrop();
	this->fig = new FigureB(super, drop);	
	this->fig->Spawn(Vector2d(i,j),1); 
	insertAt((i + BOARD_SIZE) / BOARD_INTERVAL, (j + BOARD_SIZE) / BOARD_INTERVAL, this->fig);
}

void Grid::generateFig(BasicInterface* super, int i, int j, bool round)
{
	int drop = fmanager->FigureToDrop(round);
	this->fig = new FigureB(super, drop);
	this->fig->Spawn(Vector2d(i, j), 1);
	insertAt((i + BOARD_SIZE) / BOARD_INTERVAL, (j + BOARD_SIZE) / BOARD_INTERVAL, this->fig);
}

void Grid::insertAt(int x, int y, FigureB* fig)
{
	net->at(x).at(y) = fig;
}

void Grid::deleteAt(int x, int y)
{
	this->net->at(x).at(y)->Delete();
	this->net->at(x).at(y) = nullptr;
}







Grid::~Grid()
{
	ElementDelete(fig);
	D3DDelete(net);
}