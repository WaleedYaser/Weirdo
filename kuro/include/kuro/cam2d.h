#pragma once

#include "kuro/vec2.h"

struct kuro_cam2d_t
{
	float bottom, right, top, left;
};

inline static kuro_cam2d_t
kuro_cam2d_new(float cam_width, float cam_height)
{
	kuro_cam2d_t self;
	self.right  = cam_width / 2.0f;
	self.top    = cam_height / 2.0f;
	self.left   = -self.right;
	self.bottom = -self.top;

	return self;
}

inline static void
kuro_cam2d_fit(kuro_cam2d_t &self, uint32_t image_width, uint32_t image_height)
{
	float x_scale = 1.0f;
	float y_scale = 1.0f;

	float cam_aspect_ratio = (self.right - self.left) / (self.top - self.bottom);
	float image_aspect_ratio = (float)image_width / (float)image_height;

	if (cam_aspect_ratio > image_aspect_ratio)
		y_scale = cam_aspect_ratio / image_aspect_ratio;
	else
		x_scale = image_aspect_ratio / cam_aspect_ratio;

	self.bottom *= y_scale;
	self.right  *= x_scale;
	self.top    *= y_scale;
	self.left   *= x_scale;
}

inline static void
kuro_cam2d_fill(kuro_cam2d_t &self, uint32_t image_width, uint32_t image_height)
{
	float x_scale = 1.0f;
	float y_scale = 1.0f;

	float cam_aspect_ratio = (self.right - self.left) / (self.top - self.bottom);
	float image_aspect_ratio = (float)image_width / (float)image_height;

	if (cam_aspect_ratio > image_aspect_ratio)
		x_scale = image_aspect_ratio / cam_aspect_ratio;
	else
		y_scale = cam_aspect_ratio / image_aspect_ratio;

	self.bottom *= y_scale;
	self.right  *= x_scale;
	self.top    *= y_scale;
	self.left   *= x_scale;
}

inline static vec2_t
kuro_cam2d_to_pixel(const kuro_cam2d_t &self, vec2_t p_cam, uint32_t image_width, uint32_t image_height)
{
	vec2_t p_ndc = vec2_t{
		(p_cam.x + self.right) / (self.right - self.left),
		(p_cam.y + self.top) / (self.top - self.bottom)};

	vec2_t p_raster = vec2_t{p_ndc.x * image_width, (1.0f - p_ndc.y) * image_height};
	return p_raster;
}
