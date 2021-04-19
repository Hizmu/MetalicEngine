

#include "RenderShaders.h"
#include "BaseShaderLoader\BaseShaderLoader.h"

RenderShaders::RenderShaders(ID3D11Device* dev, ID3D11DeviceContext* devcon) : m_pdevice(dev), m_pdevcon(devcon) {};
RenderShaders::~RenderShaders(){	m_pBuffer->Release(); }


void RenderShaders::LoadShaderFromFile(ShaderParam*& param)
{
	if (param->ied != nullptr && param->IED_SIZE != 0)
	{
		m_ied = param->ied;
		m_iedsize = param->IED_SIZE;
	}
	param->blob = BaseShaderLoader::LoadShader(param->path.c_str(), param->EntryPoint, param->Version);
	if (param->blob == nullptr)
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_shared<WindowMessage>("Error load shader", WindowEventList::WindowErrorDebug));
}

void RenderShaders::LoadVertex(void* vertices, size_t bitesize)
{
	HRESULT result = S_OK;
	CreateBuffer(bitesize);
	D3D11_MAPPED_SUBRESOURCE ms;
	result = m_pdevcon->Map(m_pBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	if (FAILED(result))
		MessageBox(NULL, L"", L"", MB_OK);
	memcpy(ms.pData, vertices, bitesize);
	m_pdevcon->Unmap(m_pBuffer, NULL);
}

void RenderShaders::CreateAndSetInputLayout(VertexShader* vertex)
{
	HRESULT result = S_OK;
	result = m_pdevice->CreateInputLayout(m_ied,(UINT)m_iedsize, vertex->blob->GetBufferPointer(), vertex->blob->GetBufferSize(), &m_pinputlayout);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_shared<WindowMessage>("Error CreateInputLayout", WindowEventList::WindowErrorDebug));
		return;
	}
	m_pdevcon->IASetInputLayout(m_pinputlayout);
}

void RenderShaders::getBuffer(ID3D11Buffer*& buff)
{ buff = m_pBuffer; }
ID3D11InputLayout*& RenderShaders::getInputLayout()
{ 
	return m_pinputlayout; 
}
void RenderShaders::CreateBuffer(size_t bitesize)
{
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = (UINT)bitesize;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	m_pdevice->CreateBuffer(&bd, NULL, &m_pBuffer);
}
