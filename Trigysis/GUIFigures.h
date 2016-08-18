#ifndef GUI_FIGURES_H
#define GUI_FIGURES_H

#include "BasicInterface.h"
#include "Element.h"
#include "Button.h"
#include "GUIPhysBasic.h"

#define GUIF_SIZE 64
#define GUIF_MOVE_SPEED 100

class Figure;
typedef void (Figure::*FFunc)(void);

class FButton : public ButtonInterface
{

public:

	FButton(BasicInterface* super, Figure* pFigureClass);
	void SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, FFunc tf);

private:

	void EventOnSelect() { (this->PFigureClass->*this->FFOnSelect)(); }
	void EventOnClick() { (this->PFigureClass->*this->FFOnClick)(); }
	void EventOnPress() { (this->PFigureClass->*this->FFOnPress)(); }
	void EventOnStopInquisition() { (this->PFigureClass->*this->FFOnStopInquisition)(); }

	Figure* PFigureClass;

	FFunc FFOnSelect;
	FFunc FFOnClick;
	FFunc FFOnPress;
	FFunc FFOnStopInquisition;

};

class Figure : public Element, public PhysBasic
{

public:

	Figure(BasicInterface* super);
	virtual ~Figure();

	virtual void Spawn(Vector2d& position, short indexOfVPort) override;

	Vector2d& GetInCellPos() { return this->InCellPos; }
	void SetInCellPos(Vector2d& inCellPos) { this->InCellPos = inCellPos; }

	//**Set What type of the persona this type is belogs to
	void SetFigureType(UINT type);
	//**Get What type of the persona this type is belogs to
	UINT GetFigureType() { return this->Type; }

	//**Set What type of the super persona this type is belogs to
	void SetFigureSuperType(UINT sType);
	//**Get What type of the super persona this type is belogs to
	UINT GetFigureSuperType() { return this->SType; }

	bool Update() override;

	void MoveDirect(Vector2d& dest, float moveSpeed);

	void DeleteMeBFunc();

	FButton* GetButton() { return this->FrontButton; }

	virtual void Delete() override;

	bool GetIsFalling() { return this->IsFalling ? true : false; }
	void FallToPos(Vector2d& startPos, Vector2d& endPos);

private:

	UINT Type;
	UINT SType;

	FButton* FrontButton;

	bool IsMoving;
	
	Vector2d FallPos;
	bool IsFalling;

private:

	void Move(Vector2d& dest, float deltaTime);

protected:

	float MoveSpeed;
	Vector2d DestPos;
	Vector2d InCellPos;

};

#endif // !GUI_FIGURES_H
