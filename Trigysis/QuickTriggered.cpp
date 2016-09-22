#include "QuickTriggered.h"

//////////////////////////////////////////////////////
//**QTButton
//////////////////////////////////////////////////////
QTButton::QTButton(BasicInterface* super, ButtonSettings& bs)
:ButtonInterface(super, bs)
{
	DeclareElementName(CCButton, this->EName);
	this->Sizes = Vector2d(50, 30);
	//this->SetShapeType(DX_)
}


//////////////////////////////////////////////////////
//**QuickTriggered
//////////////////////////////////////////////////////


bool QuickTriggered::InitApp()
{
	if (this->Device)
	{

		QuickTriggered::Init();
		
		/////////////////////////////////////
		//**Create Views
		/////////////////////////////////////

		this->SetStandartRenderSettings(D3D11_FILL_SOLID, D3D11_CULL_NONE);

		this->Input->SetWinSizes(this->WinSizes);

		/////////////////////////////////////
		//**Load Textures
		/////////////////////////////////////
		//this->SInitMaterials();
		/////////////////////////////////////
		//**Create BackGrounds
		/////////////////////////////////////

		this->InitVPorts();

		this->InitVPShaders();

		std::vector<std::string>* Files;
		this->MainSound = new SoundBasic(&this->HWnd);
		this->MainSound->LoadSounds(std::string(this->GetCatalogName() + "\\Resources\\Music"), &Files);
		this->MainSound->Play(std::string("Sax.wav"),80,true);

		Element* NE = new Element(this);
		NE->SetSizesRelative(Vector2d(this->WinSizes.ClientWWidth, this->WinSizes.ClientWHeight));
		NE->SetMaterial(std::string("Icon"));
		NE->Spawn(Vector2d(0, 0), 1);

	//	this->fontManager = new FontManager();
		this->primaryGame = new PrimaryGame(this);
		this->primaryGame->init(this);
		
		//this->FigToTest = new Figure(this);
		//this->FigToTest->SetFigureType(0);
		//this->FigToTest->SetFigureSuperType(0);
		//this->FigToTest->Spawn(Vector2d(0, 0), 1);

		return true;

	}

	return false;
}

void QuickTriggered::Update()
{
	
	////////////////////////////////////////////////
	//**Render Update
	////////////////////////////////////////////////

	if (GetAsyncKeyState('1'))
		this->Resize(DX_DISPLAY_MODE_1360_768);
	else if (GetAsyncKeyState('2'))
		this->Resize(DX_DISPLAY_MODE_800_600);
	else if (GetAsyncKeyState('2'))
		this->Resize(DX_DISPLAY_MODE_1360_768);
	else if (GetAsyncKeyState('3'))
		this->Resize(DX_DISPLAY_MODE_1920_1080);

	Vector2d Pos;
	
	//////////////////////
	static bool IsMoving = false;
	static Vector2d PrevMPos, MPos;

	//if (this->FigToTest->GetButton()->GetStatus(DX_BUTTON_STATUS_IS_PRESSING))
	//{
	//	if (!IsMoving)
	//	{
	//		this->Input->GetMousePosCenterVPort(this->GetVPStruct(1), &PrevMPos);
	//		//PrevMPos = TMPrevPos;
	//		IsMoving = true;
	//	}
	//	else
	//		PrevMPos = MPos;

	//	this->Input->GetMousePosCenterVPort(this->GetVPStruct(1), &MPos);
	//	//MPos = TMPos;
	//	this->FigToTest->SetPosition(this->FigToTest->GetPosition() + MPos - PrevMPos);
	//}
	//else
	//	IsMoving = false;
	//////////////////////

	this->ElementBase->UpdateAndDraw(this->Timer->GetDeltaTime());

	primaryGame->Update(this);

	QuickTriggered::Draw();
	this->GetFont2D()->Draw(Vector2d(0, 0), COLOR_WHITE_3, 1, "Time: ");

}

void QuickTriggered::InitVPorts()
{
	this->CreateViewPort(0, 0, this->WinSizes.ClientWWidth,
		this->WinSizes.ClientWHeight, 0, 0, "NewPS");
}

void QuickTriggered::ReleaseDefault()
{
	BasicInterface::ReleaseDefault();
}

void QuickTriggered::Resize(enum EDisplayModes mode)
{

	D3DAPP::Resize(mode);

	this->Input->SetWinSizes(this->WinSizes);

	this->InitVPorts();

}
