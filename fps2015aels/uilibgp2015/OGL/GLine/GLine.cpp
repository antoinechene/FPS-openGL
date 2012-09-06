#include "GLine.h"
#include "../Draw_Geometry/Draw_Geometry_Line.h"

ID::GLine::GLine(int16_t x, int16_t y,
		 int size,
		 ID::Color* color) : __size(size),
				     __color(*color)
{
	this->__point.x = x;
	this->__point.y = y;
}

ID::GLine::~GLine()
{
}

void	ID::GLine::SetVector(int16_t vX, int16_t vY)
{
	this->__point.x = vX;
	this->__point.y = vY;
}

void	ID::GLine::SetSize(uint16_t s)
{
	this->__size = s;
}

void	ID::GLine::SetColor(uint32_t c)
{
	this->__color = c;
}

void	ID::GLine::SetColor(ID::Color c)
{
	this->__color = c;
}

ID::Point	ID::GLine::GetVector(void)
{
	return this->__point;
}

uint16_t	ID::GLine::GetSize(void)
{
	return this->__size;
}

ID::Color	ID::GLine::GetColor(void)
{
	return this->__color;
}

int	ID::GLine::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (s == NULL)
		return 0;
	ID::Draw_Geometry_Line::GetInstance()->Draw(s,
						    x + this->_x,
						    y + this->_y,
						    x + this->_x + this->__point.x,
						    y + this->_y + this->__point.y,
						    this->__size,
						    &(this->__color));
	return 0;
}

