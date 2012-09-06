#include "GRect.h"
#include "../Draw_Geometry/Draw_Geometry_Rect.h"

ID::GRect::GRect(int16_t w, int16_t h,
		 bool f,
		 ID::Color* color) : /*__w(w),
				     __h(h),*/
				     __fulfil(f),
				     __color(*color)
{
	this->_w = w;
	this->_h = h;
}

ID::GRect::~GRect()
{
}

void	ID::GRect::SetDimension(int16_t w, int16_t h)
{
	this->_w = w;
	this->_h = h;
}

void	ID::GRect::SetFulfil(bool f)
{
	this->__fulfil = f;
}

void	ID::GRect::SetColor(uint32_t c)
{
	this->__color = c;
}

void	ID::GRect::SetColor(ID::Color c)
{
	this->__color = c;
}

int	ID::GRect::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (s == NULL)
		return 0;
	ID::Draw_Geometry_Rect::GetInstance()->Draw(s,
						    x + this->_x,
						    y + this->_y,
						    this->GetWidth(),
						    this->GetHeight(),
						    this->__fulfil,
						    this->__color.ConvertToInt());
	return 0;
}

