#include "FigureDrop.h"

struct FigureActionException : public std::exception
{
	const char * what() const throw (){
		return "***Figure ACTION error***";
	}
};

struct FigureTypeException : public std::exception
{
	const char * what() const throw () {
		return "***Figure TYPE error***";
	}
};

FigureDrop::FigureDrop()
{
	
}

FigureDrop::~FigureDrop()
{

}

void FigureDrop::analyseAction(FigureB *figure, int action)
 {
 	switch (action)
 	{
 	case HOLOCAUST:
 		
 		break;
 	case CHILD_POLICY:
 		
 		break;
 	case JIHAD:
 		
 		break;
 	case FEMINIST:
 		
 		break;
 	case I_HAVE_A_DREAM:
 		
 		break;

 	default:
 	throw FigureActionException();
 
 	}
 }

void FigureDrop::ChildPolicy(FigureB *figure)
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
		figure->setProb(figure->getProb() - CHILD_POLICY_PROB);
		break;
 	case WHITE_SUPREME:
 		
 		break;
 	default:
 		throw FigureTypeException();
 
 	}
}

void FigureDrop::Jihad(FigureB *figure)
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
		figure->setProb(figure->getProb() - JIHAD_PROB);
		break;
	default:
		throw FigureTypeException();

	}
}

void FigureDrop::femWave(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:

		break;
	case WOMEN:
		figure->setProb(figure->getProb() + FEMINIST_PROB);
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

void FigureDrop::holocaust(FigureB *figure)
{
	switch (figure->getType())
	{
	case MEXICANS:

		break;
	case JEWS:
		figure->setProb(figure->getProb() + HOLOCAUST_PROB);
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

void FigureDrop::iHaveADream(FigureB *figure)
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
		figure->setProb(figure->getProb() + I_HAVE_A_DREAM_PROB);
		break;
	case ASIAN:
		
		break;
	case WHITE_SUPREME:

		break;
	default:
		throw FigureTypeException();

	}
}

int FigureDrop::FigureToDrop(FigureB* figure0, FigureB* figure1, FigureB* figure2, FigureB* figure3, FigureB* figure4, FigureB* figure5)
{
	int totalProb = 0;
	int j = 0;
	srand (time(NULL));
	std::array<int, 6> figureProbabilities = { figure0->getProb() , figure1->getProb() , figure2->getProb() , figure3->getProb() , figure4->getProb() , figure5->getProb() };
	for (int i = 0; i < figureProbabilities.size(); i++)
	{
		 totalProb += figureProbabilities.at(i);
		 j = i;
	}
	int random = rand() % (totalProb + 1);

    while(totalProb > 0)
    {
		totalProb -= figureProbabilities.at(j);
		if(random>= totalProb)
		{
			break;
		}
		j--;
    }

	return j;

}














