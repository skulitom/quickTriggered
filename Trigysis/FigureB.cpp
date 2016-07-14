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

FigureB::~FigureB()
{
	
}