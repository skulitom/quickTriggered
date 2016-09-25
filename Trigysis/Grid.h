#ifndef Grid_H
#define Grid_H

#include <vector>
#include "FigureB.h"
#include "FigureManager.h"

#include "D3DAPP.h"
#include "Element.h"
#include "Button.h"
#include "BasicInterface.h"
#include "GUIFigures.h"
#include "Basic2DDraw.h"
#include "Files.h"
#include "GUIBorder.h"
#include "Entities.h"

#define GRID_FIGURE_WIDTH 9
#define GRID_FIGURE_HEIGHT GRID_FIGURE_WIDTH

#define INITIAL_PROB 100
#define INITIAL_MORALE 100

#define BOARD_INTERVAL 60
#define BOARD_SIZE ((GRID_FIGURE_WIDTH-1)*BOARD_INTERVAL)/2

#define POINT_TO_LOCATION(X) (X + BOARD_SIZE) / BOARD_INTERVAL
#define LOCATION_TO_POINT(X) (X * BOARD_INTERVAL) - BOARD_SIZE
#define CLOSEST_POINT(X) ((X + BOARD_INTERVAL/2)/ BOARD_INTERVAL)* BOARD_INTERVAL


//((GRID_FIGURE_WIDTH - 1)*BOARD_INTERVAL) / 2


class Grid {
public:
	Grid(BasicInterface* super, short indexOfVP);
	~Grid();

	void setBoard(BasicInterface* super);

	void insertAt(int x, int y, FigureB* fig);
	void smartInsertAt(int x, int y,Vector2d originalPos);
	void deleteAt(int x, int y);
	bool compareAt(int x1, int y1, int x2, int y2);
	virtual void Update(BasicInterface* super);
	void SecondRoundLogic(BasicInterface* super);
	void FirstRoundLogic(BasicInterface* super);
	void clearBreaks();
	void moveBackAll();
	void updateOriginalPos();
	bool checkBreaks();
	void freezFigures(bool freez);
	inline bool getEndTurn(){ return this->endTurn; }
	inline void setEndTurn(bool endTurn){ this->endTurn = endTurn; }
	inline bool getToMove(){ return this->toMove; }
	inline void setToBreak(bool toBreak){ this->toBreak = toBreak; }
	inline bool getToBreak(){ return this->toBreak; }
	inline bool getMovingFigBreak(){ return this->net->at(movingFig.X).at(movingFig.Y)!= nullptr ? this->net->at(movingFig.X).at(movingFig.Y)->getToBreak(): true; }

protected:
private:
	void generateFig(BasicInterface* super, int i, int j);
	void generateFig(BasicInterface* super, int i, int j, bool round);
	void breakIt(int i, int j);
	void moveFig(int i, int j, BasicInterface* super);
	void swap(int x1, int y1, int x2, int y2, bool drag);
	int round(int x);
	bool toMove;
	bool endTurn;
	bool toBreak;
	Vector2d movingFig;
	FigureManager *fmanager;

	std::vector<std::vector<FigureB*> > *net;
	FigureB *fig;
	Entities *enti;
	BasicInterface* super;

	short indexOfVP;



};

#endif