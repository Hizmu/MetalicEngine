
#include "Application/IApplication.h"
#include "SystemLog\Log.h"
#include "GraphicSystem\Camera\Camera.h"

#include "WorldViewProjectionMattrix.h"
#include "Shader\RenderShaders.h"
#include "Vertex.h"

void Main()
{

	RenderingInterfaces interf = IApplication::getApplication()->getRenderSystem()->getRenderInterfaces();
	IApplication::getApplication()->getRenderSystem()->setBackgroundColor(COLOR::TEAL);
	ShaderParam* vertexshader = new VertexShader();
	ShaderParam* pixelshader = new PixelShader();

	vertexshader->EntryPoint = "VShader";

	wchar_t temp[256];
	ProjectPath(temp, 256);

	vertexshader->path = temp;

	vertexshader->path += L"\\HLSL\\VertexShader.hlsl";
	vertexshader->Version = "vs_4_0";
	pixelshader->path = temp;
	pixelshader->path += L"\\HLSL\\VertexShader.hlsl";

	pixelshader->EntryPoint = "PShader";
	pixelshader->Version = "ps_4_0";


	vertexshader->ied = new D3D11_INPUT_ELEMENT_DESC[2];
	vertexshader->ied[0].SemanticName = "SV_POSITION";
	vertexshader->ied[0].SemanticIndex = 0;
	vertexshader->ied[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	vertexshader->ied[0].InputSlot = 0;
	vertexshader->ied[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	vertexshader->ied[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	vertexshader->ied[0].InstanceDataStepRate = 0;

	vertexshader->ied[1].SemanticName = "COLOR";
	vertexshader->ied[1].SemanticIndex = 0;
	vertexshader->ied[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	vertexshader->ied[1].InputSlot = 0;
	vertexshader->ied[1].AlignedByteOffset = 12;
	vertexshader->ied[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	vertexshader->ied[1].InstanceDataStepRate = 0;
	/*
	vertexshader->ied[2].SemanticName = "TEXCOORD";
	vertexshader->ied[2].SemanticIndex = 0;
	vertexshader->ied[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	vertexshader->ied[2].InputSlot = 0;
	vertexshader->ied[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	vertexshader->ied[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	vertexshader->ied[2].InstanceDataStepRate = 0;
	*/
	vertexshader->IED_SIZE = 2;

	RenderShaders* rendershaders = new RenderShaders(interf.m_pdevice.Get(), interf.m_pdvcontext.Get());
	rendershaders->LoadShaderFromFile(vertexshader);
	rendershaders->LoadShaderFromFile(pixelshader);
	vertexshader->CreateShader(interf.m_pdevice.Get(), interf.m_pdvcontext.Get());
	pixelshader->CreateShader(interf.m_pdevice.Get(), interf.m_pdvcontext.Get());
	rendershaders->LoadVertex(vertex, sizeof(vertex));
	rendershaders->CreateAndSetInputLayout((VertexShader*)vertexshader);

	//WorldViewProjectionMatrix* mat = new WorldViewProjectionMatrix(interf.m_pdevice.Get(), interf.m_pdvcontext.Get());
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	ID3D11Buffer* buff;
	rendershaders->getBuffer(buff);
	interf.m_buffer = buff;
	interf.m_inputLayout = rendershaders->getInputLayout();
	interf.m_pdvcontext->IASetVertexBuffers(0, 1, interf.m_buffer.GetAddressOf(), &stride, &offset);

	//unsigned int t = 0xA215CFE6;
//	unsigned int a = (0xff000000 & (int)t) >> 32;
//	unsigned int e = (0x00ff0000 & (int)t) >> 16;
//	unsigned int z = (0x0000ff00 & (int)t) >> 8;
//	unsigned int f = (0x000000ff & (int)t);
//	unsigned int i = ;
	/*
	Camera cam;
	cam.setPosition(0.0f, 0.0f, -0.5f);

	cam.Render();
	float fieldofView = DirectX::XM_PI / 4.0f ;
	float screenDepth = 1000.0f;
	float screenNear = 0.1f;


	XMMATRIX orthoMatrix = XMMatrixOrthographicLH((float)IApplication::getApplication()->getSystemClass()->getWidth(),(float)IApplication::getApplication()->getSystemClass()->getHeight(),screenNear,screenDepth);
	float screenAspect = (float)IApplication::getApplication()->getSystemClass()->getWidth() / (float)IApplication::getApplication()->getSystemClass()->getHeight();
	XMMATRIX projection = XMMatrixPerspectiveFovLH(fieldofView,screenAspect,screenNear,screenDepth);
	XMMATRIX viewmat;
	XMMATRIX worldmat = XMMatrixIdentity();


	//cam.getViewMatrix(viewmat);

	//mat->InitMatrix(projection, viewmat, worldmat);
	*/

	IApplication::getApplication()->getRenderSystem()->setRenderInterfaces(interf);
}

