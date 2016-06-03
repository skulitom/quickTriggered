#include "Basic2DDraw.h"

Basic2DDraw::Basic2DDraw(D3DAPP* d3dApp)
{
	this->D3dApp = d3dApp;
	Basic2DDrawPipeline* RS = new Basic2DDrawPipeline(this->D3dApp);
	RS->CreateVertexShader("B2DVShader.fx", "VSMain");
	RS->CreatePixelShader("B2DPShader.fx", "PSMain");
	this->Shader = RS;
	if (!this->D3dApp->SetDepthStencilStateByIndex(DX_RS_2D_RENDER_STATE))
		return;
}

void Basic2DDraw::DrawCircle(Vector2d & pos, FLOAT radius, XMFLOAT4& color, short indexOfVP)
{
	float NewX, NewY, NewX2, NewY2;
	for (float Theta = 0; Theta < D3DX_PI * 2 - 0.01f; Theta = Theta + 0.01f)
	{
		NewX = -radius*sinf(Theta);
		NewY = radius*cosf(Theta);
		NewX2 = -radius*sinf(Theta + 0.01f);
		NewY2 = radius*cosf(Theta + 0.01f);
		this->DrawLine(Vector2d(NewX, NewY) + pos, Vector2d(NewX2, NewY2) + pos, color, indexOfVP);
	}
}

void Basic2DDraw::DrawLine(Vector2d & pos1, Vector2d & pos2, XMFLOAT4 & color, short indexOfVP)
{
	this->Vertices[0].Pos = pos1;
	this->Vertices[0].Color = color;
	this->Vertices[1].Pos = pos2;
	this->Vertices[1].Color = color;
	D3D11_MAPPED_SUBRESOURCE MSR;
	this->D3dApp->dxDeviceCon->Map(this->Shader->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
	memcpy(MSR.pData, &this->Vertices, sizeof(Basic2DDrawPipeline::Vertex2d) * 2);
	this->D3dApp->dxDeviceCon->Unmap(this->Shader->GetVertexBuffer(), 0);
	///////////////////////////////////////////////////////
	//**Set Topology, InputLayout, RastState
	///////////////////////////////////////////////////////
	this->Shader->SetShaderResourceView(nullptr);
	this->D3dApp->dxDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	this->Shader->Apply(indexOfVP);
	this->D3dApp->dxDeviceCon->Draw(2, 0);
}

void Basic2DDraw::DrawTriangle(Vector2d& pos1, Vector2d& pos2, Vector2d& pos3, short indexOfVP, XMFLOAT4 color)
{
	this->Vertices[0].Pos = pos1;
	this->Vertices[0].Color = color;
	this->Vertices[1].Pos = pos2;
	this->Vertices[1].Color = color;
	this->Vertices[2].Pos = pos3;
	this->Vertices[2].Color = color;
	D3D11_MAPPED_SUBRESOURCE MSR;
	this->D3dApp->dxDeviceCon->Map(this->Shader->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
	memcpy(MSR.pData, &this->Vertices[0], sizeof(Basic2DDrawPipeline::Vertex2d) * 3);
	this->D3dApp->dxDeviceCon->Unmap(this->Shader->GetVertexBuffer(), 0);
	this->D3dApp->dxDeviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	this->Shader->Apply(indexOfVP);
	this->D3dApp->dxDeviceCon->Draw(3, 0);
}

void Basic2DDraw::DrawRectangle(Vector2d& pos, Vector2d& sizes, short indexOfVP, XMFLOAT4 color, 
	ID3D11ShaderResourceView* pTexture, std::string& textureName)
{
	if (!pTexture && textureName != "")
		pTexture = this->D3dApp->GetTextureViewPtr(textureName);
	if (pTexture)
	{
		this->Vertices[0].TexturePos = Vector2d(0, 0);
		this->Vertices[1].TexturePos = Vector2d(1, 0);
		this->Vertices[2].TexturePos = Vector2d(0, 1);
	}
	this->Shader->SetShaderResourceView(pTexture);
	this->DrawTriangle(Vector2d(pos.X - sizes.X * 0.5f, pos.Y + sizes.Y * 0.5f), pos + sizes * 0.5f,
		pos - sizes * 0.5f, indexOfVP, color);
	if (pTexture)
	{
		this->Vertices[0].TexturePos = Vector2d(0, 1);
		this->Vertices[1].TexturePos = Vector2d(1, 0);
		this->Vertices[2].TexturePos = Vector2d(1, 1);
	}
	this->DrawTriangle(pos - sizes * 0.5f, pos + sizes * 0.5f,
		Vector2d(pos.X + sizes.X * 0.5f, pos.Y - sizes.Y * 0.5f), indexOfVP, color);
}