#ifndef FigureDrop_H
#define FigureDrop_H

#include <exception>

#define MAX_PROB 600
#define MIN_PROB 0

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5

#define HOLOCAUST 50
#define FEMINIST 200
#define I_HAVE_A_DREAM 50
#define CHILD_POLICY 50
#define JIHAD 50

class FigureDrop{

public:
	FigureDrop();
	~FigureDrop();
	int getProbability(int type);

	void holocaust();
	void femWave();
	void iHaveADream();
	void ChildPolicy();
	void Jihad();

protected:
private:
	int mexicans=100;
	int jews=100;
	int women=100;
	int black=100;
	int asian=100;
	int whiteSup=100;

	inline void setMexicanProb(int prob) { this->mexicans = prob; }
	inline void setJewProb(int prob) { this->jews = prob; }
	inline void setWomenProb(int prob) { this->women = prob; }
	inline void setBlackProb(int prob) { this->black = prob; }
	inline void setAsianProb(int prob) { this->asian = prob; }
	inline void setWSProb(int prob) { this->whiteSup = prob; }

	void setProbability(int type, int prob);

	bool validProbability(int num);

};

#endif