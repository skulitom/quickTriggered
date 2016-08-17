#include "GUIFigures.h"
#include "GUIPhysBasic.h"

//////////////////////////////////////////////////////
//**CCButton
//////////////////////////////////////////////////////
FButton::FButton(BasicInterface* super, Figure* pFigureClass)
	:ButtonInterface(super)
{
	DeclareElementName(FButton, this->EName);
	this->PFigureClass = pFigureClass;
	ButtonSettings BS;
	BS.IdleColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.f);
	BS.InActiveColor = XMFLOAT4(1, 1, 1, 0.f);
	BS.ReadyColor = XMFLOAT4(0.3f, 0.3f, 0.3f, 0.f);
	BS.SuppressColor = XMFLOAT4(0.2f, 0.2f, 0.2f, 0.f);
	BS.IsActive = true;
	BS.IsLongTerm = false;
	BS.IsVisible = false;
	
	this->SetSettings(BS);

	this->Sizes = Vector2d(GUIF_SIZE, GUIF_SIZE);

	this->ShapeType = EL_SHAPE_TYPE_HEXAGON;
	this->IsCircle = true;
}

void FButton::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, FFunc ff)
{
	switch (DX_BUTTON_FUNC_TYPE_)
	{
	case DX_BUTTON_FUNC_TYPE_ONSELECT:
	{
		this->FFOnSelect = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONPRESS:
	{
		this->FFOnPress = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONCLICK:
	{
		this->FFOnClick = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
		return;
	}
	case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
	{
		this->FFOnStopInquisition = ff;
		this->Feature |= DX_BUTTON_FEATURE_ONSTOPINQUISITION;
		return;
	}
	}
}

//////////////////////////////////////////////////////
//**Figure
//////////////////////////////////////////////////////

Figure::Figure(BasicInterface* super)
	:Element(super)
{

	DeclareElementName(Figure, this->EName);
	this->Sizes = Vector2d(GUIF_SIZE, GUIF_SIZE);
	this->Color = XMFLOAT4(1, 1, 1, 0);

	this->FrontButton = new FButton(super, this);
//	this->FrontButton->SetFunc(DX_BUTTON_FUNC_TYPE_ONCLICK, &Figure::DeleteMeBFunc);

	Figure::SetFigureSuperType(0);

	this->ShapeType = EL_SHAPE_TYPE_RECTANGLE;
	this->SetBlendState((UINT)DX_BS_TRANSPARENCY);
}

Figure::~Figure()
{



}

void Figure::Spawn(Vector2d& position, short indexOfVPort)
{
	Element::Spawn(position, indexOfVPort);
	
	this->FrontButton->Spawn(position, indexOfVPort);

}

void Figure::SetFigureSuperType(UINT sType)
{

	this->SType = sType;
	
	if (this->FrontButton)
	{
		std::string TName;
		switch (this->SType)
		{

			case 0:
			{

				TName = "DTFig";
				break;

			}
			default:
			{
				TName = "DonaldHD";
			}

		}

		this->SetMaterial(TName);

	}

}

void Figure::SetFigureType(UINT type)
{

	this->Type = type;

	//switch (this->Type)
	//{

	//	/*case 0:
	//	{
	//		this->Color = XMFLOAT4(1, 0, 0, 1);
	//		break;
	//	}*/
	//	default :
	//	{
	//		this->Color = XMFLOAT4(0, 0, 0, 0);
	//		break;
	//	}

	//}

}

void Figure::Move(Vector2d& dest, float deltaTime)
{

	if (!this->IsMoving)
		return;

	const float Delta = deltaTime * this->MoveSpeed;

	Vector2d NDest = dest - this->Position;
	NDest.Normalize();
	
	short Ind = 0;

	this->Position.X = this->Position.X + NDest.X * Delta;
	if (abs(dest.X - this->Position.X) < Delta)
		Ind++;

	this->Position.Y = this->Position.Y + NDest.Y*Delta;
	if (abs(dest.Y - this->Position.Y) < Delta)
		Ind++;

	if (Ind == 2)
	{
		this->Position = dest;
		this->IsMoving = false;
	}

}

void Figure::MoveDirect(Vector2d& dest, float moveSpeed)
{

	if (!this->IsMoving)
	{
		if (this->Position.X == dest.X && this->Position.Y == dest.Y)
			return;
		this->DestPos = dest;
		this->MoveSpeed = moveSpeed;
		this->IsMoving = true;
	}

}

#define NUM_OF_PIECES 5

void Figure::Delete()
{

	Element::Delete();

	Material* DestrMat = nullptr;

	switch (MathHelp::GetRandom(0, 0, false))
	{
		case 0:
		{
			DestrMat = this->Super->GetMaterial(std::string("HexagonBroken01"));
			break;
		}
	}

	if (!DestrMat)
		return;

	DestrMat->AdditionalTexture = this->MaterialPtr->AdditionalTexture;

	PhysBasic* NewFigPiece = nullptr;

	for (int i = 0; i < NUM_OF_PIECES; i++)
	{

		NewFigPiece = new PhysBasic(this->Super);
		NewFigPiece->SetMaterial(DestrMat);
		NewFigPiece->SetMass(40.f);
		NewFigPiece->SetLifeTime(2);
		//NewFigPiece->TogglePhysic();
		NewFigPiece->SetCustomVars(XMFLOAT4(i, 0, 0, 0));
		NewFigPiece->SetBlendState(DX_BS_TRANSPARENCY);
		NewFigPiece->SetSizes(this->Sizes);
		
		NewFigPiece->SetColors(this->Color);

		if (i == 0)
			NewFigPiece->SetImpulse(Vector2d(0, MathHelp::GetRandom(70,48,false)));
		else if (i == 1)
			NewFigPiece->SetImpulse(Vector2d(MathHelp::GetRandom(70, 48, false), MathHelp::GetRandom(70, 48, false)));
		else if (i == 2)
			NewFigPiece->SetImpulse(Vector2d(MathHelp::GetRandom(70, 48, false), 0));
		else if (i == 3)
			NewFigPiece->SetImpulse(Vector2d(-MathHelp::GetRandom(70, 48, false), -MathHelp::GetRandom(70, 48, false)));
		else if (i == 4)
			NewFigPiece->SetImpulse(Vector2d(-MathHelp::GetRandom(70, 48, false), 0));

		NewFigPiece->Spawn(this->Position, this->IndexOfViewPort);

	}
	this->IsNeedRender = false;

}

bool Figure::Update()
{

	if (!Element::Update())
		return false;

	//this->Color = this->FrontButton->GetColors();

	this->Move(this->DestPos, this->D3dApp->GetTimer()->GetDeltaTime());
	this->FrontButton->SetPosition(this->Position);

	this->CustomVars.x = this->Input->GetMousePosCenterVPort(this->D3dApp->GetVPStruct(this->IndexOfViewPort)).X;
	this->CustomVars.y = this->Input->GetMousePosCenterVPort(this->D3dApp->GetVPStruct(this->IndexOfViewPort)).Y;

	this->FrontButton->SetCustomVars(this->CustomVars);

}