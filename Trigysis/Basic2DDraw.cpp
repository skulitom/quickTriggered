#include "Basic2DDraw.h"

Basic2DDraw::Basic2DDraw(D3DAPP* d3dApp)
{

	this->Shader = nullptr;
	this->D3dApp = nullptr;

	this->D3dApp = d3dApp;
	ShaderManager* RS = new ShaderManager(this->D3dApp, SHADER_MODEL_4_0);

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
	//this->Vertices[0].Pos = pos1;
	//this->Vertices[0].Color = color;
	//this->Vertices[1].Pos = pos2;
	//this->Vertices[1].Color = color;
	//D3D11_MAPPED_SUBRESOURCE MSR;
	//this->D3dApp->DeviceContext->Map(this->Shader->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
	//memcpy(MSR.pData, &this->Vertices, sizeof(Basic2DDrawPipeline::Vertex2d) * 2);
	//this->D3dApp->DeviceContext->Unmap(this->Shader->GetVertexBuffer(), 0);
	/////////////////////////////////////////////////////////
	////**Set Topology, InputLayout, RastState
	/////////////////////////////////////////////////////////
	//this->Shader->SetShaderResourceView(nullptr);
	//this->D3dApp->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//this->Shader->Apply(indexOfVP);
	//this->D3dApp->DeviceContext->Draw(2, 0);
}

void Basic2DDraw::DrawTriangle(Vector2d& pos1, Vector2d& pos2, Vector2d& pos3,
	Vector2d& tPos1, Vector2d& tPos2, Vector2d& tPos3, short indexOfVP, XMFLOAT4& color)
{
	//this->Vertices[0].Pos = pos1;
	//this->Vertices[0].Color = color;
	//this->Vertices[1].Pos = pos2;
	//this->Vertices[1].Color = color;
	//this->Vertices[2].Pos = pos3;
	//this->Vertices[2].Color = color;
	//D3D11_MAPPED_SUBRESOURCE MSR;
	//this->D3dApp->DeviceContext->Map(this->Shader->GetVertexBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MSR);
	//memcpy(MSR.pData, &this->Vertices[0], sizeof(Basic2DDrawPipeline::Vertex2d) * 3);
	//this->D3dApp->DeviceContext->Unmap(this->Shader->GetVertexBuffer(), 0);
	//this->D3dApp->DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//this->PMatrix = XMFLOAT4X4(pos1.X, pos1.Y, tPos1.X, tPos1.Y, pos2.X, pos2.Y, tPos2.X, tPos2.Y, pos3.X, pos3.Y, tPos3.X, tPos3.Y,
	//	color.x, color.y, color.z, color.w);
	//this->Shader->ApplyTriangle(indexOfVP, this->PMatrix);
	//this->D3dApp->DeviceContext->Draw(3, 0);
}

void Basic2DDraw::UpdateMaterial(Material* pMaterial)
{

	if (pMaterial)
	{

		if (pMaterial->Texture)
		{

			if (pMaterial->Animate.w)
			{

				pMaterial->LFrameTime = pMaterial->LFrameTime + this->D3dApp->GetTimer()->GetDeltaTime();

				if (pMaterial->LFrameTime >= (float)(pMaterial->Animate.z) / 1000.f)
				{
					pMaterial->LFrameTime = 0;

					pMaterial->LFrameIndex++;
					pMaterial->LFrameIndex = pMaterial->LFrameIndex % pMaterial->Animate.x;

					//Надо занести в TAS
					INT DIndex = (pMaterial->Animate.w / pMaterial->Animate.y);
					pMaterial->TextureOffset.x = (float)(pMaterial->Animate.y * (pMaterial->LFrameIndex % DIndex)) / pMaterial->Animate.w;
					pMaterial->TextureOffset.y = (float)(pMaterial->Animate.y * (pMaterial->LFrameIndex / DIndex)) / pMaterial->Animate.w;

					//XMMATRIX MM = XMMatrixSet(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, TexAnimSettings.Coord.x / TexAnimSettings.Size.x, TexAnimSettings.Coord.y / TexAnimSettings.Size.y, 0.f, 1.f);

					//this->TexAnimSettings.Transform._41 = 0;
					//this->TexAnimSettings.Transform._42 = 0;

					//XMStoreFloat4x4(&this->TexAnimSettings.Transform, XMMatrixMultiply(XMLoadFloat4x4(&this->TexAnimSettings.Transform), MM));

				}

			}
			else
			{

				pMaterial->TextureOffset.x = pMaterial->TextureOffset.x + pMaterial->TextureMove.x * this->D3dApp->GetTimer()->GetDeltaTime();
				pMaterial->TextureOffset.y = pMaterial->TextureOffset.y + pMaterial->TextureMove.y * this->D3dApp->GetTimer()->GetDeltaTime();

			}

		}

		if (pMaterial->AdditionalTexture)
		{

			pMaterial->TextureOffset.z = pMaterial->TextureOffset.z + pMaterial->TextureMove.z * this->D3dApp->GetTimer()->GetDeltaTime();
			pMaterial->TextureOffset.w = pMaterial->TextureOffset.w + pMaterial->TextureMove.w * this->D3dApp->GetTimer()->GetDeltaTime();

		}

	}

}

void Basic2DDraw::DrawRectangle(Vector2d& pos, float rotation, Vector2d& sizes, short indexOfVP, XMFLOAT4& userVars,
	XMFLOAT4& color, Material* pMaterial, XMFLOAT4& aColor)
{

	if (pMaterial)
	{

		this->UpdateMaterial(pMaterial);
		this->Shader->Render(indexOfVP, color, pos, rotation, sizes, pMaterial, userVars, aColor);

		this->D3dApp->DeviceContext->DrawIndexed(BASIC_2DDRAWP_RECTANGLE_I_NUM, BASIC_2DDRAWP_RECTANGLE_I_START, 0);

	}

}

void Basic2DDraw::DrawHexagon(Vector2d& pos, Vector2d& sizes, short indexOfVP, XMFLOAT4& userVars,
	XMFLOAT4& color, Material* pMaterial, XMFLOAT4& aColor)
{

	if (pMaterial)
	{

		this->UpdateMaterial(pMaterial);
		this->Shader->Render(indexOfVP, color, pos,0 , sizes, pMaterial, userVars, aColor);

		this->D3dApp->DeviceContext->DrawIndexed(BASIC_2DDRAWP_HEXAGON_I_NUM, BASIC_2DDRAWP_HEXAGON_I_START, 0);

	}

}
