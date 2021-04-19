#include "WorldViewProjectionMattrix.h"


WorldViewProjectionMatrix::WorldViewProjectionMatrix(ID3D11Device* device, ID3D11DeviceContext* devcon)
{
	if (device == nullptr || devcon == nullptr)
	{
		Logs::Log::GetLog()->MsgPrint("Init WorldViewProjectionMatrix FALSE. Arguments not initialized ", Logs::TypeLogs::Warning);
		return;
	}
	m_pdevice = device;
	m_pdevcon = devcon;
}

void WorldViewProjectionMatrix::InitMatrix(XMMATRIX& matProjection, XMMATRIX& matView, XMMATRIX& matWorld)
{
	if (FAILED(this->CreateWVPBuffer()))
		return;
	constbuffers = new VS_CONSTANT_BUFFER;
	constbuffers->projectionMatrix = XMMatrixTranspose(matProjection);
	constbuffers->viewMatrix = XMMatrixTranspose(matView);
	constbuffers->worldMatrix = XMMatrixTranspose(matWorld);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &constbuffers;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;

	HRESULT result = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER);
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	//result = m_pdevice->CreateBuffer(&bd, &InitData, &this->m_constbuff);

	//m_pdevcon->VSSetConstantBuffers(0, 1, &this->m_constbuff);
//	m_pdevcon->UpdateSubresource(*&this->m_constbuff, 0, 0, constbuffers, 0, 0);
}

HRESULT WorldViewProjectionMatrix::CreateWVPBuffer()
{
	return S_OK;
}

XMMATRIX WorldViewProjectionMatrix::getProjectionMatrix()
{
	return constbuffers->projectionMatrix;
}
XMMATRIX WorldViewProjectionMatrix::getViewnMatrix()
{
	return constbuffers->viewMatrix;
}
XMMATRIX WorldViewProjectionMatrix::getWorldnMatrix()
{
	return constbuffers->worldMatrix;
}