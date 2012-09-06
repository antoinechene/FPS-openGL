#include "Draw_Geometry_Line.h"
#include "../Surface.h"

ID::Draw_Geometry_Line::Draw_Geometry_Line()
{
}

ID::Draw_Geometry_Line::~Draw_Geometry_Line()
{
}

void	ID::Draw_Geometry_Line::Draw(ID::Surface* s,
				     ID::Line* l,
				     int size,
				     ID::Color* color)
{
	this->__lastX = -1;
	this->__lastY = -1;
	this->__size = size;
	this->__color  = color;
	this->__target = s;
	this->__Line(l->p1.x, l->p1.y, l->p2.x, l->p2.y);
}

void	ID::Draw_Geometry_Line::Draw(ID::Surface* s,
				     int16_t x1, int16_t y1,
				     int16_t x2, int16_t y2,
				     int size,
				     ID::Color* color)
{
	this->__lastX = -1;
	this->__lastY = -1;
	this->__size = size;
	this->__color = color;
	this->__target = s;
	this->__Line(x1, y1, x2, y2);
}

void	ID::Draw_Geometry_Line::__Line(int x1, int y1, int x2, int y2)
{
	int	dx;
	int	dy;
	int	e;

	dx = x2 - x1;
	if (dx != 0)
	{
		if (dx > 0)
		{
			dy = y2 - y1;
			if (dy != 0)
			{
				if (dy > 0) // vecteur oblique dans le 1er quadran
				{
					if (dx >= dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 1er octant
					{
						e = dx;
						dx *= 2;
						dy *= 2;  // e est positif
						while (1) // déplacements horizontaux
						{
							this->__PixelBrush(x1, y1);
							++x1;
							if (x1 == x2)
								break;
							e -= dy;
							if (e < 0)
							{
								++y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 2nd octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;  // e est positif
						while  (1)// déplacements verticaux
						{
							this->__PixelBrush(x1, y1);
							++y1;
							if (y1 == y2)
								break;
							e -= dx;
							if (e < 0)
							{
								++x1; // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else  // dy < 0 (et dx > 0) vecteur oblique dans le 4e cadran
				{
					if (dx >= -dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
					{
						e = dx;
						dx *= 2;
						dy *= 2;  // e est positif
						while (1) // déplacements horizontaux
						{
							this->__PixelBrush(x1, y1);
							++x1;
							if (x1 == x2)
								break;
							e += dy;
							if (e < 0)
							{
								--y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else  // vecteur oblique proche de la verticale, dans le 7e octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;  // e est négatif
						while (1) // déplacements verticaux
						{
							this->__PixelBrush(x1, y1);
							--y1;
							if (y1 == y2)
								break;
							e += dx;
							if (e > 0)
							{
								++x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else  // dy = 0 (et dx > 0) vecteur horizontal vers la droite
			{
				while (x1 != x2)
				{
					this->__PixelBrush(x1, y1);
					++x1;
				}
			}
		}
		else  // dx < 0
		{
			dy = y2 - y1;
			if (dy != 0)
			{
				if (dy > 0) // vecteur oblique dans le 2nd quadran
				{
					if (-dx >= dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
					{
						e = dx;
						dx *= 2;
						dy *= 2;  // e est négatif
						while (1) // déplacements horizontaux
						{
							this->__PixelBrush(x1, y1);
							--x1;
							if (x1 == x2)
								break;
							e += dy;
							if (e >= 0)
							{
								++y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 3e octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;  // e est positif
						while (1) // déplacements verticaux
						{
							this->__PixelBrush(x1, y1);
							++y1;
							if (y1 == y2)
								break;
							e += dx;
							if (e <= 0)
							{
								--x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
				else  // dy < 0 (et dx < 0) vecteur oblique dans le 3e cadran
				{
					if (dx <= dy) // vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
					{
						e = dx;
						dx *= 2;
						dy *= 2;  // e est négatif
						while (1) // déplacements horizontaux
						{
							this->__PixelBrush(x1, y1);
							--x1;
							if (x1 == x2)
								break;
							e -= dy;
							if (e >= 0)
							{
								--y1;  // déplacement diagonal
								e += dx;
							}
						}
					}
					else // vecteur oblique proche de la verticale, dans le 6e octant
					{
						e = dy;
						dy *= 2;
						dx *= 2;  // e est négatif
						while (1) // déplacements verticaux
						{
							this->__PixelBrush(x1, y1);
							--y1;
							if (y1 == y2)
								break;
							e -= dx;
							if (e >= 0)
							{
								--x1;  // déplacement diagonal
								e += dy;
							}
						}
					}
				}
			}
			else  // dy = 0 (et dx < 0) vecteur horizontal vers la gauche
			{
				while (x1 != x2)
				{
					this->__PixelBrush(x1, y1);
					--x1;
				}
			}
		}
	}
	else  // dx = 0
	{
		dy = y2 - y1;
		if (dy != 0)
		{
			if (dy > 0) // vecteur vertical croissant
			{
				while (y1 != y2)
				{
					this->__PixelBrush(x1, y1);
					++y1;
				}
			}
			else  // dy < 0 (et dx = 0) // vecteur vertical décroissant
			{
				while (y1 != y2)
				{
					this->__PixelBrush(x1, y1);
					--y1;
				}
			}
		}
	}
	// le pixel final (x2, y2) n’est pas tracé.
}


void	ID::Draw_Geometry_Line::__PixelBrush(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (this->__lastX == -1 ||
	    this->__lastX < x_center - 1 ||
	    this->__lastX > x_center + 1 ||
	    this->__lastY < y_center - 1 ||
	    this->__lastY > y_center + 1)
	{
		this->__target->SetPixelTrans(x_center, y_center, this->__color);
		while (r > 0)
		{
			x = 0;
			y = r;
			d = r - 1;
			while (y >= x)
			{
				if (x == 0)
				{
					this->__target->SetPixelTrans(x_center, y + y_center, this->__color);
					this->__target->SetPixelTrans(y + x_center, y_center, this->__color);
					this->__target->SetPixelTrans(-y + x_center, y_center, this->__color);
					this->__target->SetPixelTrans(x_center, -y + y_center, this->__color);
				}
				else if (y == 0)
				{
					this->__target->SetPixelTrans(x + x_center, y_center, this->__color);
					this->__target->SetPixelTrans(x_center, x + y_center, this->__color);
					this->__target->SetPixelTrans(-x + x_center, y_center, this->__color);
					this->__target->SetPixelTrans(x_center, -x + y_center, this->__color);
				}
				else if (x != y)
				{
					this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
					this->__target->SetPixelTrans(y + x_center, -x + y_center, this->__color);
					this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
					this->__target->SetPixelTrans(x + x_center, y + y_center, this->__color);
					this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
					this->__target->SetPixelTrans(-y + x_center, x + y_center, this->__color);
					this->__target->SetPixelTrans(-y + x_center, -x + y_center, this->__color);
					this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
				}
				else if (x == y)
				{
					this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
					this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
					this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
					this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
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
			--r;
		}
	}
	else if (this->__lastY < y_center && this->__lastX < x_center)
		this->__PixelBrush_1(x_center, y_center);
	else if (this->__lastY < y_center && this->__lastX == x_center)
		this->__PixelBrush_2(x_center, y_center);
	else if (this->__lastY < y_center && this->__lastX > x_center)
		this->__PixelBrush_3(x_center, y_center);
	else if (this->__lastY == y_center && this->__lastX > x_center)
		this->__PixelBrush_4(x_center, y_center);
	else if (this->__lastY > y_center && this->__lastX > x_center)
		this->__PixelBrush_5(x_center, y_center);
	else if (this->__lastY > y_center && this->__lastX == x_center)
		this->__PixelBrush_6(x_center, y_center);
	else if (this->__lastY > y_center && this->__lastX < x_center)
		this->__PixelBrush_7(x_center, y_center);
	else if (this->__lastY == y_center && this->__lastX < x_center)
		this->__PixelBrush_8(x_center, y_center);
	this->__lastX = x_center;
	this->__lastY = y_center;
}

void	ID::Draw_Geometry_Line::__PixelBrush_1(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, -x + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_2(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, x + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_3(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, -x + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_4(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(-x + x_center, y + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_5(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_6(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(-y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_7(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(-x + x_center, -y + y_center, this->__color);
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
		--r;
	}
}

void	ID::Draw_Geometry_Line::__PixelBrush_8(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__target->SetPixelTrans(x + x_center, -y + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, -x + y_center, this->__color);
			this->__target->SetPixelTrans(y + x_center, x + y_center, this->__color);
			this->__target->SetPixelTrans(x + x_center, y + y_center, this->__color);
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
		--r;
	}
}

