#include "AppWindow.h"
#include <Windows.h>

AppWindow::AppWindow()
{

}

AppWindow::~AppWindow()
{
	
}

void AppWindow::Update(float delta_time)
{
	Matrix world_cam = scene_camera->GetInverseWorldCam();
	// Quads
	for (Quad* quad_ptr : quads)
	{
		quad_ptr->SetViewMatrix(world_cam);
		quad_ptr->Update(delta_time);
		quad_ptr->Draw(width, height);
	}
	scene_camera->Update(delta_time);
	
	// Cubes
	for (Cube* cube_ptr : cubes)
	{
		cube_ptr->SetViewMatrix(world_cam);
		cube_ptr->Update(delta_time);
		cube_ptr->Draw(width, height);
	}

	// Plane
	for (Plane* plane_ptr : planes)
	{
		plane_ptr->SetViewMatrix(world_cam);
		plane_ptr->Update(delta_time);
		plane_ptr->Draw(width, height);
	}

	// Draw UI
	UIManager::Get()->DrawAllUI();
	
	m_swap_chain->Present(true);
}

void AppWindow::OnCreate()
{
	srand(time(0));
	Mouse::Initialize();
	EngineTime::Initialize();
	EventManager::Initialize();
	
	Window::OnCreate();
	GraphicsEngine::Get()->Init();
	m_swap_chain = GraphicsEngine::Get()->CreateSwapChain();
	
	RECT rc = this->GetClientWindowRect();
	m_swap_chain->Init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	UIManager::Initialize(this->m_hwnd);

	// Camera
	scene_camera = new Camera("Main Camera");
	
	// Quads
	Quad* quad_ptr;
	for (int i = 0; i < 3; i++)
	{
		Vector3 vec = Vector3(-0.6 + (i * 0.6), -0.6 + (i * 0.6), -0.6 + (i * 0.6)); // Position
		quad_ptr = new Quad("Quad" + to_string(i), vec);
		quads.push_back(quad_ptr);
		//EventManager::BindListener("MouseLDown", quad_ptr);
	}
	
	/*-- Question 6 --*/
	/*
	// Cubes
	Cube* cube_ptr;
	for (int i = 0; i < 3; i++)
	{
		cube_ptr = new Cube("Cube " + to_string(i + 1));
		//Vector3 rand_position = Vector3(((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f);
		// Random
		//cube_ptr->SetSpeed((((rand() % 200) - 100) / 50.0f) + 0.25f);
		//cube_ptr->SetPosition(rand_position);

		cube_ptr->SetSpeed(1.0f);
		Vector3 position;
		switch (i)
		{
		case 0: position = Vector3(0.0f, 0.9f, 0.0f); break;
		case 1: position = Vector3(-1.5f, 2.0f, 0.0f); break;
		case 2: position = Vector3(-1.5f, 3.0f, -2.0f); break;
		default: position = Vector3(0.0f, 0.0f, 0.0f); break;
		}

		cube_ptr->SetPosition(position);
		cubes.push_back(cube_ptr);
	}

	// Create plane
	Plane* plane_ptr = new Plane("Plane");
	plane_ptr->SetScale(Vector3(10.0f, 10.0f, 10.0f));
	plane_ptr->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	planes.push_back(plane_ptr);
	*/

	/*-- Question 7 --*/
	
	Plane* plane_ptr;
	// 6 Cards Slanted
	for (int i = 0; i < 3; i++)
	{
		float xOffset = 0.0f;
		if (i != 0)
		{
			xOffset = i * -0.55f;
		}
		for (int j = i; j < 3; j++)
		{
			plane_ptr = new Plane("Card");
			plane_ptr->SetScale(Vector3(1.5, 0, 1));
			plane_ptr->SetPosition(Vector3((j * 1.1f) + xOffset, i * 1.4f, 0));
			plane_ptr->SetRotation(Vector3(0.0f, 0.0f, 1.2f));

			planes.push_back(plane_ptr);
		}
	}
	// 6 Cards Slanted Opposite
	for (int i = 0; i < 3; i++)
	{
		float xOffset = 0.0f;
		if (i != 0)
		{
			xOffset = i * -0.55f;
		}
		for (int j = i; j < 3; j++)
		{
			plane_ptr = new Plane("Card");
			plane_ptr->SetScale(Vector3(1.5, 0, 1));
			plane_ptr->SetPosition(Vector3((j * 1.1f) + xOffset + 0.55f, i * 1.4f, 0));
			plane_ptr->SetRotation(Vector3(0.0f, 0.0f, -1.2f));

			planes.push_back(plane_ptr);
		}
	}
	
	// 3 Cards Platform
	for (int i = 0; i < 3; i++)
	{
		float xOffset = 0.2f;
		float yOffset = 0.7f;
		if (i > 1)
		{
			xOffset = -1.7f;
			yOffset = 2.1f;
		}

		plane_ptr = new Plane("Card");
		plane_ptr->SetScale(Vector3(1.5, 0, 1));
		plane_ptr->SetPosition(Vector3((i * 1.25f) + xOffset + 0.55f, yOffset, 0));

		planes.push_back(plane_ptr);
	}
}

void AppWindow::OnUpdate()
{
	Window::OnUpdate();
	
	// Clear render target
	GraphicsEngine::Get()->GetImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 0, 0.3f, 0.4f, 1);
	// Set viewport of render
	RECT rc = this->GetClientWindowRect();
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	delta_time = EngineTime::GetDeltaTime();

	Update(delta_time);
}

void AppWindow::OnDestroy()
{
	Window::OnDestroy();

	delete scene_camera;

	for (Quad* quad_ptr : quads)
	{
		delete quad_ptr;
	}
	quads.clear();

	for (Cube* cube_ptr : cubes)
	{
		delete cube_ptr;
	}
	cubes.clear();

	for (Plane* plane_ptr : planes)
	{
		delete plane_ptr;
	}
	planes.clear();

	m_swap_chain->Release();
	
	GraphicsEngine::Get()->Release();
}

void AppWindow::OnResize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void AppWindow::OnRMouseDown()
{
	Mouse::ShowCursor(false);
}

void AppWindow::OnRMouseUp()
{
	Mouse::ShowCursor(true);
}

void AppWindow::OnLMouseDrag(Vector2 delta_pos)
{/*
	if (Mouse::GetIsDown(MouseInputType::R)) return;
	delta_pos *= delta_time;

	if (selected_obj >= 0 and selected_obj <= 3)
	{
		switch (transform_mode)
		{
		case TRANSLATE: cubes[selected_obj]->SetPositionMouse(delta_pos); break;
		case SCALE: cubes[selected_obj]->SetScaleMouse(delta_pos); break;
		case ROTATE: cubes[selected_obj]->SetRotationMouse(delta_pos); break;
		default: break;
		}
	}*/
}

void AppWindow::OnRMouseDrag(Vector2 delta_pos)
{
	delta_pos *= delta_time;
	
	// Camera
	scene_camera->SetRotationMouse(delta_pos);
	/*
	switch (transform_mode)
	{
		case TRANSLATE: break;
		case ROTATE:  break;
		default: break;
	}

	if (selected_obj >= 0 and selected_obj <= 2)
	{
		switch (transform_mode)
		{
			case TRANSLATE: cubes[selected_obj]->SetPositionZMouse(delta_pos); break;
			case SCALE: cubes[selected_obj]->SetScaleZMouse(delta_pos); break;
			case ROTATE: cubes[selected_obj]->SetRotationZMouse(delta_pos); break;
			default: break;
		}
		/*switch (transform_mode)
		{
		case TRANSLATE: plane->SetPositionZMouse(delta_pos); break;
		case SCALE: plane->SetScaleZMouse(delta_pos); break;
		case ROTATE: plane->SetRotationZMouse(delta_pos); break;
		default: break;
		}
	}*/
}

void AppWindow::OnKeyDown(const char key)
{
	int num = key - '0';
	if (num >= 1 && num <= 3)
	{/*
		selected_obj = num - 1;
		
		for (Cube* cube : cubes)
		{
			cube->SetOutlined(false);
		}
		cubes[selected_obj]->SetOutlined(true);*/
	}
	else
	{
		if (Mouse::GetIsDown(MouseInputType::R))
		{
			switch (tolower(key))
			{
				case 'w': {
					scene_camera->SetForward(1.0f);
					break;
				}
				case 'a': {
					scene_camera->SetRight(-1.0f);
					break;
				}	
				case 's': {
					scene_camera->SetForward(-1.0f);
					break;
				}
				case 'd': {
					scene_camera->SetRight(1.0f);
					break;
				}
				case 'q': {
					scene_camera->SetTop(-1.0f);
					break;
				}
				case 'e': {
					scene_camera->SetTop(1.0f);
					break;
				}
				default: return; break;
			}
		}
		else
		{
			switch (tolower(key))
			{
				case 'q': transform_mode = TRANSLATE; break;
				case 'w': transform_mode = SCALE; break;
				case 'e': transform_mode = ROTATE;  break;
				default: break;
			}
		}
	}
}

void AppWindow::OnKeyUp(const char key)
{
	switch (tolower(key))
	{
		case 'w': {
			scene_camera->SetForward(0.0f);
			break;
		}
		case 'a': {
			scene_camera->SetRight(0.0f);
			break;
		}
		case 's': {
			scene_camera->SetForward(0.0f);
			break;
		}
		case 'd': {
			scene_camera->SetRight(0.0f);
			break;
		}
		case 'q': {
			scene_camera->SetTop(0.0f);
			break;
		}
		case 'e': {
			scene_camera->SetTop(0.0f);
			break;
		}
		default: return; break;
	}
}
