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
	this->IndexOfTBuffer = -1;
	this->CameraAffect = 1;
}

void Element::Spawn(Vector2d& position, short indexOfVPort)
{

	ElementInterface::Spawn(position, indexOfVPort);
	this->PMLand->AddNewElement(this);
	this->PrevCamPos = this->D3dApp->GetVPStruct(indexOfVPort).VPCamera.GetPosition();

}

void Element::Render()
{

	ElementInterface::Render();

	if (this->IsNeedRender && this->TNeedRender)
	{
		//this->TNeedRender = false;
		for (int i = 0; i < this->IndexOfTBuffer + 1; i++)
			this->Super->GetFont2D()->Draw(this->TSBuffer[i].TPos, this->TSBuffer[i].TColor, this->TSBuffer[i].TScale, 
			this->TSBuffer[i].TBuffer);
	}

	if (!this->TIsConstant)
		this->IndexOfTBuffer = -1;

}

void Element::RenderText(Vector2d& pos, XMFLOAT3& color, float scale, const char* text, ...)
{

	this->IndexOfTBuffer++;

	if (!this->TSBuffer[this->IndexOfTBuffer].TBuffer)
	{

		this->TSBuffer[this->IndexOfTBuffer].TBuffer = new char[256];

	}

	va_list List;
	va_start(List, text);
	vsprintf(this->TSBuffer[this->IndexOfTBuffer].TBuffer, text, List);

	this->TSBuffer[this->IndexOfTBuffer].TColor = color;
	this->TSBuffer[this->IndexOfTBuffer].TPos = this->Position + pos;
	this->TSBuffer[this->IndexOfTBuffer].TScale = scale;

	this->TNeedRender = true;


}

bool Element::Update()
{

	if (!ElementInterface::Update())
		return false;

	this->CameraMove();

	return true;

}

void Element::CameraMove()
{

	if (this->CameraAffect)
	{

		this->Position = this->Position -
			(this->D3dApp->GetVPStruct(this->IndexOfViewPort).VPCamera.GetPosition() - this->PrevCamPos) * this->CameraAffect *
			this->D3dApp->GetTimer()->GetDeltaTime();

		this->PrevCamPos = this->D3dApp->GetVPStruct(this->IndexOfViewPort).VPCamera.GetPosition();


	}

}
