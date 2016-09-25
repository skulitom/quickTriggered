#ifndef FigureB_H
#define FigureB_H

#include <iostream>
#include <vector>
#include "BasicInterface.h"
#include "GUIFigures.h"
#include "Crypter.h"

#define MEXICANS 0
#define JEWS 1
#define WOMEN 2
#define BLACK 3
#define ASIAN 4
#define WHITE_SUPREME 5

#define DISTANCE_DELTA 1

class FigureB : public Element {
public:
	FigureB(BasicInterface* super, int type);
	virtual ~FigureB();

	inline void setType(int type) { this->type = type; };
	inline int getType() { return this->type; }
	inline bool getIsMoving(){ return this->IsMoving; }
	inline bool getToBreak(){ return this->toBreak; }
	inline void breakFig(){ this->toBreak = true; }
	inline void recoverFig(){ this->toBreak = false; }
	virtual bool Update() override;
	virtual void Spawn(Vector2d& pos, short indexOfVP) override;
	virtual void FallToPos(Vector2d& endPos);
	virtual inline bool getIsFalling(){ return this->fig->GetIsFalling(); };
	virtual Vector2d getPositionB();
	inline Vector2d getOriginalPos(){ return this->originalPos; };
	inline void setOriginalPos(Vector2d pos){ this->originalPos = pos; }
	inline Vector2d getLastPos(){ return this->lastPos; };
	inline void setLastPos(Vector2d pos){ this->lastPos = pos; }
	inline void setPositionB(Vector2d pos){ this->fig->SetPosition(pos); }
	inline bool isClicked(){ return this->fig->GetButton()->GetStatus(DX_BUTTON_STATUS_CLICKED) ? true : false; }
	inline bool isDragged(){ return this->fig->GetButton()->GetStatus(DX_BUTTON_STATUS_IS_PRESSING) ? true : false; }

protected:
private:

	XMFLOAT4 colorPicker();
	int type;
	bool toBreak;
	Figure *fig;
	bool IsMoving;
	Vector2d PrevMPos, MPos;
	Vector2d originalPos;
	Vector2d lastPos;
	Vector2d newPos;
};

#endif
