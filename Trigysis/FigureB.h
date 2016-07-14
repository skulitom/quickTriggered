#ifndef FigureB_H
#define FigureB_H

#include <iostream>

#define MAX_PROB 600
#define MIN_PROB 0

#define MAX_MORALE 600
#define MIN_MORALE 0

#define MAX_FIGURE_NUM 6
#define MIN_FIGURE_NUM 0

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5




class FigureB {
public:
	FigureB(int type, int prob, int morale);
	~FigureB();

	inline void setProb(int prob) { this->prob = prob; };
	inline void setType(int type) { this->type = type; };
	inline void setMorale(int morale) { this->morale = morale; };

	inline int getProb() { return this->prob; }
	inline int getType() { return this->type; }
	inline int getMorale() { return this->morale; }
protected:
private:
	int type;
	int prob;
	int morale;
};

#endif
