#pragma once

#ifndef _BASE_SHADER_LOADER
#define _BASE_SHADER_LOADER

#include <d3dcompiler.h>
#include <string>
 class BaseShaderLoader
{
public:
	static ID3DBlob* LoadShader(std::wstring Path, std::string EntryPoint, std::string version);
};

#endif