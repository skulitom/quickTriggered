#include "Mouse.h"

void MouseHandle::SetMousePos(float x, float y)
{

	this->Pos = XMFLOAT2(x, y);

}

XMFLOAT2& MouseHandle::GetMousePos()
{

	return this->Pos;

}