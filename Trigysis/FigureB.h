#ifndef FigureB_H
#define FigureB_H

#include <iostream>
#include <vector>
#include "BasicInterface.h"
#include "GUIFigures.h"

#define MAX_PROB 600
#define MIN_PROB 0

#define MAX_MORALE 600
#define MIN_MORALE 0

#define MAX_FIGURE_NUM 6
#define MIN_FIGURE_NUM 0

#define HOLOCAUST 0
#define FEMINIST 1
#define I_HAVE_A_DREAM 2
#define CHILD_POLICY 3
#define JIHAD 4

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5

#define BOARD_INTERVAL 60
#define BOARD_SIZE 240




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

	void createFigure(BasicInterface* super, int x, int y);
	void deleteFigAt(int x, int y);
	void deleteFigure(Figure* fig);
	Vector2d& getFigAt(int x, int y);

protected:
private:

	XMFLOAT4 colorPicker();
	int type;
	int prob;
	int morale;

	Figure *fig;
	std::vector<Figure*> list;
	std::vector<std::vector<int> > *track;
};

#endif
