#ifndef RENDER_QUAD_RANGLE_H
#define RENDER_QUAD_RANGLE_H
#include "D3DAPP.h"
#include "Vector2d.h"
#include "Basic2DDraw.h"
#include "Files.h"
#include <vector>
class ElementsMLand;
class ElementInterface;

#define ElementDelete(x) {if(x){x->Delete();}}

#define RegisterElement(classTypeName, ptrToMLand, sFinder) \
	if(sFinder == #classTypeName){						    \
	classTypeName* NC = new classTypeName(ptrToMLand);  	\
	NC->Spawn(NC->GetPosition(), NC->GetIndexOfViewPort());} 

#define DeclareElementName(classTypeName, returnName) \
	returnName = #classTypeName;

#define ProtectPtr(ptr) {if(ptr!=nullptr) ptr = nullptr;}
#define ProtectPtrArray(ptr, arraySize) \
	for(int i = 0; i < arraySize; i++) \
		ProtectPtr(ptr[i]);

class ElementInterface
{
public:
	ElementInterface(D3DAPP* d3dApp, Vector2d& position, Vector2d& sizes, short indexOfVPort, 
		ElementsMLand* ptrToMotherLand, bool isNeedRender = true);
	ElementInterface(ElementsMLand* ptrToMotherLand);
	virtual ~ElementInterface() {}
	virtual void Spawn(Vector2d& position, short indexOfVPort);
	virtual void SetPosition(Vector2d& position) { this->Position = position; }
	virtual void SetSizes(Vector2d& sizes) { this->Sizes = sizes; }
	virtual void SetSizesRelative(Vector2d& sizes, short indexOfVPort = -1);
	Vector2d& GetPosition() { return this->Position; }
	Vector2d& GetSizes() { return this->Sizes; }
	virtual void SetIsNeedRender(bool isNeedRender) { this->IsNeedRender = isNeedRender; }
	bool GetIsNeedRender() { return this->IsNeedRender; }
	void SetColors(XMFLOAT4& color) { this->Color = color; }
	XMFLOAT4 GetColors() { return this->Color; }
	void SetIndexOfViewPort(short indexOfVPort) { this->IndexOfViewPort = indexOfVPort; }
	short GetIndexOfViewPort() { return this->IndexOfViewPort; }
	bool SetTexture(std::string& textureName);
	ID3D11ShaderResourceView* GetTextureViewPtr() { return this->TextureView; }
	virtual bool Update(FLOAT deltaTime) { return true; }
	bool GetIsFired() { return this->IsFired; }
	void SetIsFired(bool isFired) { this->IsFired = isFired; }
	std::string& GetEName() { return this->EName; }
	void SetInput(D3DAPPINPUT* input) { this->Input = input; }
	D3DAPPINPUT* GetInput() { return this->Input; }
	virtual void Delete() { this->SetIsFired(true); }
	bool GetIsSpawned() { return this->IsSpawned; }
	ElementsMLand* GetPMLand(){ return this->PMLand; }
protected:
	ID3D11ShaderResourceView* TextureView;
	Vector2d Position;
	Vector2d Sizes;
	XMFLOAT4 Color;
	INT IndexOfViewPort; //short
	BOOL IsNeedRender;
	std::string EName;
	BOOL IsFired; //bool
	ElementsMLand* PMLand;
	D3DAPPINPUT* Input;
	D3DAPP* D3dApp;
	BOOL IsSpawned;
};

//////////////////////////////////////////////
//**ElementsMLand
//////////////////////////////////////////////
class ElementsMLand
{
public:
	ElementsMLand(D3DAPP* d3dApp, D3DAPPINPUT* input, std::string& saveBufferName = std::string());
	~ElementsMLand();
	void AddNewElement(ElementInterface* pNewElement);
	void DeleteElement(ElementInterface* pElementToDelete);
	std::vector<ElementInterface*> GetElements() { return this->Elements; }
	void UpdateAndDraw(FLOAT deltaTime);
	D3DAPP* GetD3DApp() { return this->D3dApp; }
	Basic2DDraw* GetDraw2D() { return this->Draw2D; }
	void SetIsLoadMode(bool isLoadMode);
	bool GetIsLoadMode() { return this->IsLoadMode; }
	FileManager* GetFManager() { return this->FManager; }
	
private:

	void LoadElements();

private:

	D3DAPP* D3dApp;
	std::vector<ElementInterface*> Elements;
	ID3D11Buffer* VertexBuffer; //<-Ch
	ID3D11Buffer* IndexBuffer; //<-Ch
	ID3D11InputLayout* InputLayout; //<-Ch
	D3DAPPINPUT* Input;
	Basic2DDraw* Draw2D;
	bool IsLoadMode;
	FileManager* FManager;
};

class Element : public ElementInterface
{

public:
	Element(ElementsMLand* ptrToMotherLand);

	virtual ~Element() {}

private:

};

#endif// RENDER_QUAD_RANGLE_H