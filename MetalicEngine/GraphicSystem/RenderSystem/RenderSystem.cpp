
#include "RenderSystem.h"
#include "Application/IApplication.h"
#include "EventSystem/WindowEvent.h"


RenderSystem::RenderSystem(){}

RenderSystem::~RenderSystem(){}

void RenderSystem::Init()
{

	HRESULT result = E_FAIL;
	DXGI_SWAP_CHAIN_DESC scd;

	IDXGIDevice1* device1 = nullptr;
	IDXGIAdapter1* adapter1 = nullptr;
	IDXGIFactory1* factory1 = nullptr;
	IDXGIOutput* adapterOutput;
	
	UINT numModes = 0, i, numerator, denominator;
	size_t stringLength;
	
	DXGI_MODE_DESC* displayModeList = nullptr;
	DXGI_ADAPTER_DESC adapterDesc;
	ID3D11Texture2D* pBackBuffer;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc ;
	float fieldOfView = 0, screenAspect = 0;
	char videocarddescription[128];
	UINT flags = 0;

#ifdef _DEBUG
	flags |= D3D11_CREATE_DEVICE_DEBUG ;
#endif
	SettingDesc desc = IApplication::getApplication()->getSystemClass()->getSettingDesc();
	D3D_FEATURE_LEVEL MaxSupportedFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FeatureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_12_1
	};

	result = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory1);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error CreateDXGIFactory1", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	result = factory1->EnumAdapters1(0, &adapter1);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error EnumAdapters1", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	result = adapter1->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error EnumOutputs", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error GetDisplayModeList", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error Allocate displayModeList", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error GetDisplayModeList", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)desc.m_width)
		{
			if (displayModeList[i].Height == (unsigned int)desc.m_height)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}
	result = adapter1->GetDesc(&adapterDesc);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error GetDesc", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
	errno_t error;
	
	size_t size = 128;
	error = wcstombs_s(&stringLength,videocarddescription, size, adapterDesc.Description, size);
	if (error != 0)
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error wcstombs_s", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	m_videoCardDescription = videocarddescription;
	delete[] displayModeList;
	displayModeList = 0;

	adapterOutput->Release();
	adapterOutput = nullptr;
	adapter1->Release();
	adapter1 = nullptr;
	factory1->Release();
	factory1 = nullptr;

//	m_interfaces.m_pdevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMxaaQuality);

	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	if (m_Vsync == true)
	{
		scd.BufferDesc.RefreshRate.Numerator = numerator;
		scd.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		scd.BufferDesc.RefreshRate.Numerator = 0;
		scd.BufferDesc.RefreshRate.Denominator = 1;
	}

	if (getEnableMultisampling())
	{
	//	scd.SampleDesc.Count = 4;
	// scd.SampleDesc.Quality = m4xMxaaQuality - 1;
	}
	else
	{
		scd.SampleDesc.Count = 1;
		scd.SampleDesc.Quality = 0;
	}
	
	scd.BufferCount = 1;
	scd.BufferDesc.Width = desc.m_width;
	scd.BufferDesc.Height = desc.m_height;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = IApplication::getApplication()->getSystemClass()->getWindowHwnd();
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.Windowed = !(IApplication::getApplication()->getSystemClass()->getWindowMode());
	
//	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


	result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		flags,
		FeatureLevels,
		ARRAYSIZE(FeatureLevels),
		D3D11_SDK_VERSION,
		&scd,
		&m_interfaces.m_pswapchain,
		&m_interfaces.m_pdevice,
		&MaxSupportedFeatureLevel,
		&m_interfaces.m_pdvcontext
		);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error D3D11CreateDeviceAndSwapChain", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}

	result = m_interfaces.m_pswapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error Swapchain GetBuffer", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}
	result = m_interfaces.m_pdevice->CreateRenderTargetView(pBackBuffer, NULL, &m_interfaces.m_pbackbuffer);

	if (FAILED(result))
	{
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error CreateRenderTargetView", WindowEventList::WindowErrorDebug));
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_unique<WindowMessage>("Error RenderSystem Init", WindowEventList::WindowError));
		return;
	}

	pBackBuffer->Release();
	pBackBuffer = 0;
	
	ZeroMemory(&depthBufferDesc, sizeof(D3D11_TEXTURE2D_DESC));

	depthBufferDesc.Width = desc.m_width;
	depthBufferDesc.Height = desc.m_height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = m_interfaces.m_pdevice->CreateTexture2D(&depthBufferDesc,NULL,&m_interfaces.m_depthStencilBuffer);

	if (FAILED(result)) {
		MessageBox(NULL, L"Error create depth stencil buffer", L"ERROR", MB_OK);
		return;
	}

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = m_interfaces.m_pdevice->CreateDepthStencilState(&depthStencilDesc, &m_interfaces.m_depthStencilState);
	if (FAILED(result)) {
		MessageBox(NULL, L"Error create Depth Stencil State", L"ERROR", MB_OK);
		return;
	}

	m_interfaces.m_pdvcontext->OMSetDepthStencilState(*&m_interfaces.m_depthStencilState, 1);


	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	result = m_interfaces.m_pdevice->CreateDepthStencilView(*&m_interfaces.m_depthStencilBuffer, &depthStencilViewDesc,&m_interfaces.m_depthStencilView);

	if (FAILED(result)) {
		MessageBox(NULL, L"Error create depth stencil View", L"ERROR", MB_OK);
		return;
	}
	
	m_interfaces.m_pdvcontext->OMSetRenderTargets(1,m_interfaces.m_pbackbuffer.GetAddressOf(), NULL);
	
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = m_Enable4xMsaa;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = m_interfaces.m_pdevice->CreateRasterizerState(&rasterDesc, &m_interfaces.m_rasterState);

	
	if (FAILED(result)) {
		MessageBox(NULL, L"Error CreateRasterizerState", L"ERROR", MB_OK);
		return;
	}
	SetViewPort();
	
}

void RenderSystem::SetViewPort()
{
    SettingDesc desc = IApplication::getApplication()->getSystemClass()->getSettingDesc();

	D3D11_VIEWPORT m_viewport;
	ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.MinDepth = 0.0f; 
	m_viewport.Width = (float)desc.m_width;
	m_viewport.Height = (float)desc.m_height;
	m_interfaces.m_pdvcontext->RSSetViewports(1, &m_viewport);
}

void RenderSystem::Release()
{
	if(m_interfaces.m_pswapchain != nullptr)
	m_interfaces.m_pswapchain->SetFullscreenState(false, NULL);
	RenderSystem::~RenderSystem();
}
void RenderSystem::setBackgroundColor(COLOR color)
{	
	unsigned int red = (0xff0000 & (int)color) >> 16;
	unsigned int green = (0x00ff00 & (int)color) >> 8;
	unsigned int blue = (0x0000ff & (int)color);
	FLOAT col[4];
	col[0] = (float)red / 255.0f;
	col[1] = (float)green / 255.0f;
	col[2] = (float)blue / 255.0f;
	col[3] = 0.1f;
	m_interfaces.m_pdvcontext->ClearRenderTargetView(*&m_interfaces.m_pbackbuffer, col);
}

void RenderSystem::Run()
{

	m_interfaces.m_pdvcontext->ClearDepthStencilView(*&m_interfaces.m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_interfaces.m_pdvcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_interfaces.m_pdvcontext->Draw(3, 0);
	/*
	ID3D11Debug* debug = 0;
	m_interfaces.m_pdevice->QueryInterface(__uuidof(ID3D11Debug),(void**)&debug);
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	*/
	HRESULT result = m_interfaces.m_pswapchain->Present(0, 0);
	/*DWORD dwErrorCode = GetLastError();
	if (dwErrorCode != 0) {
		std::wstringstream err;
		err << dwErrorCode;
		std::wstring er = err.str();
		MessageBox(NULL, er.c_str(), L"", MB_OK);
	}
	result = debug->ValidateContext(m_interfaces.m_pdvcontext.Get());*/
	if (FAILED(result))
		IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_shared<WindowMessage>("Error present SwapChain",WindowEventList::WindowErrorDebug));
}
