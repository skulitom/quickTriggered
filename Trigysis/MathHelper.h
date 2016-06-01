#ifndef MATHHELPER_H
#define MATHHELPER_H

#include "DXInclude\xnamath.h"
#include "Vector2d.h"
#include <time.h>

#define RAND(min, max) \
	((rand()%(int)(((max) + 1) - (min))) + (min))

namespace MathHelp
{

	static void InitRand()
	{

		srand((unsigned)time(NULL));

	}

	
	static INT GetRandomByFloat(INT source, bool isSigned = true)
	{

		if (!source)
			return 0;

		short S = rand() % 2;

		if(S)
			if(!isSigned)
				return rand() % source;
		else 
			return (rand() % source) * (-1);
	

	}

	static INT GetRandom(INT source, INT floor, bool isSigned = true)
	{

		if (!source)
			return 0;

		short S = rand() % 2;
		//((rand() % (int)(((max)+1) - (min))) + (min))
		if (S && isSigned)
			return ((rand() % ((source + 1) - floor)) + floor) * (-1);
		else
			return (rand() % ((source + 1) - floor)) + floor;

	}

	static XMMATRIX MatrixInverseTranspose(CXMMATRIX matrix)
	{

		XMMATRIX A = matrix;

		A.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);

		XMVECTOR det = XMMatrixDeterminant(A);

		return XMMatrixTranspose(XMMatrixInverse(&det, A));

	}

	static FLOAT LengthOfVector(Vector2d& vec)
	{

		return sqrtf(pow(vec.X, 2) + pow(vec.Y,2));

	}

	static FLOAT GetLength(Vector2d pos1, Vector2d pos2)
	{

		pos1 = pos2 - pos1;

		//pos1.x = pos2.x - pos1.x;
		//pos1.y = pos2.y - pos1.y;
		//pos1.z = pos2.z - pos1.z;

		return sqrtf(pow(pos1.X, 2) + pow(pos1.Y, 2));

	}

 	static UINT CBufferMemory(UINT haveMemory)
	{

		UINT Helper = 16;

		do
		{

			if (Helper >= haveMemory)
				return Helper;

			Helper += 16;

		} while (Helper <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT);

		MessageBox(NULL, "CBuffer memory is out of limits", "Math helper: 'CBufferMemory' error!", MB_ICONERROR);

		return false;
	}

	static INT DistIsLessOrEquals(Vector2d& pos1, Vector2d& pos2, FLOAT dist)
	{

		if ((abs(pos1.X - pos2.X) > dist) || (abs(pos1.Y - pos2.Y) > dist))
			return false;

		Vector2d D;

		D = pos1 - pos2;

		//XMStoreFloat3(&D, XMLoadFloat3(&pos1) - XMLoadFloat3(&pos2));

		if(FLOAT Dist = D.GetLength() <= dist)
			return D.GetLength();

		return 0;

	}

	//static Vector2d& GetDeltaAngle(Vector2d& pos1, Vector2d& rot1, Vector2d& pos2)
	//{

	//	Vector2d Vec;

	//	Vec = pos2 - pos1;

	//	//Vec.x = pos2.x - pos1.x;
	//	//Vec.y = pos2.y - pos1.y;
	//	//Vec.z = pos2.z - pos1.z;

	//	FLOAT Len = MathHelp::LengthOfVector(Vec);

	//	Vector2d BestAngle;

	//	BestAngle.Y = acosf(Vec.X / Len);

	//	if (Vec.Y < 0)
	//	{

	//		BestAngle.Y = XMConvertToRadians(360) - BestAngle.Y;

	//	}

	//	Vector2d DeltaAngle;
	//	
	//	DeltaAngle.Y = abs(BestAngle.Y - rot1.Y);
	//	FLOAT F;
	//	F = XMConvertToDegrees(DeltaAngle.Y);
	//	return DeltaAngle;

	//}

	static FLOAT GetAngle(Vector2d& posFrom, Vector2d& posTo, HWND hwnd = NULL)
	{

		//XMVECTOR V = XMLoadFloat3(&posTo) - XMLoadFloat3(&posFrom);

		Vector2d F3 = posTo - posFrom;

		//XMStoreFloat3(&F3, V);

		FLOAT F = F3.GetLength();

		F = acosf(F3.X / F);

		if (F3.Y < 0)
		{

			F = XMConvertToRadians(360) - F;

		}

		std::stringstream outs;
		outs.precision(2);

		//outs << "X = " << F3.X << "Z = " << F3.Z << "Angle = " << F;


		if(hwnd)
			SetWindowText(hwnd, outs.str().c_str());

		return F;
		
	}

	static void NormalizeDegrees(FLOAT& degrees)
	{

		do
		{


			if (degrees > 360)
			{

				degrees = degrees - 360;

			}
			else if (degrees < 0)
			{
				
				degrees = degrees + 360;

			}


		} while (degrees < 0 || degrees > 360);

	}

	static FLOAT NormalizeRadians(FLOAT radians)
	{

		if (radians < 0)
		{

			radians = XM_2PI + radians;

		}

		if (radians > XM_2PI)
		{

			radians = radians - XM_2PI;

		}

		return radians;

	}

	static FLOAT FloatClamp(FLOAT& fl, const FLOAT& flr, const FLOAT& cl)
	{

		if (fl < flr)
		{

			fl = flr;

		}
		else if (fl > cl)
		{

			fl = cl;

		}

		return fl;

	}

	static Vector2d GetFLOAT3FromRot(Vector2d& rot)
	{

		Vector2d Vec;

		Vec.X = sinf(rot.Y);
		Vec.Y = 0.f;//Доработать

		return Vec;

	}

	//static Vector2d GetRotFromTarget(XMFLOAT& lookAt)
	//{

	//	Vector2d Rot;

	//	Rot.y = asinf(lookAt.y);

	//	return Rot;

	//}

}


#endif //MATHIHELPER_H
