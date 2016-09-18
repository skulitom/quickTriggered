#ifndef GUI_FIGURES_H
#define GUI_FIGURES_H

#include "BasicInterface.h"
#include "Element.h"
#include "Button.h"
#include "GUIPhysBasic.h"

#define GUIF_SIZE 64
#define GUIF_MOVE_SPEED 100

class FButton : public ButtonInterface
{

public:
	FButton(BasicInterface* super);
};

class Figure : public Element, public PhysBasic
{

public:

	Figure(BasicInterface* super);
	virtual ~Figure();

	virtual void Spawn(Vector2d& position, short indexOfVPort) override;

	inline Vector2d& GetInCellPos() { return this->InCellPos; }
	void SetInCellPos(Vector2d& inCellPos) { this->InCellPos = inCellPos; }

	//**Set What type of the persona this type is belogs to
	void SetFigureType(UINT type);
	//**Get What type of the persona this type is belogs to
	inline UINT GetFigureType() { return this->Type; }

	//**Set What type of the super persona this type is belogs to
	void SetFigureSuperType(UINT sType);
	//**Get What type of the super persona this type is belogs to
	inline UINT GetFigureSuperType() { return this->SType; }

	bool Update() override;

	void MoveDirect(Vector2d& dest, float moveSpeed);

	void DeleteMeBFunc();

	inline FButton* GetButton() { return this->FrontButton; }

	virtual void Delete() override;

	inline bool GetIsFalling() { return this->IsFalling ? true : false; }
	void FallToPos(Vector2d& startPos, Vector2d& endPos);

	Vector2d& GetFallDestPos() { return this->FallDestPos; }

private:

	UINT Type;
	UINT SType;

	FButton* FrontButton;

	bool IsMoving;
	
	Vector2d FallPos;
	Vector2d FallDestPos;
	bool IsFalling;

private:

	void Move(Vector2d& dest, float deltaTime);

protected:

	float MoveSpeed;
	Vector2d DestPos;
	Vector2d InCellPos;

};

#endif // !GUI_FIGURES_H
