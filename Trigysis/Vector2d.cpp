#include "Vector2d.h"

#include <cmath>

Vector2d::Vector2d()
{

	//this->X = 0 - 0.001f;
	//this->Y = 0;

}

Vector2d::Vector2d(float x, float y)
{

	this->X = x;
	this->Y = y;

}

//////////////////////////////////////////
//**Conversion
//////////////////////////////////////////

void Vector2d::GetFromXMVector(XMVECTOR& sourceVec)
{

	XMFLOAT2 FATTYFLOATBASTARD;

	XMStoreFloat2(&FATTYFLOATBASTARD, sourceVec);

	this->X = FATTYFLOATBASTARD.x;
	this->Y = FATTYFLOATBASTARD.y;

}

XMVECTOR& Vector2d::GetXMVector()
{

	XMFLOAT2 FATTYFLOATBASTARD;

	FATTYFLOATBASTARD.x = this->X;
	FATTYFLOATBASTARD.y = this->Y;

	return XMLoadFloat2(&FATTYFLOATBASTARD);

}

//////////////////////////////////////////
//**Math functions
//////////////////////////////////////////

void Vector2d::Negative()
{

	this->X = -this->X;
	this->Y = -this->Y;

}

void Vector2d::Normalize()
{

	float Length = sqrtf(this->X * this->X + this->Y * this->Y);

	this->X /= Length;
	this->Y /= Length;

}

float Vector2d::GetLength()
{

	return sqrtf(this->X * this->X + this->Y * this->Y);

}

//////////////////////////////////////////
//**Operators
//////////////////////////////////////////

Vector2d& Vector2d::operator= (Vector2d& secondVec)
{

	this->X = secondVec.X;
	this->Y = secondVec.Y;

	return *this;

}

Vector2d Vector2d::operator+ (Vector2d secondVec)
{

	Vector2d Ans;

	Ans.X = this->X + secondVec.X;
	Ans.Y = this->Y + secondVec.Y;

	return Ans;
}

Vector2d Vector2d::operator- (Vector2d secondVec)
{

	Vector2d Ans;

	Ans.X = this->X - secondVec.X;
	Ans.Y = this->Y - secondVec.Y;

	return Ans;
}

Vector2d Vector2d::operator* (Vector2d secondVec)
{

	Vector2d Ans;

	Ans.X = this->X * secondVec.X;
	Ans.Y = this->Y * secondVec.Y;

	return Ans;
}

Vector2d Vector2d::operator / (Vector2d secondVec)
{

	Vector2d Ans;

	Ans.X = this->X / secondVec.X;
	Ans.Y = this->Y / secondVec.Y;

	return Ans;
}

void Vector2d::operator= (float& val)
{

	this->X = val;
	this->Y = val;

}

Vector2d Vector2d::operator+ (float val)
{

	Vector2d Ans;

	Ans.X = this->X + val;
	Ans.Y = this->Y + val;

	return Ans;
}

Vector2d Vector2d::operator- (float val)
{

	Vector2d Ans;

	Ans.X = this->X - val;
	Ans.Y = this->Y - val;

	return Ans;
}

Vector2d Vector2d::operator* (float val)
{

	Vector2d Ans;

	Ans.X = this->X * val;
	Ans.Y = this->Y * val;

	return Ans;
}

Vector2d Vector2d::operator / (float val)
{

	Vector2d Ans;

	Ans.X = this->X / val;
	Ans.Y = this->Y / val;

	return Ans;
}