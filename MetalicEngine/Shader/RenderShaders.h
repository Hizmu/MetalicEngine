
#pragma once
#ifndef _RENDER_SHADERS_
#define _RENDER_SHADERS_


#include "Shader.h"


class RenderShaders
{
public:
	RenderShaders(ID3D11Device* dev, ID3D11DeviceContext* devcon);
	~RenderShaders();

	void LoadShaderFromFile(ShaderParam*& param);

	void CreateAndSetInputLayout(VertexShader* vertex);
	void CreateBuffer(size_t bitesize);

	void LoadVertex(void* vertices, size_t bitesize);
	void getBuffer(ID3D11Buffer*& buff);
	ID3D11InputLayout*& getInputLayout();
private:

	ID3D11Buffer* m_pBuffer;
	ID3D11Device* m_pdevice;
	ID3D11DeviceContext* m_pdevcon;
	D3D11_INPUT_ELEMENT_DESC* m_ied;
	size_t m_iedsize;
	ID3D11InputLayout* m_pinputlayout;
};
#endif