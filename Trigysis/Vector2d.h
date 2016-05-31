#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <Windows.h>
#include <Directx\xnamath.h>

class Vector2d
{

public:

	Vector2d();
	Vector2d(float x, float y);

	//////////////////////////////////////////
	//*Math functions
	//////////////////////////////////////////

	void Negative();
	void Normalize();

	float GetLength();

	//////////////////////////////////////////
	//**Conversion
	//////////////////////////////////////////

	void GetFromXMVector(XMVECTOR& sourceVec);

	XMVECTOR& GetXMVector();

	//////////////////////////////////////////
	//**Operators
	//////////////////////////////////////////

	// Vec2 = Vec1
	void operator = (Vector2d& secondVec);

	// Vec3 = Vec1(this) + Vec2
	Vector2d operator + (Vector2d secondVec);
	Vector2d operator - (Vector2d secondVec);
	Vector2d operator * (Vector2d secondVec);
	Vector2d operator / (Vector2d secondVec);

	void operator = (float& val);
	Vector2d operator + (float val);
	Vector2d operator - (float val);
	Vector2d operator * (float val);
	Vector2d operator / (float val);

public:

	float X;
	float Y;

private:



};

#endif //VECTOR2D_H