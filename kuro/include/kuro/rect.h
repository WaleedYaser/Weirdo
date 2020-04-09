#ifndef KURO_RECT_H
#define KURO_RECT_H

#include "kuro/vec2.h"

struct rect_t
{
	vec2_t tl, tr, br, bl;	// corners
	vec2_t v, a;			// accelaration
	float theta, omega, alpha;
	float m;
	float j;
};

inline static rect_t
rect_new(vec2_t center, float width, float height, float mass = 1.0f)
{
	rect_t self = {0};

	self.tl = vec2_t{center.x - width / 2.0f, center.y - height / 2.0f};
	self.tr = vec2_t{center.x + width / 2.0f, center.y - height / 2.0f};
	self.br = vec2_t{center.x + width / 2.0f, center.y + height / 2.0f};
	self.bl = vec2_t{center.x - width / 2.0f, center.y + height / 2.0f};

	self.m = mass;
	self.j = mass * (width * width + height * height) / 12000;

	return self;
}

inline static vec2_t
rect_center(const rect_t &self)
{
	vec2_t diagonal = self.tr - self.bl;
	return self.bl + (diagonal / 2.0f);
}

inline static rect_t&
rect_rotate(rect_t &self, float angle)
{
	self.theta += angle;
	vec2_t center = rect_center(self);

	self.tl = rotate(self.tl, angle, center);
	self.tr = rotate(self.tr, angle, center);
	self.br = rotate(self.br, angle, center);
	self.bl = rotate(self.bl, angle, center);

	return self;
}

#endif
