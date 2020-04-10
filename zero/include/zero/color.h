#ifndef ZERO_COLOR_T
#define ZERO_COLOR_T

typedef struct _zero_color
{
	float r;
	float g;
	float b;
	float a;
} zero_color_t;

inline static zero_color_t
zero_color_lerp(zero_color_t c1, zero_color_t c2, float t)
{
	zero_color_t res;
	res.r = c1.r + (c2.r - c1.r) * t;
	res.g = c1.g + (c2.g - c1.g) * t;
	res.b = c1.b + (c2.b - c1.b) * t;
	res.a = c1.a + (c2.a - c1.a) * t;

	return res;
}

#endif /* ZERO_COLOR_T */
