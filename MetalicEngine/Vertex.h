#pragma once
#include <DirectXMath.h>
struct Vertex
{
	DirectX::XMFLOAT3 Position3;
	DirectX::XMFLOAT4 Color;
};

Vertex vertex[]
{
	{{0.0f, 1.0f, 0.0f},{1.0f, 0.0f, 0.0f, 1.0f} },
	{{ 0.5f, 0.0f, 0.0f },{0.0f, 1.0f, 0.0f, 1.0f}},
	{{ -0.5f, 0.0f, 0.0 },{0.0f, 0.0f, 1.0f, 1.0f}},
};