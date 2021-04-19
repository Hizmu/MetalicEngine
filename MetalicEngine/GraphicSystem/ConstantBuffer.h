#pragma once


#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
struct
{
	DirectX::XMMATRIX world;
};



class ConstBuffer
{
public:
	ConstBuffer() {};
	
	ID3D11Buffer* Get() const
	{
		return buff.Get();
	}
	ID3D11Buffer* const* GetAddress()const
	{
		buff.GetAddressOf();
	}

	HRESULT Initialize()
	{

	}

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buff;
	ID3D11DeviceContext* deviceContext = nullptr;
};