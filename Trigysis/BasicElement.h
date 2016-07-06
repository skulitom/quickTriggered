#ifndef BASIC_ELEMENT_H
#define BASIC_ELEMENT_H
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

#define PrepareShader(pMaterial, pSManager){										 \
	if(pMaterial->ShaderName != "")	{												 \
		pMaterial->EffectShader = pSManager->GetPixelShader(pMaterial->ShaderName);  \
		pMaterial->ShaderName = ""; }}												
	 

#define EL_SHAPE_TYPE_RECTANGLE 0
#define EL_SHAPE_TYPE_HEXAGON 1

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
	void AddPrimaryShader(char* shaderName);
	Vector2d& GetPosition() { return this->Position; }
	Vector2d& GetSizes() { return this->Sizes; }
	virtual void SetIsNeedRender(bool isNeedRender) { this->IsNeedRender = isNeedRender; }
	bool GetIsNeedRender() { return this->IsNeedRender; }
	void SetColors(XMFLOAT4& color) { this->Color = color; }
	XMFLOAT4 GetColors() { return this->Color; }
	void SetIndexOfViewPort(short indexOfVPort) { this->IndexOfViewPort = indexOfVPort; }
	short GetIndexOfViewPort() { return this->IndexOfViewPort; }
	bool SetMaterial(std::string& materialName);
	bool SetMaterial(Material* pMaterial);
	Material* GetMaterial() { return this->MaterialPtr; }
	virtual bool Update(FLOAT deltaTime) { return true; }
	bool GetIsFired() { return this->IsFired; }
	void SetIsFired(bool isFired) { this->IsFired = isFired; }
	std::string& GetEName() { return this->EName; }
	void SetInput(D3DAPPINPUT* input) { this->Input = input; }
	D3DAPPINPUT* GetInput() { return this->Input; }
	virtual void Delete() { this->SetIsFired(true); }
	bool GetIsSpawned() { return this->IsSpawned; }
	ElementsMLand* GetPMLand(){ return this->PMLand; }
	__int8 GetShapeType(){ return this->ShapeType; }
	void SetShapeType(__int8 shapeType) { this->ShapeType = shapeType; }
	XMFLOAT4& GetCustomVars(){ return this->CustomVars; }
	void SetCustomVars(XMFLOAT4& customVars){ this->CustomVars = customVars; }
protected:
	Material* MaterialPtr;
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
	__int8 ShapeType;
	XMFLOAT4 CustomVars;
};

//////////////////////////////////////////////
//**ElementsMLand
//////////////////////////////////////////////
class ElementsMLand
{
public:
	ElementsMLand(D3DAPP* d3dApp, D3DAPPINPUT* input,Basic2DDraw* draw2D, std::string& saveBufferName = std::string());
	~ElementsMLand();
	void AddNewElement(ElementInterface* pNewElement);
	void DeleteElement(const UINT indexOfVP, const UINT indexOfElement);
	std::vector<ElementInterface*> GetElements(const UINT indexOfVP) { return this->Elements.at(indexOfVP); }
	void UpdateAndDraw(FLOAT deltaTime);
	D3DAPP* GetD3DApp() { return this->D3dApp; }
	Basic2DDraw* GetDraw2D() { return this->Draw2D; }
	void SetIsLoadMode(bool isLoadMode);
	bool GetIsLoadMode() { return this->IsLoadMode; }
	FileManager* GetFManager() { return this->FManager; }
	void LoadShaders();
	
private:

	void LoadElements();

private:

	D3DAPP* D3dApp;
	std::vector<std::vector<ElementInterface*>> Elements;
	ID3D11Buffer* VertexBuffer; //<-Ch
	ID3D11Buffer* IndexBuffer; //<-Ch
	ID3D11InputLayout* InputLayout; //<-Ch
	D3DAPPINPUT* Input;
	Basic2DDraw* Draw2D;
	bool IsLoadMode;
	FileManager* FManager;
};

#endif// !BASIC_ELEMENT_H