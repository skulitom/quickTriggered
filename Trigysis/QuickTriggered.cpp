#include "QuickTriggered.h"

//////////////////////////////////////////////////////
//**QTButton
//////////////////////////////////////////////////////
QTButton::QTButton(BasicInterface* super, ButtonSettings& bs)
:ButtonInterface(super, bs)
{
	DeclareElementName(CCButton, this->EName);
	this->Sizes = Vector2d(50, 30);
	this->PQTClass = dynamic_cast<QuickTriggered*>(this->D3dApp);
}

void QTButton::SetFunc(unsigned short DX_BUTTON_FUNC_TYPE_, QTFunc qtf)
{
	switch (DX_BUTTON_FUNC_TYPE_)
	{
		case DX_BUTTON_FUNC_TYPE_ONSELECT:
		{
			this->QTFOnSelect = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONSELECT;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONPRESS:
		{
			this->QTFOnPress = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONPRESS;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONCLICK:
		{
			this->QTFOnClick = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONCLICK;
			return;
		}
		case DX_BUTTON_FUNC_TYPE_ONSTOPINQUISITION:
		{
			this->QTFOnStopInquisition = qtf;
			this->Feature |= DX_BUTTON_FEATURE_ONSTOPINQUISITION;
			return;
		}
	}
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
		this->SInitMaterials();
		/////////////////////////////////////
		//**Create BackGrounds
		/////////////////////////////////////

		this->InitVPorts();

		this->InitVPShaders();
		
		Element* NE = new Element(this);
		NE->SetSizesRelative(Vector2d(512, 512));
		NE->SetMaterial(std::string("Icon"));
		NE->Spawn(Vector2d(0, 0), 1);

		setBoard();

		return true;

	}

	return false;
}

void QuickTriggered::setBoard()
{
	for (int i = -BOARD_SIZE; i <= BOARD_SIZE; i += BOARD_INTERVAL)
	{
		for (int j = -BOARD_SIZE; j <= BOARD_SIZE; j += BOARD_INTERVAL)
		{
			createFigure(i, j);
		}
	}
}


void QuickTriggered::createFigure(int x, int y)
{
	this->Fig1 = new Figure(this);
	this->Fig1->SetFigureSuperType(0);
	this->Fig1->SetFigureType(0);
	this->Fig1->Spawn(Vector2d(x, y), 1);
}


void QuickTriggered::Update()
{
	
	////////////////////////////////////////////////
	//**Render Update
	////////////////////////////////////////////////

	if (GetAsyncKeyState('1'))
		this->Resize(DX_DISPLAY_MODE_800_600);
	else if (GetAsyncKeyState('2'))
		this->Resize(DX_DISPLAY_MODE_1360_768);
	else if (GetAsyncKeyState('3'))
		this->Resize(DX_DISPLAY_MODE_1920_1080);

	Vector2d Pos;
	if (GetAsyncKeyState(VK_SPACE))
	{

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		Vector2d Pos = this->Input->GetMousePosCenterVPort(this->GetVPStruct(1));
		this->Fig1->Spawn(Pos, 1);

	}

	this->ElementBase->UpdateAndDraw(this->Timer->GetDeltaTime());

	QuickTriggered::Draw();

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