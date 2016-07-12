#include "FigureDrop.h"

struct FigureTypeException : public std::exception
{
	const char * what() const throw (){
		return "***Figure type error***";
	}
};

struct FigureProbException : public std::exception
{
	const char * what() const throw () {
		return "***Figure probability error***";
	}
};

FigureDrop::FigureDrop(){

}

FigureDrop::~FigureDrop(){

}

int FigureDrop::getProbability(int type)
{
	switch (type)
	{
	case MEXICANS:
		return this->mexicans;
		break;
	case JEWS:
		return this->jews;
		break;
	case WOMEN:
		return this->women;
		break;
	case BLACK:
		return this->black;
		break;
	case ASIAN:
		return this->asian;
		break;
	case WHITE_SUPREME:
		return this->whiteSup;
		break;
	default:
		throw FigureTypeException();

	}
}

void FigureDrop::setProbability(int type, int prob)
{
	if (validProbability(prob)) {
		switch (type)
		{
		case MEXICANS:
			setMexicanProb(prob);
			break;
		case JEWS:
			setJewProb(prob);
			break;
		case WOMEN:
			setWomenProb(prob);
			break;
		case BLACK:
			setBlackProb(prob);
			break;
		case ASIAN:
			setAsianProb(prob);
			break;
		case WHITE_SUPREME:
			setWSProb(prob);
			break;
		default:
			throw FigureTypeException();

		}
	}else
	{
		throw FigureProbException();
	}
}

bool FigureDrop::validProbability(int num)
{
	if(num <= MAX_PROB && num > MIN_PROB)
	{
		return true;
	}else
	{
		return false;
	}
}






