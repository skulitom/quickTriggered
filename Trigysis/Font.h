#ifndef FONT_H
#define FONT_H

#include "Basic2DDraw.h"
#include "Files.h"

#include <map>

struct GUIChar
{

	Vector2d Sizes;
	XMFLOAT2 TexCoords;
	INT XOffSet;
	INT YOffSet;

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

	FontManager(D3DAPP* d3dApp, Basic2DDraw* draw2d, char* fntFile, char* loc = "en");
	~FontManager();

	void DrawA(Vector2d& pos, XMFLOAT3& color, float scale, const char* text, ...);
	void Draw(Vector2d& pos, XMFLOAT3& color, float scale, const char* buffer);

private:

	void Render(Vector2d& pos, XMFLOAT3& color, float scale, const char* buffer);
	const char* GetLocText(const char* key);

	bool CompileFile(char* fntFile);
	bool InitConstTexts();

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

	std::map<std::string, std::string> LocMap;
	char* Locale;

};

#endif // !FONT_H
