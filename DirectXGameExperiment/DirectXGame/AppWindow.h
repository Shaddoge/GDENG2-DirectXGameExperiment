#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Quad.h"
#include "EngineTime.h"
#include "Mouse.h"
#include "EventManager.h"
#include <vector>

enum TransformMode
{
	TRANSLATE,
	SCALE,
	ROTATE
};

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void OnCreate() override;
	virtual void OnUpdate() override;
	virtual void OnDestroy() override;
	virtual void OnMouseDrag(const Vector2 delta_pos);
	virtual void OnKeyDown(const char key) override;
private:
	SwapChain* m_swap_chain;
private:
	TransformMode transform_mode = TransformMode::TRANSLATE;
	vector<Quad*> quads;
	int selected_quad = 0;
};