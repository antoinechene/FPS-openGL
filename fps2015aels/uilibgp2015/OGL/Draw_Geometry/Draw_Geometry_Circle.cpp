#include "Draw_Geometry_Circle.h"
#include "../Surface.h"

ID::Draw_Geometry_Circle::Draw_Geometry_Circle(void) :
				   __target(NULL),
				   __color(NULL)
{
}

ID::Draw_Geometry_Circle::~Draw_Geometry_Circle(void)
{
}

void	ID::Draw_Geometry_Circle::Draw(ID::Surface* s,
				       ID::Circle* c,
				       bool f,
				       ID::Color* color)
{
	this->__target = s;
	this->__color = color;
	this->__Circle(c->center.x, c->center.y, c->radius, f);
}

void	ID::Draw_Geometry_Circle::Draw(ID::Surface* s,
				       int16_t x, int16_t y,
				       int r,
				       bool f,
				       ID::Color* color)
{
	this->__target = s;
	this->__color = color;
	this->__Circle(x, y, r, f);
}

void	ID::Draw_Geometry_Circle::__Circle(int x1, int y1,
					   int s,
					   bool f)
{
	int	x;
	int	y;
	int	d;
	int	true_r;
	int	r;

	true_r = s;
	if (f == true)
		r = true_r - s - s;
	else
		r = true_r;
	while (r <= (true_r))
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			if (x == 0)
			{
				this->__target->SetPixelTrans(y + x1, y1, this->__color);
				this->__target->SetPixelTrans(x1, -y + y1, this->__color);
				this->__target->SetPixelTrans(x1, y + y1, this->__color);
				this->__target->SetPixelTrans(-y + x1, y1, this->__color);
			}
			else if (y == 0)
			{
				this->__target->SetPixelTrans(x + x1, y1, this->__color);
				this->__target->SetPixelTrans(-x + x1, y1, this->__color);
				this->__target->SetPixelTrans(x1, x + y1, this->__color);
				this->__target->SetPixelTrans(x1, -x + y1, this->__color);
			}
			else if (x != y)
			{
				this->__target->SetPixelTrans(y + x1, x + y1, this->__color);
				this->__target->SetPixelTrans(y + x1, -x + y1, this->__color);
				this->__target->SetPixelTrans(x + x1, -y + y1, this->__color);
				this->__target->SetPixelTrans(x + x1, y + y1, this->__color);
				this->__target->SetPixelTrans(-x + x1, y + y1, this->__color);
				this->__target->SetPixelTrans(-x + x1, -y + y1, this->__color);
				this->__target->SetPixelTrans(-y + x1, x + y1, this->__color);
				this->__target->SetPixelTrans(-y + x1, -x + y1, this->__color);
			}
			else if (x == y)
			{
				this->__target->SetPixelTrans(y + x1, x + y1, this->__color);
				this->__target->SetPixelTrans(x + x1, -y + y1, this->__color);
				this->__target->SetPixelTrans(-x + x1, y + y1, this->__color);
				this->__target->SetPixelTrans(-x + x1, -y + y1, this->__color);
			}
			if (d >= x + x)
			{
				d = d - (x + x) - 1;
				++x;
			}
			else if (d <= (r - y) + (r - y))
			{
				d = d + (y + y) - 1;
				--y;
			}
			else
			{
				d = d + (y - x + y - x - 2);
				--y;
				++x;
			}
		}
		++r;
	}
}

float	ID::Draw_Geometry_Circle::__Distance(int xa, int ya,
					     int xb, int yb)
{
	return this->__Sqrt((float)((xb - xa) * (xb - xa) +
				    (yb - ya) * (yb - ya)));
}

float	ID::Draw_Geometry_Circle::__Sqrt(float n) // Thx John
{
	long		i;
	float		x2;
	float		y;
	const float	threehalfs = 1.5F;

	x2 = n * 0.5F;
	y = n;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1); //what the fuck ?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	return 1 / y;
}

