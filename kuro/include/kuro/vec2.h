#pragma once

#include <math.h>

struct vec2_t
{
	float x, y;
};

inline static vec2_t
operator+(vec2_t a, vec2_t b)
{
	return vec2_t{a.x + b.x, a.y + b.y};
}

inline static vec2_t &
operator+=(vec2_t &a, vec2_t b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

inline static vec2_t
operator-(vec2_t a, vec2_t b)
{
	return vec2_t{a.x - b.x, a.y - b.y};
}

inline static vec2_t &
operator-=(vec2_t &a, vec2_t b)
{
	a.x -= b.x;
	a.y -= b.y;
	return a;
}

inline static vec2_t
operator*(vec2_t a, float s)
{
	return vec2_t{a.x * s, a.y * s};
}

inline static vec2_t
operator*(float s, vec2_t a)
{
	return a * s;
}

inline static vec2_t &
operator*=(vec2_t &a, float s)
{
	a.x *= s;
	a.y *= s;
	return a;
}

inline static vec2_t
operator/(vec2_t a, float s)
{
	return a * (1.0f / s);
}

inline static vec2_t
operator/(float s, vec2_t a)
{
	return a / s;
}

inline static vec2_t &
operator/=(vec2_t &a, float s)
{
	a *= (1.0f / s);
	return a;
}

inline static vec2_t
min(vec2_t a, vec2_t b)
{
	vec2_t res;
	res.x = a.x < b.x ? a.x : b.x;
	res.y = a.y < b.y ? a.y : b.y;
	return res;
}

inline static vec2_t
max(vec2_t a, vec2_t b)
{
	vec2_t res;
	res.x = a.x > b.x ? a.x : b.x;
	res.y = a.y > b.y ? a.y : b.y;
	return res;
}

inline static float
dot(vec2_t a, vec2_t b)
{
	return a.x * b.x + a.y * b.y;
}

inline static float
cross(vec2_t a, vec2_t b)
{
	return a.x * b.y - a.y * b.x;
}

// rotate a around b with angle
inline static vec2_t
rotate(vec2_t a, float angle, vec2_t b = {0})
{
	vec2_t seg = a - b;
	return vec2_t{
		b.x + ((seg.x * cosf(angle)) - (seg.y * sinf(angle))),
		b.y + ((seg.x * sinf(angle)) + (seg.y * cosf(angle)))};
}
