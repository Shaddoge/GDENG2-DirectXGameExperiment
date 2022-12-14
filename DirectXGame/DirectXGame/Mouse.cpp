#include "Mouse.h"

Mouse* Mouse::sharedInstance = NULL;

void Mouse::Initialize()
{
	sharedInstance = new Mouse();
}

POINT Mouse::GetPos()
{
	//::GetCursorPos(&sharedInstance->mouse_pos);
	return sharedInstance->curr_pos;
}

Vector2D Mouse::GetDeltaPos()
{
	return sharedInstance->delta_pos;
}

bool Mouse::GetIsDown(const MouseInputType& type)
{
	switch (type)
	{
		case MouseInputType::L: //std::cout << "Get L" << std::endl; 
					return sharedInstance->l_is_down; break;
		case MouseInputType::R: //std::cout << "Get R" << std::endl; 
				return sharedInstance->r_is_down; break;
		default: return false;
	}
}

void Mouse::SetDown(const MouseInputType& type, bool is_down)
{
	switch (type)
	{
		case MouseInputType::L: {
			sharedInstance->l_is_down = is_down; 
			if (!is_down)
			{
				sharedInstance->l_released = true;
			}
			break;
		}
		case MouseInputType::R: {
			sharedInstance->r_is_down = is_down; break;
			if (!is_down)
			{
				sharedInstance->r_released = true;
			}
		}
		default: break;
	}
}

void Mouse::SetCursorPos(const POINT& pos)
{
	::SetCursorPos(pos.x, pos.y);
	sharedInstance->old_pos = {pos.x, pos.y};
}

void Mouse::ShowCursor(bool shown)
{
	::ShowCursor(shown);
}

void Mouse::OnDrag(POINT new_pos)
{
	if (sharedInstance->l_released)
	{
		sharedInstance->old_pos = { new_pos.x, new_pos.y };
		sharedInstance->l_released = false;
		return;
	}
	sharedInstance->curr_pos = new_pos;
	int old_pos_x = sharedInstance->old_pos.x;
	int old_pos_y = sharedInstance->old_pos.y;
	sharedInstance->delta_pos = Vector2D(-(old_pos_x - new_pos.x), old_pos_y - new_pos.y );
	sharedInstance->old_pos = { new_pos.x, new_pos.y };
}

Mouse::Mouse()
{
}	

Mouse::~Mouse()
{
}
