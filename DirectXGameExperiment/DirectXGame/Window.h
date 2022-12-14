#pragma once
#include <Windows.h>
#include "EngineTime.h"
#include "Mouse.h"
#include "Vector2.h"

class Window
{
public:
	Window();
	// Initialize the window
	bool Init();
	bool Broadcast();
	// Release the window
	bool Release();
	bool IsRun();

	RECT GetClientWindowRect();
	void SetHWND(HWND hwnd);

	//EVENTS
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void OnMouseDrag(const Vector2 delta_pos);
	virtual void OnKeyDown(const char key);
	~Window();
protected:
	HWND m_hwnd;
	bool m_is_run;
};

