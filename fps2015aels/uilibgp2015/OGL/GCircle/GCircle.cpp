#include "GCircle.h"
#include "../Draw_Geometry/Draw_Geometry_Circle.h"

ID::GCircle::GCircle(uint32_t r,
		     bool f,
		     ID::Color* color) : __radius(r),
					 __color(*color),
					 __fulfil(f)
{
	this->_w = r;
	this->_h = r;
}

ID::GCircle::~GCircle()
{
}

void		ID::GCircle::SetColor(uint32_t color)
{
	this->__color = color;
}

void		ID::GCircle::SetColor(ID::Color* color)
{
	this->__color = *color;
}

void		ID::GCircle::SetRadius(uint32_t r)
{
	this->__radius = r;
	this->_w = r;
	this->_h = r;
}

void		ID::GCircle::SetFulfil(bool f)
{
	this->__fulfil = f;
}

ID::Color	ID::GCircle::GetColor(void)
{
	return this->__color;
}

uint32_t	ID::GCircle::GetRadius(void)
{
	return this->__radius;
}

bool		ID::GCircle::GetFulfil(void)
{
	return this->__fulfil;
}

int	ID::GCircle::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (s == NULL)
		return 0;
	ID::Draw_Geometry_Circle::GetInstance()->Draw(s,
						      x + this->_x,
						      y + this->_y,
						      this->__radius,
						      this->__fulfil,
						      &(this->__color));
	return 0;
}

