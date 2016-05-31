//#include "Link.h"
//
//Link::Link(D3DAPP* d3dApp, Vector2d& position, short indexOfVPort,
//	ElementsMLand* ptrToMotherLand, Link* pPrevLink, __int8 DX_LINK_SPAWNTYPE_)
//	: Element(d3dApp, position, Vector2d(0,0), indexOfVPort, ptrToMotherLand, (bool)DX_LINK_SPAWNTYPE_)
//{
//
//	this->EName = "Link";
//
//	if ((DX_LINK_SPAWNTYPE_ == DX_LINK_SPAWNTYPE_PUSH) || (DX_LINK_SPAWNTYPE_ == DX_LINK_SPAWNTYPE_NORMAL) )
//	{
//
//		if (pPrevLink)
//		{
//
//			LLinks.Links.push_back(pPrevLink);
//
//		}
//
//		if (DX_LINK_SPAWNTYPE_ == DX_LINK_SPAWNTYPE_PUSH)
//			this->IsLinkToMouse = true;
//
//	}
//
//	this->Draw2D = this->PMLand->GetDraw2D();
//
//}
//
//Link::~Link()
//{
//
//
//
//}
//
//bool Link::Update(float deltaTime)
//{
//
//	if (!Element::Update(deltaTime))
//		return false;
//
//	this->TotalLifeTime = this->TotalLifeTime + deltaTime;
//
//	if (this->IsLinkToMouse)
//	{
//
//		if (this->LLinks.Links.size() == 0)
//			this->Position = this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->IndexOfViewPort));
//
//		if (this->LLinks.Links.size() == 1)
//		{
//
//			if (this->LLinks.Links.back())
//			{
//
//				if (abs(this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->IndexOfViewPort)).X 
//					- this->LLinks.Links.back()->Position.X) <
//					abs(this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->IndexOfViewPort)).Y
//					- this->LLinks.Links.back()->Position.Y))
//				{
//					this->Position.X = this->LLinks.Links.back()->Position.X;
//					this->Position.Y = this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->IndexOfViewPort)).Y;
//				}
//				else
//				{
//
//					this->Position.Y = this->LLinks.Links.back()->Position.Y;
//					this->Position.X = this->Input->GetMousePosCenterVPort(this->D3dApp->GetViewPort(this->IndexOfViewPort)).X;
//
//				}
//
//			}
//
//		}
//
//
//		if (this->TotalLifeTime >= 1 && (this->Input->GetStatus() == DX_MOUSE_DOWN_LEFT))
//		{
//
//			this->IsLinkToMouse = false;
//
//		}
//
//	}
//
//	if (this->IsNeedRender)
//		this->Draw2D->DrawCircle(this->Position, 5, XMFLOAT4(0, 0, 1, 1));
//
//	for (size_t i = 0; i < this->LLinks.Links.size(); i++)
//	{
//
//		if (this->LLinks.Links.at(i))
//		{
//
//			this->Draw2D->DrawLine(this->Position, this->LLinks.Links.at(i)->GetPosition(), XMFLOAT4(0, 0, 1, 1),
//				this->IndexOfViewPort);
//
//		}
//
//	}
//
//}
//
