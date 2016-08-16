#include "FigureB.h"


FigureB::FigureB(int type, int prob, int morale)
{
	if (type >= MIN_FIGURE_NUM && type <= MAX_FIGURE_NUM && prob > MIN_PROB && prob <= MAX_PROB && morale > MIN_MORALE && morale <= MAX_MORALE) {
		this->type = type;
		this->prob = prob;
		this->morale = morale;
	}else
	{
		std::cout << "Wrong Figure Parameters";
		throw;
	}

	this->track = new std::vector<std::vector<int>>(((2 * BOARD_SIZE) / BOARD_INTERVAL) + 1);
	for (int t = 0; t <= (2 * BOARD_SIZE) / BOARD_INTERVAL; t++)
	{
		this->track->at(t).resize(((2 * BOARD_SIZE) / BOARD_INTERVAL) + 1);
	}
}

void FigureB::createFigure(BasicInterface* super, int x, int y)
{
	this->fig = new Figure(super);
	this->fig->SetFigureSuperType(0);
	this->fig->SetFigureType(0);

	this->fig->SetColors(colorPicker());
	this->fig->Spawn(Vector2d(x, y), 1);

	this->list.push_back(fig);

	this->track->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((x + BOARD_SIZE) / BOARD_INTERVAL) = list.size() - 1;

	
}



XMFLOAT4 FigureB::colorPicker()
{
	switch(type)
	{
	case MEXICANS:
		return XMFLOAT4(0, 0, 1, 0);
	case JEWS:
		return XMFLOAT4(0, 1, 1, 0);
	case WOMEN:
		return XMFLOAT4(0, 1, 0, 0);
	case BLACK:
		return XMFLOAT4(0,0,0,0);
	case ASIAN:
		return XMFLOAT4(1, 0, 0, 0);
	case WHITE_SUPREME:
		return XMFLOAT4(1, 1, 1, 0);
	default:
		return XMFLOAT4(1, 1, 0, 0);

	}
}

void FigureB::deleteFigAt(int x, int y)
{
	x = x - (x % BOARD_INTERVAL);
	y = y - (y % BOARD_INTERVAL);
	Vector2d& pos = getFigAt(x, y);	
    deleteFigure(list.at(track->at((pos.X + BOARD_SIZE) / BOARD_INTERVAL).at((pos.Y + BOARD_SIZE) / BOARD_INTERVAL)));
}

Vector2d& FigureB::getFigAt(int x, int y)
{
	x = x - (x % BOARD_INTERVAL);
	y = y - (y % BOARD_INTERVAL);
	return list.at(track->at((x + BOARD_SIZE) / BOARD_INTERVAL).at((y + BOARD_SIZE) / BOARD_INTERVAL))->GetPosition();
}

void FigureB::deleteFigure(Figure* fig)
{
	if (fig->GetIsFired())
	{
		fig = nullptr;
	}
	for (int index = 0; index < this->list.size(); index++)
	{
		if (fig == this->list.at(index))
		{
			this->list.erase(this->list.begin() + index);
		}
	}
	//for (int i = 0; i < net->size(); i++)
	//{
	//	for (int j = 0; j < net->at(i).size(); j++)
	//	{
	//		if (fig == net->at(i).at(j))
	//		{
	//			net->at(i).erase(net->at(i).begin() + j);
	//		}
	//	}
	//}

	ElementDelete(fig);
}



FigureB::~FigureB()
{
	D3DDelete(fig);
	D3DDelete(track);
	list.clear();
	list.shrink_to_fit();
}