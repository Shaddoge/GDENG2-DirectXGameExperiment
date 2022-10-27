#include "Quad.h"

Quad::Quad(string name) : GameObject(name)
{
	quad_vertex vertex_list[4] = {
		// X - Y - Z					Color
		{Vector3(-0.25f,-0.25f, 0.0f),	Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-0.25f, 0.25f, 0.0f),	Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(0.25f,-0.25f, 0.0f),	Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(0.25f, 0.25f, 0.0f),	Vector3(0,0,0),	Vector3(1,1,1)}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;
	
	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

Quad::Quad(string name, Vector3 position) : GameObject(name)
{
	SetPosition(position);
	Vector2 dimension = Vector2(1.0f, 1.0f);
	float x_half = dimension.x / 2;
	float y_half = dimension.y / 2;

	quad_vertex vertex_list[4] = {
		// X - Y - Z					Color
		{Vector3(-x_half,-y_half , 0.0f),	Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-x_half, y_half , 0.0f),	Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(x_half ,-y_half , 0.0f),	Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(x_half , y_half , 0.0f),	Vector3(0,0,0),	Vector3(1,1,1)}
	};

	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

// With offset positioning
Quad::Quad(string name, Vector2 dimension) : GameObject(name)
{
	//EventManager::BindEvent("MouseMove", this);
	float x_half = dimension.x / 2;
	float y_half = dimension.y / 2;
	quad_vertex vertex_list[4] = {
		
		// X - Y - Z													Color
		{Vector3(-x_half,-y_half , 0.0f),	Vector3(1,0,0),	Vector3(0,0,1)},
		{Vector3(-x_half, y_half , 0.0f),	Vector3(0,1,0),	Vector3(0,1,1)},
		{Vector3(x_half ,-y_half , 0.0f),	Vector3(0,0,1),	Vector3(1,0,0)},
		{Vector3(x_half , y_half , 0.0f),	Vector3(0,0,0),	Vector3(1,1,1)}
	};
	
	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(&vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

Quad::Quad(string name, quad_vertex vertex_list[4]) : GameObject(name)
{
	//EventManager::BindEvent("MouseMove", this);
	m_vb = GraphicsEngine::Get()->CreateVertexBuffer();
	UINT size_list = 4;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// Vertex Shader
	GraphicsEngine::Get()->CompileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::Get()->CreateVertexShader(shader_byte_code, size_shader);
	m_vb->Load(vertex_list, sizeof(quad_vertex), size_list, shader_byte_code, size_shader);

	// Pixel Shader
	GraphicsEngine::Get()->CompilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::Get()->CreatePixelShader(shader_byte_code, size_shader);
	GraphicsEngine::Get()->ReleaseCompiledShader();

	// Constant Buffer
	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::Get()->CreateConstantBuffer();
	m_cb->Load(&cc, sizeof(constant));
}

void Quad::Update(float delta_time)
{
	m_angle += 1.57f * delta_time;
	m_delta_scale += delta_time * m_speed;
}

void Quad::Draw(int width, int height)
{
	constant cc;

	Vector3 scale = GetScale();
	// Scale
	cc.m_world.SetIdentity();
	cc.m_world.SetScale(Vector3(scale.x, scale.y, scale.z));

	Vector3 local_rotation = GetLocalRotation();
	// Temp Matrix
	Matrix temp;
	// Rotation Z
	temp.SetIdentity();
	temp.SetRotationZ(local_rotation.z);
	cc.m_world *= temp;
	// Rotation Y
	temp.SetIdentity();
	temp.SetRotationY(local_rotation.y);
	cc.m_world *= temp;
	// Rotation X
	temp.SetIdentity();
	temp.SetRotationX(local_rotation.x);
	cc.m_world *= temp;

	Vector3 world_pos = GetWorldPosition();
	// Translate
	temp.SetIdentity();
	temp.SetTranslate(Vector3(world_pos.x, world_pos.y, world_pos.z));

	cc.m_world *= temp;

	cc.m_view.SetIdentity();
	cc.m_view = GetViewMatrix();
	//cc.m_projection.SetOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);
	cc.m_projection.SetPerspectiveFovLH(1.57f, (float)width / (float)height, 0.05f, 100.0f);
	cc.m_angle = m_angle;

	m_cb->Update(GraphicsEngine::Get()->GetImmediateDeviceContext(), &cc);

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_vs, m_cb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetConstantBuffer(m_ps, m_cb);

	// Set default shader in graphics pipeline
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexShader(m_vs);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetPixelShader(m_ps);

	//GraphicsEngine::Get()
	if (GetOutlined())
	{
		// Set Vertex Buffer for outline
		//GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb_outline);
		//GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_vb_outline->GetSizeVertexList(), 0, 0);
	}

	GraphicsEngine::Get()->GetImmediateDeviceContext()->SetVertexBuffer(m_vb);
	GraphicsEngine::Get()->GetImmediateDeviceContext()->DrawIndexedTriangleList(m_vb->GetSizeVertexList(), 0, 0);
}

Quad::~Quad()
{
	m_vb->Release();
	m_vs->Release();
	m_ps->Release();
}

VertexBuffer Quad::GetVertexBuffer()
{
	return *m_vb;
}

void Quad::SetSpeed(float speed)
{
	this->m_speed = speed;
}
