#ifndef FigureB_H
#define FigureB_H

#include <iostream>
#include <vector>
#include "BasicInterface.h"
#include "GUIFigures.h"

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5

class FigureB : public Element{
public:
	FigureB(BasicInterface* super, int type);
	virtual ~FigureB();

	inline void setType(int type) { this->type = type; };
	inline int getType() { return this->type; }
	inline bool getToBreak(){ return this->toBreak; }
	inline void breakFig(){ this->toBreak = true; }
	virtual bool Update() override;
	virtual void Spawn(Vector2d& pos, short indexOfVP) override;
	inline bool isClicked(){ return this->fig->GetButton()->GetStatus(DX_BUTTON_STATUS_CLICKED) ? true : false; }

protected:
private:

	XMFLOAT4 colorPicker();
	int type;
	bool toBreak;
	Figure *fig;
};

#endif
