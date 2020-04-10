#pragma once

struct zero_color_t
{
	float r;
	float g;
	float b;
	float a;
};

inline static zero_color_t
operator+(zero_color_t c1, zero_color_t c2)
{
	return zero_color_t{
		c1.r + c2.r,
		c1.g + c2.g,
		c1.b + c2.b,
		c1.a + c2.a};
}

inline static zero_color_t
operator+=(zero_color_t c1, zero_color_t c2)
{
	return c1 + c2;
}

inline static zero_color_t
operator-(zero_color_t c1, zero_color_t c2)
{
	return zero_color_t{
		c1.r - c2.r,
		c1.g - c2.g,
		c1.b - c2.b,
		c1.a - c2.a};
}

inline static zero_color_t
operator-=(zero_color_t c1, zero_color_t c2)
{
	return c1 - c2;
}

inline static zero_color_t
operator*(zero_color_t c1, float s)
{
	return zero_color_t{
		c1.r * s,
		c1.g * s,
		c1.b * s,
		c1.a * s};
}

inline static zero_color_t
operator*(float s, zero_color_t c1)
{
	return c1 * s;
}

inline static zero_color_t
operator*=(zero_color_t c1, float s)
{
	return c1 * s;
}

inline static zero_color_t
zero_color_lerp(zero_color_t c1, zero_color_t c2, float t)
{
	return c1 + (c2 - c1) * t;
}
