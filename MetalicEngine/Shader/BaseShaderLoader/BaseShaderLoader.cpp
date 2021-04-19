#include "BaseShaderLoader.h"

ID3DBlob* BaseShaderLoader::LoadShader(std::wstring Path, std::string EntryPoint, std::string version)
{
	ID3DBlob* shader;
	HRESULT result = S_OK;
	int flags = 0;
#ifdef _DEBUG
	flags = D3DCOMPILE_DEBUG;
#endif
	result = D3DCompileFromFile(Path.c_str(), 0, 0, EntryPoint.c_str(), version.c_str(), flags, 0, &shader, 0);

	if (FAILED(result))
	{
		MessageBox(NULL, L"Failed Load Shader", L"Error",MB_OK | MB_ICONERROR);
		return nullptr;
	}

	return shader;
}