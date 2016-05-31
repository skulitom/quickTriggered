#ifndef MOUSE_H
#define MOUSE_H

#include "Vector2d.h"

class MouseHandle
{

public:

	XMFLOAT2& GetMousePos();
	void SetMousePos(float x, float y);

private:

	XMFLOAT2 Pos;

};

#endif //MOUSE_H