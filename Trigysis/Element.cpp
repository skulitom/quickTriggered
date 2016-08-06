#include "Element.h"
#include <stdarg.h>

//////////////////////////////////////////////////////////
//**Element
//////////////////////////////////////////////////////////
Element::Element(BasicInterface* super)
	: ElementInterface(super->GetElementBase())
{
	DeclareElementName(Element, this->EName);
	this->Super = super;
}

void Element::Spawn(Vector2d& position, short indexOfVPort)
{

	ElementInterface::Spawn(position, indexOfVPort);
	this->PMLand->AddNewElement(this);

}

void Element::Render()
{

	ElementInterface::Render();

	if (this->IsNeedRender && this->TNeedRender)
	{
		//this->TNeedRender = false;
		this->Super->GetFont2D()->Draw(this->TPos, this->TColor, this->TScale, this->TBuffer);
	}
}

void Element::RenderText(Vector2d& pos, XMFLOAT3& color, float scale, char* text, ...)
{
	if (!this->TBuffer)
	{

		this->TBuffer = new char[256];

	}

	va_list List;
	va_start(List, text);
	vsprintf(this->TBuffer, text, List);

	this->TColor = color;
	this->TPos = this->Position + pos;
	this->TScale = scale;

	this->TNeedRender = true;

}

void Element::TDraw()
{

	if (this->TNeedRender)
		this->Super->GetFont2D()->Draw(this->TPos, this->TColor,this->TScale, this->TBuffer);

}