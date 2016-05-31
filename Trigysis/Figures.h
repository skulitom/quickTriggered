//#ifndef FIGURES_H
//#define FIGURES_H
//
//#include "Element.h"
//#include "Button.h"
//
//class Figure;
//typedef void (Figure::*FFunc)(void);
//
//class FButton : public ButtonInterface
//{
//
//public:
//
//	FButton(ElementsMLand* ptrToMotherLand);
//	void SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, FFunc tf);
//
//private:
//
//	void EventOnSelect() { (this->PFigureClass->*this->FFOnSelect)(); }
//	void EventOnClick() { (this->PFigureClass->*this->FFOnClick)(); }
//	void EventOnPress() { (this->PFigureClass->*this->FFOnPress)(); }
//	void EventOnStopInquisition() { (this->PFigureClass->*this->FFOnStopInquisition)(); }
//
//	Figure* PFigureClass;
//
//	FFunc FFOnSelect;
//	FFunc FFOnClick;
//	FFunc FFOnPress;
//	FFunc FFOnStopInquisition;
//
//};
//
//class Figure : public Element
//{
//
//public:
//
//	Figure(ElementsMLand* ptrToMLand);
//	virtual ~Figure();
//
//	virtual void Spawn(Vector2d& position, short indexOfVPort) override;
//
//	Vector2d& GetInCellPos() { return this->InCellPos; }
//	void SetInCellPos(Vector2d& inCellPos) { this->InCellPos = inCellPos; }
//
//private:
//
//
//
//protected:
//
//	Vector2d InCellPos;
//
//};
//
//#endif // !FIGURES_H
