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
	prob.resize(NUM_TYPES);
	morale.resize(NUM_TYPES);

	for (int i = 0; i < NUM_TYPES; i++)
	{
		prob.at(i) = 100;
		morale.at(i) = 100;
	}
}

FigureManager::~FigureManager()
{
	prob.clear();
	prob.shrink_to_fit();
	morale.clear();
	morale.shrink_to_fit();
}

void FigureManager::analyseAction(int type, int action)
{
	switch (action)
	{
	case HOLOCAUST:
		holocaust(type);
		break;
	case CHILD_POLICY:
		ChildPolicy(type);
		break;
	case JIHAD:
		Jihad(type);
		break;
	case FEMINIST:
		femWave(type);
		break;
	case I_HAVE_A_DREAM:
		iHaveADream(type);
		break;

	default:
		throw FigureActionException();

	}
}

void FigureManager::ChildPolicy(int type)
{
	switch (type)
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
		this->setProb(type,this->prob.at(type) * -CHILD_POLICY_PROB);
		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

void FigureManager::Jihad(int type)
{
	switch (type)
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
		this->setProb(type, this->prob.at(type) * JIHAD_PROB);
		this->setMorale(type, this->morale.at(type) * JIHAD_MORALE);
		break;
	default:
		throw FigureTypeException();

	}
}

void FigureManager::femWave(int type)
{
	switch (type)
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:
		this->setProb(type, this->prob.at(type) * FEMINIST_PROB);
		this->setMorale(type, this->morale.at(type) * FEMINIST_MORALE);
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

void FigureManager::holocaust(int type)
{
	switch (type)
	{
	case MEXICANS:

		break;
	case JEWS:
		this->setProb(type, this->prob.at(type) * HOLOCAUST_PROB);
		this->setMorale(type, this->morale.at(type) * HOLOCAUST_MORALE);
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

void FigureManager::iHaveADream(int type)
{
	switch (type)
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:

		break;
	case BLACK:
		this->setProb(type, this->prob.at(type) * I_HAVE_A_DREAM_PROB);
		this->setMorale(type, this->morale.at(type) * I_HAVE_A_DREAM_MORALE);
		break;
	case ASIAN:

		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

int FigureManager::FigureToDrop()
{
	int totalProb = 0;
	int j = 0;
	for (int i = 0; i < prob.size(); i++)
	{
		totalProb += this->prob.at(i);
		j = i;
	}
	int random = MathHelp::GetRandom(totalProb, 0, false);

	while (totalProb > 0)
	{
		totalProb -= this->prob.at(j);
		if (random >= totalProb)
		{
			break;
		}
		j--;
	}

	return j;

}