#include "Draw_Geometry_Rect.h"

ID::Draw_Geometry_Rect::Draw_Geometry_Rect(void) :
				   __target(NULL),
				   __color(NULL)
{
}

ID::Draw_Geometry_Rect::~Draw_Geometry_Rect(void)
{
}

void	ID::Draw_Geometry_Rect::Draw(ID::Surface* s,
				       ID::Rect* r,
				       bool f,
				       uint32_t color)
{
	this->__target = s;
	this->__color = color;
	this->__Rect(r->x, r->y, r->x + r->w, r->y + r->h, f);
}

void	ID::Draw_Geometry_Rect::Draw(ID::Surface* s,
				     int16_t x, int16_t y,
				     int16_t w, int16_t h,
				     bool f,
				     uint32_t color)
{
	this->__target = s;
	this->__color = color;
	this->__Rect(x, y, w, h, f);
}

