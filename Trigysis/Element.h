#ifndef ELEMENT_H
#define ELEMENT_H

#include "BasicElement.h"
#include "BasicInterface.h"

struct TStruct
{

	TStruct()
	{
		this->TBuffer = nullptr;
		this->TColor = XMFLOAT3(0, 0, 0);
		this->TPos = Vector2d(0, 0);
		this->TScale = 1;
	}

	~TStruct() {
		D3DDelete(this->TBuffer);
	}

	char* TBuffer;
	XMFLOAT3 TColor;
	Vector2d TPos;
	float TScale;

};

class Element : public ElementInterface
{

public:
	Element(BasicInterface* super);

	virtual ~Element() {}

	virtual void Spawn(Vector2d& position, short indexOfVPort) override;

	virtual void RenderText(Vector2d& pos, XMFLOAT3& color, float scale, const char* text, ...);

	virtual void Render() override;

	virtual bool Update() override;

	void SetCameraAffect(float cAffect) { this->CameraAffect = cAffect; }
	float GetCameraAffect() { return this->CameraAffect; }

private:

	void CameraMove();

private:
	Vector2d PrevCamPos;

protected:

	TStruct TSBuffer[8];

	int IndexOfTBuffer;

	bool TNeedRender;

	bool TIsConstant;

	BasicInterface* Super;

	//Value [0:1]
	float CameraAffect;

};

#endif // !ELEMENT_H
