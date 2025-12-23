#pragma once

class Vector2 {
public:
	double x;
	double y;
	Vector2() = default;

	Vector2(double x, double y) : x(x), y(y) {}

	Vector2 operator +() const
	{
		return *this;
	}

	Vector2 operator -() const
	{
		return{ -x, -y };
	}

	Vector2 operator +(const Vector2& vec) const
	{
		return{ x + vec.x, y + vec.y };
	}

	Vector2 operator -(const Vector2& vec) const
	{
		return{ x - vec.x, y - vec.y };
	}

	Vector2 operator *(double s) const
	{
		return{ x * s, y * s };
	}

	Vector2 operator /(double s) const
	{
		return{ x / s, y / s };
	}

private:
};