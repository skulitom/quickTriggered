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
	//this->SetShapeType(DX_)
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
void QuickTriggered::BExit()
{

	PostQuitMessage(0);

}

void QuickTriggered::BToggleResButtons()
{

	for (int i = 0; i < this->Buttons.size(); i++)
	{

		if (!strcmp(this->Buttons.at(i)->GetIndName(0), "R"))
		{
			this->Buttons.at(i)->ToggleVisible();
		}
	}

}

void QuickTriggered::CheckResButtons()
{

	for (int i = 0; i < this->Buttons.size(); i++)
	{

		if (!strcmp(this->Buttons.at(i)->GetIndName(0), "R"))
		{
			if (!strcmp(this->Buttons.at(i)->GetIndName(1), "86") && this->Buttons.at(i)->GetStatus(DX_BUTTON_STATUS_CLICKED))
				this->Resize(DX_DISPLAY_MODE_800_600);
			else if (!strcmp(this->Buttons.at(i)->GetIndName(1), "1276") && this->Buttons.at(i)->GetStatus(DX_BUTTON_STATUS_CLICKED))
				this->Resize(DX_DISPLAY_MODE_1280_768);
		}
	}

}

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
		
		Element* NE = new Element(this);
		NE->SetSizesRelative(Vector2d(512, 512));
		NE->SetMaterial(std::string("Icon"));
		NE->Spawn(Vector2d(0, 0), 1);

		NE = new Element(this);
		NE->SetSizes(Vector2d(128, 128));
		NE->SetMaterial(std::string("ExplosionAnim"));
		NE->SetBlendState(DX_BS_TRANSPARENCY);
		NE->Spawn(Vector2d(100, 100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(100, -100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(-100, -100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(-100, 100), 1);

		/////////////////////////////////////
		//**InitButtons
		/////////////////////////////////////
		ButtonSettings SBS;
		SBS.IdleColor = XMFLOAT4(0, 0, 0, 0);
		SBS.InActiveColor = XMFLOAT4(0, 0, 0.25f, 0);
		SBS.MaterialName = std::string("Button");
		SBS.ReadyColor = XMFLOAT4(0.25, 0.25, 0.25, 0);
		SBS.SuppressColor = XMFLOAT4(0.5, 0.5, 0.5, 0);
		QTButton* NB = new QTButton(this, SBS);
		this->Buttons.push_back(NB);
		NB->SetSizes(Vector2d(80, 30));
		NB->SetFunc(DX_BUTTON_FUNC_TYPE_ONCLICK, &QuickTriggered::BToggleResButtons);
		NB->Spawn(Vector2d(0, 0), 1);
		NB->RenderText(Vector2d(-33, 0), COLOR_WHITE_3, 0.65f, "@B_QUIT");
		SBS.IsActive = false;
		SBS.IsVisible = false;
		NB = new QTButton(this, SBS);
		this->Buttons.push_back(NB);
		NB->SetSizes(Vector2d(80, 30));
		NB->Spawn(Vector2d(0, -30), 1);
		NB->RenderText(Vector2d(-20, 0), COLOR_BLACK_3, 0.5f, "800x600");//800600
		NB->SetIndName(0, "R");
		NB->SetIndName(1, "86");
		NB = new QTButton(this, SBS);
		this->Buttons.push_back(NB);
		NB->SetSizes(Vector2d(80, 30));
		NB->Spawn(Vector2d(0, -60), 1);
		NB->RenderText(Vector2d(-20, 0), COLOR_RED_3, 1.f, "1280x768");//1280768
		NB->SetIndName(0, "R");
		NB->SetIndName(1, "1276");
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

	Vector2d Pos;
	if (GetAsyncKeyState(VK_SPACE))
	{

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		Vector2d Pos = this->Input->GetMousePosCenterVPort(this->GetVPStruct(1));
		this->Fig1->Spawn(Pos, 1);

	}

	this->CheckResButtons();

	this->ElementBase->UpdateAndDraw(this->Timer->GetDeltaTime());
	
	//this->Font2D->Draw(Vector2d(-100, 0), COLOR_WHITE_3, "%d", this->Timer->GetFPS());

	//std::vector<int> Vec;
	//Vec.erase(Vec.begin() + 2);
	//Vec.clear();
	//Vec.shrink_to_fit();

	QuickTriggered::Draw();

}

void QuickTriggered::WorkWithButtons()
{



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