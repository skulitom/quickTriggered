//#ifndef LINK_H
//#define LINK_H
//
//#include "Element.h"
//#include "Button.h"
//
//class Link;
//
//#define DX_LINK_SPAWNTYPE_NORMAL 0
//#define DX_LINK_SPAWNTYPE_DOT 1
//#define DX_LINK_SPAWNTYPE_PUSH 2
//
//struct LinkStruct
//{
//
//	std::vector<Link*> Links;
//
//};
//
//class Link : public Element
//{
//
//public:
//
//	//Link(D3DAPP* d3dApp, Vector2d& position, short indexOfVPort,
//	//	ElementsMLand* ptrToMotherLand, Link* pPrevLink = nullptr, __int8 DX_LINK_SPAWNTYPE_ = 0);
//	Link(ElementsMLand* ptrToMotherLand);
//
//	virtual ~Link();
//
//	virtual bool Update(float deltaTime) override;
//
//private:
//
//	Basic2DDraw* Draw2D;
//
//	LinkStruct LLinks;
//
//	bool IsLinkToMouse;
//	float TotalLifeTime;
//
//};
//
//#endif //LINK_H