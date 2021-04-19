#pragma once

#ifndef _SHADER_
#define _SHADER_
#include <d3d11.h>
#include <string>
#include "EventSystem\WindowEvent.h"
#include "Application\IApplication.h"

struct ShaderParam
{
	virtual void setShader(ID3D11DeviceChild* shader) = 0;
	virtual void CreateShader(ID3D11Device* m_pdevice, ID3D11DeviceContext* devcon) = 0;
	virtual ID3D11DeviceChild* getShader() = 0;
	virtual void Release() { if (blob != nullptr)blob->Release(); if (ied != nullptr) delete ied; }
	std::wstring path;
	std::string EntryPoint;
	std::string Version;
	ID3DBlob* blob = nullptr;
	D3D11_INPUT_ELEMENT_DESC* ied = nullptr;
	size_t IED_SIZE = 0;
};

class VertexShader : public ShaderParam
{
public:
	ID3D11DeviceChild* getShader() { return (ID3D11DeviceChild*)m_pshader; }
	void setShader(ID3D11DeviceChild* shader)override { m_pshader = (ID3D11VertexShader*)shader; }

	void CreateShader(ID3D11Device* m_pdevice, ID3D11DeviceContext* devcon)
	{
		HRESULT result = S_OK;
		result = m_pdevice->CreateVertexShader(this->blob->GetBufferPointer(), this->blob->GetBufferSize(), NULL, &this->m_pshader);
		if (FAILED(result))
		{
			IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_shared<WindowMessage>("Error create vertex shader", WindowEventList::WindowErrorDebug));
		}
		devcon->VSSetShader(this->m_pshader, 0, 0);
	}
private:
	ID3D11VertexShader* m_pshader;
};

class PixelShader : public ShaderParam
{
public:
	ID3D11DeviceChild* getShader() { return (ID3D11DeviceChild*)m_pshader; }
	void setShader(ID3D11DeviceChild* shader) { m_pshader = (ID3D11PixelShader*)shader; }
	void CreateShader(ID3D11Device* m_pdevice, ID3D11DeviceContext* devcon)
	{
		HRESULT result = S_OK;
		result = m_pdevice->CreatePixelShader(this->blob->GetBufferPointer(), this->blob->GetBufferSize(), NULL, &this->m_pshader);
		if (FAILED(result))
		{
			IApplication::getApplication()->getEventSystem()->Notify("Error Render", std::make_shared<WindowMessage>("Error create pixel shader", WindowEventList::WindowErrorDebug));
		}
		devcon->PSSetShader(this->m_pshader, 0, 0);
	}
private:
	ID3D11PixelShader* m_pshader;
};
#endif