#include "FigureMorale.h"

struct FigureActionException : public std::exception
{
	const char * what() const throw () {
		return "***Figure ACTION error***";
	}
};

struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

FigureMorale::~FigureMorale()
{
	
}

void FigureMorale::analyseAction(FigureB *figure, int action)
{
	switch (action)
	{
	case HOLOCAUST:
		holocaust(figure);
		break;
	case JIHAD:
		Jihad(figure);
		break;
	case FEMINIST:
		femWave(figure);
		break;
	case I_HAVE_A_DREAM:
		iHaveADream(figure);
		break;

	default:
		throw FigureActionException();

	}
}

void FigureMorale::Jihad(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:

		break;
	case BLACK:

		break;
	case ASIAN:

		break;
	case WHITE_SUPREME:
		figure->setProb(figure->getProb() * -JIHAD_MORALE);
		break;
	default:
		throw FigureTypeException();

	}
}

void FigureMorale::femWave(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:
		figure->setProb(figure->getProb() * FEMINIST_MORALE);
		break;
	case BLACK:

		break;
	case ASIAN:

		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

void FigureMorale::holocaust(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:
		figure->setProb(figure->getProb() * HOLOCAUST_MORALE);
		break;
	case WOMEN:

		break;
	case BLACK:

		break;
	case ASIAN:

		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

void FigureMorale::iHaveADream(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:

		break;
	case BLACK:
		figure->setProb(figure->getProb() * I_HAVE_A_DREAM_MORALE);
		break;
	case ASIAN:

		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

FigureMorale::FigureMorale()
{
	
}
