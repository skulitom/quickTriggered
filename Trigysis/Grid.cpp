#include "Grid.h"

struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

Grid::Grid()
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
	FirstRoundLogic(super);
	SecondRoundLogic(super);
}

void Grid::FirstRoundLogic(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (!(this->net->at(i).at(j) == nullptr))
			{
				if (j >= 2)
					if (this->net->at(i).at(j - 1) != nullptr && this->net->at(i).at(j - 2) != nullptr)
						if (compareAt(i, j, i, j - 1) && compareAt(i, j, i, j - 2))
						{
							this->net->at(i).at(j)->breakFig();
							this->net->at(i).at(j - 1)->breakFig();
							this->net->at(i).at(j - 2)->breakFig();
						}
				if (i >= 2)
					if (this->net->at(i - 1).at(j) != nullptr && this->net->at(i - 2).at(j) != nullptr)
						if (compareAt(i, j, i - 1, j) && compareAt(i, j, i - 2, j))
						{
							this->net->at(i).at(j)->breakFig();
							this->net->at(i - 1).at(j)->breakFig();
							this->net->at(i - 2).at(j)->breakFig();
						}
				if (this->net->at(i).at(j)->isClicked())
				{
					//Vector2d originalPos = this->net->at(i).at(j)->getPositionB();
					//while (this->net->at(i).at(j)->isDragged())
					//{
					//	this->net->at(i).at(j)->SetPosition(Vector2d(super->GetInput()->GetMousePosCenterVPort(super->GetVPStruct(1))));
					//}
					//Vector2d newPos = this->net->at(i).at(j)->getPositionB();
					//smartInsertAt(newPos.X, newPos.Y, originalPos, this->net->at(i).at(j));
					deleteAt(i, j);
				}
				if (j - 1 >= 0)
				{
					if (this->net->at(i).at(j - 1) == nullptr)
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
}

void Grid::SecondRoundLogic(BasicInterface* super)
{
	for (int i = 0; i < GRID_FIGURE_HEIGHT; i++)
	{
		if (this->net->at(i).at(GRID_FIGURE_WIDTH-1) == nullptr)
		{
			generateFig(super, (i*BOARD_INTERVAL) - BOARD_SIZE, BOARD_SIZE);
		}
		for (int j = 0; j < GRID_FIGURE_WIDTH; j++)
		{
			if (this->net->at(i).at(j) != nullptr){
				Vector2d pos = this->net->at(i).at(j)->getPositionB();
				if (!this->net->at(i).at(j)->getIsFalling())
				{
						this->net->at(i).at(j)->FallToPos(Vector2d((i*BOARD_INTERVAL) - BOARD_SIZE, (j*BOARD_INTERVAL) - BOARD_SIZE));

				}
			}
			breakIt(i, j);
		}
	}
}

void Grid::breakIt(int i, int j)
{

	if (this->net->at(i).at(j)!=nullptr)
		if (this->net->at(i).at(j)->getToBreak())
			deleteAt(i,j);

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

void Grid::smartInsertAt(int x, int y, Vector2d originalPos, FigureB* fig)
{
	x -= x%BOARD_INTERVAL;
	y -= y%BOARD_INTERVAL;
	if (x < -BOARD_SIZE || x > BOARD_SIZE || y < -BOARD_SIZE || y > BOARD_SIZE)
	{
		fig->SetPosition(originalPos);
	}
	else if (originalPos.X == x && originalPos.Y == y)
	{
		fig->SetPosition(originalPos);
	}
	else
	{
		insertAt((x / BOARD_INTERVAL) - BOARD_SIZE, (y / BOARD_INTERVAL) - BOARD_SIZE, fig);
	}
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