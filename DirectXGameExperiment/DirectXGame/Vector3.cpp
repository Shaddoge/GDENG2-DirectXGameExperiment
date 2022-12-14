#include "Vector3.h"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::~Vector3()
{
}

void Vector3::operator+=(const Vector3& vector)
{
	Vector3 out;

	x += vector.x;
	y += vector.y;
	z += vector.z;
}