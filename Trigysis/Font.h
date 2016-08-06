#ifndef FONT_H
#define FONT_H

#include "Basic2DDraw.h"
#include "Files.h"

#include <map>

struct GUIChar
{

	Vector2d Sizes;
	XMFLOAT2 TexCoords;

};

struct SDecoder
{

	char Sym;
	GUIChar* GUISym;

};

class FontManager;

class FontManager
{

public:

	FontManager(D3DAPP* d3dApp, Basic2DDraw* draw2d, char* fntFile);
	~FontManager();

	void DrawA(Vector2d& pos, XMFLOAT3& color, float scale, char* text, ...);
	void Draw(Vector2d& pos, XMFLOAT3& color, float scale, char* buffer);

private:

	void Render(Vector2d& pos, XMFLOAT3& color, float scale, char* buffer);

	bool CompileFile(char* fntFile);
	bool InitConstTexts();

	FileManager* CTFManager;

	std::vector<SDecoder> Decoder;

	float Size;

	//std::vector<Font*> FElements;

	std::string CTextFName;
	std::string MatName;

	Material* FontMaterial;

	D3DAPP* D3dApp;

	Basic2DDraw* Draw2d;

	BlendState* BState;

	bool NeedRender;
	bool Error;

};

#endif // !FONT_H
