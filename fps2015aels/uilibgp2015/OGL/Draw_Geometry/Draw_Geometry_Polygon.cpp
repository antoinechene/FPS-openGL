#include "Draw_Geometry_Polygon.h"
#include "../Surface.h"
#include <iostream>

ID::Draw_Geometry_Polygon::Draw_Geometry_Polygon()
{
}

ID::Draw_Geometry_Polygon::~Draw_Geometry_Polygon()
{
}

void	ID::Draw_Geometry_Polygon::Draw(ID::Surface* s,
					int16_t x, int16_t y,
					ID::GPolygon* l,
					int size,
					bool f,
					ID::Color* color)
{
	this->__size = size;
	this->__target = s;
	this->__color  = color;
	this->__Polygon(x, y, l->GetPoints(), f);
}

void	ID::Draw_Geometry_Polygon::Draw(ID::Surface* s,
					int16_t x, int16_t y,
					std::vector<Point>* v,
					int size,
					bool f,
					ID::Color* color)
{
	this->__size = size;
	this->__color = color;
	this->__target = s;
	this->__Polygon(x, y, v, f);
}

void	ID::Draw_Geometry_Polygon::__Polygon(int16_t oX, int16_t oY,
					     std::vector<Point>* l,
					     bool f)
{
	std::vector<Point>::iterator	it;
	std::vector<Point>::iterator	end;
	int16_t				x;
	int16_t				y;
	Point*				first;

	this->__points.clear();
	it = l->begin();
	end = l->end();
	first = &(*it);
	x = (*it).x;
	y = (*it).y;
	++it;
	while (it != end)
	{
		this->__Line(oX + x, oY + y, oX + (*it).x, oY + (*it).y);
		x = (*it).x;
		y = (*it).y;
		++it;
	}
	this->__Line(oX + x, oY + y, oX + first->x, oY + first->y);
	if (f == true)
		this->__Fill();
}

void	ID::Draw_Geometry_Polygon::__Fill(void)
{
	std::map<int, std::list<int> >::iterator	it;
	std::map<int, std::list<int> >::iterator	end;
	std::list<int>::iterator			itX;
	std::list<int>::iterator			itXEnd;
	int						minX;
	int						maxX;

	it = this->__points.begin();
	end = this->__points.end();
	while (it != end)
	{
		itX = (*it).second.begin();
		itXEnd = (*it).second.end();
		while (itX != itXEnd)
		{
			minX = *itX;
			++itX;
			maxX = *itX;
			++itX;
			while (minX <= maxX)
			{
				this->__target->SetPixelTrans(minX,
							      (*it).first,
							      this->__color);
				++minX;
			}
		}
		++it;
	}
}

void	ID::Draw_Geometry_Polygon::__SetPixelTrans(uint16_t x, uint16_t y)
{
	std::list<int>::iterator	it;
	std::list<int>::iterator	nearer;
	int				i;

	it = this->__points[y].begin();
	i = this->__points[y].size();
	if (i > 1)
	{
		--i;
		nearer = it++;
		while (i > 1)
		{
			if (*nearer == x)
				break ;
			else if (*it >= x && (*it <= *nearer ||
					      *nearer < x))
					nearer = it;
				++it;
			--i;
		}
		if (*nearer < x)
		{
			while (nearer != this->__points[y].end() &&
			       *nearer < x)
				++nearer;
			this->__points[y].insert(nearer, x);
		}
		else
			this->__points[y].insert(nearer, x);
	}
	else if (i == 1)
	{
		if (*it > x)
			this->__points[y].push_front(x);
		else
			this->__points[y].push_back(x);
	}
	else
		this->__points[y].push_back(x);
	this->__target->SetPixelTrans(x, y, this->__color);
}

void	ID::Draw_Geometry_Polygon::__Line(int x1, int y1, int x2, int y2)
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
	this->__PixelBrush(x2, y2);
	// le pixel final (x2, y2) n’est pas tracé.
}


void	ID::Draw_Geometry_Polygon::__PixelBrush(int x_center, int y_center)
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
		this->__SetPixelTrans(x_center, y_center);
		while (r > 0)
		{
			x = 0;
			y = r;
			d = r - 1;
			while (y >= x)
			{
				if (x == 0)
				{
					this->__SetPixelTrans(x_center, y + y_center);
					this->__SetPixelTrans(y + x_center, y_center);
					this->__SetPixelTrans(-y + x_center, y_center);
					this->__SetPixelTrans(x_center, -y + y_center);
				}
				else if (y == 0)
				{
					this->__SetPixelTrans(x + x_center, y_center);
					this->__SetPixelTrans(x_center, x + y_center);
					this->__SetPixelTrans(-x + x_center, y_center);
					this->__SetPixelTrans(x_center, -x + y_center);
				}
				else if (x != y)
				{
					this->__SetPixelTrans(x + x_center, -y + y_center);
					this->__SetPixelTrans(y + x_center, -x + y_center);
					this->__SetPixelTrans(y + x_center, x + y_center);
					this->__SetPixelTrans(x + x_center, y + y_center);
					this->__SetPixelTrans(-x + x_center, y + y_center);
					this->__SetPixelTrans(-y + x_center, x + y_center);
					this->__SetPixelTrans(-y + x_center, -x + y_center);
					this->__SetPixelTrans(-x + x_center, -y + y_center);
				}
				else if (x == y)
				{
					this->__SetPixelTrans(y + x_center, x + y_center);
					this->__SetPixelTrans(-x + x_center, y + y_center);
					this->__SetPixelTrans(x + x_center, -y + y_center);
					this->__SetPixelTrans(-x + x_center, -y + y_center);
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
//	this->__lastX = x_center;
//	this->__lastY = y_center;
}

void	ID::Draw_Geometry_Polygon::__PixelBrush_1(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, y + y_center);
			this->__SetPixelTrans(y + x_center, x + y_center);
			this->__SetPixelTrans(-x + x_center, y + y_center);
			this->__SetPixelTrans(y + x_center, -x + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_2(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(y + x_center, x + y_center);
			this->__SetPixelTrans(x + x_center, y + y_center);
			this->__SetPixelTrans(-x + x_center, y + y_center);
			this->__SetPixelTrans(-y + x_center, x + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_3(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, y + y_center);
			this->__SetPixelTrans(-x + x_center, y + y_center);
			this->__SetPixelTrans(-y + x_center, x + y_center);
			this->__SetPixelTrans(-y + x_center, -x + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_4(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(-x + x_center, y + y_center);
			this->__SetPixelTrans(-y + x_center, x + y_center);
			this->__SetPixelTrans(-y + x_center, -x + y_center);
			this->__SetPixelTrans(-x + x_center, -y + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_5(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, -y + y_center);
			this->__SetPixelTrans(-y + x_center, x + y_center);
			this->__SetPixelTrans(-y + x_center, -x + y_center);
			this->__SetPixelTrans(-x + x_center, -y + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_6(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, -y + y_center);
			this->__SetPixelTrans(y + x_center, -x + y_center);
			this->__SetPixelTrans(-y + x_center, -x + y_center);
			this->__SetPixelTrans(-x + x_center, -y + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_7(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, -y + y_center);
			this->__SetPixelTrans(y + x_center, -x + y_center);
			this->__SetPixelTrans(y + x_center, x + y_center);
			this->__SetPixelTrans(-x + x_center, -y + y_center);
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

void	ID::Draw_Geometry_Polygon::__PixelBrush_8(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = this->__size;

	if (r == 0)
	{
		this->__SetPixelTrans(x_center, y_center);
		return ;
	}
	while (r > this->__size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->__SetPixelTrans(x + x_center, -y + y_center);
			this->__SetPixelTrans(y + x_center, -x + y_center);
			this->__SetPixelTrans(y + x_center, x + y_center);
			this->__SetPixelTrans(x + x_center, y + y_center);
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

