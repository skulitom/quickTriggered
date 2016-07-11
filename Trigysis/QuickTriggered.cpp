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
		//this->TPipeline = new TestPipeline(this, SHADER_MODEL_4_0);
		/////////////////////////////////////
		//**Create BackGrounds
		/////////////////////////////////////

		this->CreateViewPort(0, 0, this->WinSizes.ClientWWidth,
			this->WinSizes.ClientWHeight, 0, 0, "NewPS");
		//this->CreateViewPort(this->WinSizes.ClientWWidth*0.5f, 0, this->WinSizes.ClientWWidth * 0.5f,
		//	this->WinSizes.ClientWHeight*0.5f, 0, 0);
		//this->CreateViewPort(0, this->WinSizes.ClientWHeight*0.5f, this->WinSizes.ClientWWidth * 0.5f,
		//	this->WinSizes.ClientWHeight*0.5f, 0, 0);

		this->InitVPShaders();
		
		Element* NE = new Element(this);
		NE->SetSizesRelative(Vector2d(512, 512));
		NE->SetMaterial(std::string("Icon"));
		NE->Spawn(Vector2d(0, 0), 1);

		//NE = new Element(this);
		//NE->SetSizes(Vector2d(80, 80));
		//NE->SetMaterial(std::string("DonaldLow"));
		//NE->Spawn(Vector2d(60, -60), 1);

		//NE = new Element(this);
		//NE->SetSizes(Vector2d(256, 256));
		//NE->SetMaterial(std::string("DonaldHD"));
		//NE->Spawn(Vector2d(0, 0), 2);

		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{

		//		Figure* F = new Figure(this);
		//		F->SetFigureSuperType(0);
		//		F->SetFigureType(0);
		//		F->Spawn(Vector2d((i - 3) * 64, (j - 3)*64), 1);

		//	}
		//}

		//for (int i = 0; i < 4; i++)
		//{
		//	for (int j = 0; j < 4; j++)
		//	{

		//		Figure* F = new Figure(this);
		//		F->SetFigureSuperType(0);
		//		F->SetFigureType(0);
		//		F->Spawn(Vector2d((i - 3) * 64, (j - 3) * 64), 2);

		//	}
		//}

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(-100, -100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(100, -100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(100, 100), 1);

		this->Fig1 = new Figure(this);
		this->Fig1->SetFigureSuperType(0);
		this->Fig1->SetFigureType(0);
		this->Fig1->Spawn(Vector2d(-100, 100), 1);

		//this->Fig1 = new Figure(this);
		//this->Fig1->SetFigureSuperType(0);
		//this->Fig1->SetFigureType(0);
		//this->Fig1->Spawn(Vector2d(0, 0), 2);

		//F->MoveDirect(Vector2d(-100, -100), 100);

		//Figure* F = new Figure(this);
		//F->SetFigureSuperType(1);
		//F->SetFigureType(0);
		//F->Spawn(Vector2d(1, 0), 2);

		return true;

	}

	return false;
}

void QuickTriggered::Update()
{
	
	////////////////////////////////////////////////
	//**Render Update
	////////////////////////////////////////////////

	
	//Figure* FigureToWork = nullptr;
	//for (int i = 0; i < this->ElementBase->GetElements().size(); i++)
	//{
		
		//if (this->ElementBase->GetElements().at(i)->GetEName() == "Figure")
		//{

			//FigureToWork = dynamic_cast<Figure*>(this->ElementBase->GetElements().at(i));
			//if (this->Input->GetStatus() == DX_MOUSE_DOWN_LEFT)
				//FigureToWork->MoveDirect(this->Input->GetMousePosCenterVPort(this->GetViewPort(0)), 100);

		//}

	//}

	//if (this->Input->GetStatus() == DX_MOUSE_DOWN_LEFT)
	//	this->Fig1->MoveDirect(this->Input->GetMousePosCenterVPort(this->GetViewPort(0)),100);

	//this->Draw2D->DrawRectangle(Vector2d(0, 0), Vector2d(64, 64), 0, XMFLOAT4(0, 0, 0, 0), NULL, std::string("DTBF.dds"));

	//this->Draw2D->DrawHexagon(this->Input->GetMousePosCenterVPort(this->ViewPorts[0].VPort), Vector2d(10, 10), 0, XMFLOAT4(1, 0, 0, 1));
	//this->Draw2D->DrawHexagon(Vector2d(0, 0), Vector2d(50, 50), 0, XMFLOAT4(1, 0, 0, 1));

	this->Draw2D->GetShaderManager()->SetFilter();

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

	//this->SetRenderTarget(this->ViewPorts[1].RTView);
	//this->TPipeline->Apply(this->ViewPorts[1].TextureToRender, 1, XMFLOAT4(0,0,0,1),this->ViewPorts[1].WorldPos, 
	//	Vector2d(this->ViewPorts[1].VPort.Width, this->ViewPorts[1].VPort.Height));
	//this->DeviceContext->

	QuickTriggered::Draw();

}

void QuickTriggered::ReleaseDefault()
{
	//D3DDelete(this->ElementsBase);
	//D3DDelete(this->TPipeline);
	BasicInterface::ReleaseDefault();
}