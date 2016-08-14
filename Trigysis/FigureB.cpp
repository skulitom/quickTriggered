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
}

void FigureB::createFigure(BasicInterface* super, int x, int y)
{
	this->fig = new Figure(super);
	this->fig->SetFigureSuperType(0);
	this->fig->SetFigureType(0);

	this->fig->SetColors(colorPicker());
	this->fig->Spawn(Vector2d(x, y), 1);

	this->list.push_back(fig);
}

XMFLOAT4 FigureB::colorPicker()
{
	switch(type)
	{
	case MEXICANS:
		return XMFLOAT4(0.5, 0.5, 0, 0);
	case JEWS:
		return XMFLOAT4(0.2, 0.2, 0.2, 0);
	case WOMEN:
		return XMFLOAT4(0.2, 0.7, 0, 0);
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

void FigureB::deleteFigure(int index)
{
	
	this->list.erase(this->list.begin() + index);
}

FigureB::~FigureB()
{
	delete fig;
	list.clear();
	list.shrink_to_fit();
}