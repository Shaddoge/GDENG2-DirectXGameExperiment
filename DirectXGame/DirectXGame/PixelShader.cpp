#include "PixelShader.h"
#include "GraphicsEngine.h"
#include <iostream>

PixelShader::PixelShader()
{
}

void PixelShader::Release()
{
	m_ps->Release();
	delete this;
}


bool PixelShader::Init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::Get()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		return false;

	return true;
}

PixelShader::~PixelShader()
{
}