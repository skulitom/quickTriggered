#include "FigureManager.h"

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

FigureManager::FigureManager()
{
	
}

FigureManager::~FigureManager()
{
	
}

void FigureManager::analyseAction(FigureB *figure, int action)
{
	switch (action)
	{
	case HOLOCAUST:
		holocaust(figure);
		break;
	case CHILD_POLICY:
		ChildPolicy(figure);
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

void FigureManager::ChildPolicy(FigureB *figure)
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
		figure->setProb(figure->getProb() * -CHILD_POLICY_PROB);
		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

void FigureManager::Jihad(FigureB *figure)
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
		figure->setProb(figure->getProb() * JIHAD_PROB);
		figure->setMorale(figure->getMorale() * JIHAD_MORALE);
		break;
	default:
		throw FigureTypeException();

	}
}

void FigureManager::femWave(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:
		figure->setProb(figure->getProb() * FEMINIST_PROB);
		figure->setMorale(figure->getMorale() * FEMINIST_MORALE);
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

void FigureManager::holocaust(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:
		figure->setProb(figure->getProb() * HOLOCAUST_PROB);
		figure->setMorale(figure->getMorale() * HOLOCAUST_MORALE);
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

void FigureManager::iHaveADream(FigureB *figure)
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
		figure->setProb(figure->getProb() * I_HAVE_A_DREAM_PROB);
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

int FigureManager::FigureToDrop(std::vector<FigureB*> list)
{
	int totalProb = 0;
	int j = 0;
	std::array<int, 6> figureProbabilities = { list.at(0)->getProb() , list.at(1)->getProb() , list.at(2)->getProb() , list.at(3)->getProb() , list.at(4)->getProb() , list.at(5)->getProb() };
	for (int i = 0; i < figureProbabilities.size(); i++)
	{
		totalProb += figureProbabilities.at(i);
		j = i;
	}
	int random = MathHelp::GetRandom(totalProb, 0, false);

	while (totalProb > 0)
	{
		totalProb -= figureProbabilities.at(j);
		if (random >= totalProb)
		{
			break;
		}
		j--;
	}

	return j;

}