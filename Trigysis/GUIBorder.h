#ifndef BORDER_H
#define BODRED_H

#include "Element.h"

class GUIBorder : public Element
{

public:
	GUIBorder(BasicInterface* super);
	virtual ~GUIBorder();

	void Spawn(Vector2d& startPos, Vector2d& endPos, __int16 width, XMFLOAT3& color, short indexOfVP);

	virtual bool Update() override;

private:

};

#endif //!BORDER_H