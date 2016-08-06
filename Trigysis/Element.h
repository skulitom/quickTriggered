#ifndef ELEMENT_H
#define ELEMENT_H

#include "BasicElement.h"
#include "BasicInterface.h"

class Element : public ElementInterface
{

public:
	Element(BasicInterface* super);

	virtual ~Element() { D3DDelete(this->TBuffer); }

	virtual void Spawn(Vector2d& position, short indexOfVPort) override;

	virtual void RenderText(Vector2d& pos, XMFLOAT3& color, float scale, char* text, ...);

	virtual void Render() override;

private:

	void TDraw();

protected:

	char* TBuffer;
	XMFLOAT3 TColor;
	bool TNeedRender;
	Vector2d TPos;
	float TScale;

	BasicInterface* Super;

	

};

#endif // !ELEMENT_H
