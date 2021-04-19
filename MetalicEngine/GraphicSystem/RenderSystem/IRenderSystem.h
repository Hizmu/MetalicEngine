#pragma once

#ifndef _IRENDER_SYSTEM_
#define _IRENDER_SYSTEM_

#include<d3d.h>
#include <wrl.h>
#include <DirectXCollision.h>
#include <DirectXMath.h>
#include <d3d11.h>
#include <string>
#include "Color.h"
using namespace DirectX;

struct RenderingInterfaces
{
	Microsoft::WRL::ComPtr<ID3D11Device> m_pdevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pdvcontext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> m_pswapchain;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pbackbuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterState;
};

struct IRenderSystem
{
	IRenderSystem() = default;
	virtual ~IRenderSystem() = default;

	virtual void Init() = 0;
	virtual void Run() = 0;
	virtual void Release() = 0;
	
	virtual RenderingInterfaces getRenderInterfaces() = 0;
	virtual void setRenderInterfaces(RenderingInterfaces rend) = 0;
	virtual void enableMultisampling() = 0;
	virtual void disableMultisampling() = 0;

	virtual bool getEnableMultisampling() = 0;
	virtual void setBackgroundColor(COLOR color) = 0;
	virtual void enableVsync() = 0;
	virtual void disableVsync() = 0;

};

#endif