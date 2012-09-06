#include "GPolygon.h"
#include "../Draw_Geometry/Draw_Geometry_Polygon.h"

ID::GPolygon::GPolygon(int s, bool f,
		       ID::Color* color) : __size(s),
					   __fulfil(f),
					   __color(*color)
{
}

ID::GPolygon::~GPolygon()
{
}

void	ID::GPolygon::AddPoint(int16_t x, int16_t y)
{
	this->__points.push_back(Point(x, y));
	this->SetInvalidate(true);
}

void	ID::GPolygon::AddPoint(Point* p)
{
	this->__points.push_back(*p);
	this->SetInvalidate(true);
}

void		ID::GPolygon::SetFulfil(bool f)
{
	this->__fulfil = f;
	this->SetInvalidate(true);
}

void	ID::GPolygon::SetColor(uint32_t c)
{
	this->__color = c;
	this->SetInvalidate(true);
}

void	ID::GPolygon::SetColor(ID::Color c)
{
	this->__color = c;
	this->SetInvalidate(true);
}

std::vector<ID::Point>*	ID::GPolygon::GetPoints(void)
{
	return &(this->__points);
}

bool		ID::GPolygon::GetFulfil(void)
{
	return this->__fulfil;
}

ID::Color	ID::GPolygon::GetColor(void)
{
	return this->__color;
}

int	ID::GPolygon::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (s == NULL)
		return 0;
	ID::Draw_Geometry_Polygon::GetInstance()->Draw(s,
						       x + this->_x,
						       y + this->_y,
						       &(this->__points),
						       this->__size,
						       this->__fulfil,
						       &(this->__color));
	return 0;
}

