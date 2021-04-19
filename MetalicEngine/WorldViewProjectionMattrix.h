#pragma once

#include "Application\IApplication.h"
#include "SystemLog\Log.h"


struct VS_CONSTANT_BUFFER
{
	XMMATRIX worldMatrix;
	XMMATRIX viewMatrix;
	XMMATRIX projectionMatrix;
};

class WorldViewProjectionMatrix
{
public:
	WorldViewProjectionMatrix() = delete;
	WorldViewProjectionMatrix(ID3D11Device* device, ID3D11DeviceContext* devcon);


	void InitMatrix(XMMATRIX& matProjection, XMMATRIX& matView, XMMATRIX& matWorld);
	XMMATRIX getProjectionMatrix();
	XMMATRIX getViewnMatrix();
	XMMATRIX getWorldnMatrix();
	HRESULT CreateWVPBuffer();
private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pdevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pdevcon;	

	ID3D11Buffer* m_constbuff;
	VS_CONSTANT_BUFFER* constbuffers = {};
};