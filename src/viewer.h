#pragma once

#include <d3d11.h>

class Viewer
{
public:
	ID3D11ShaderResourceView* g_Texture = nullptr;
	int g_TextureWidth = 0;
	int g_TextureHeight = 0;
	bool LoadTextureFromOpenCV(const char* filename, ID3D11Device* device, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
};