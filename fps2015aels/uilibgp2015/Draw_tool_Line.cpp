#include "Draw_tool_Line.h"
#include "Widget_Layer.h"
#include "Container_Status.h"
#include "Widget_Container.h"
#include "Draw.h"
#include "TTF.h"
#include "Container_Window.h"

Line::Line()
{
}

Line::~Line()
{
}

void	Line::event_motion(SDL_Event* e, void* l)
{
	SDL_Rect	rec;
	Layer*		layer;
	Draw*		draw;
	unsigned int	i_action;

	layer = (Layer*)l;
	rec = this->get_realpos(e->motion.x, e->motion.y, layer);

	this->refresh_status(&rec, e);
	if (this->actions == NULL)
		return;
	if (e->motion.state == SDL_BUTTON(1) ||
	    e->motion.state == SDL_BUTTON(3))
	{
		draw = Draw::get_instance();
		this->actions->undo(draw->preview->surface);
		Window::get_instance()->draw_area->draw_layers(this->actions);
		this->actions->clear_actions();
		if (e->motion.state == SDL_BUTTON(1))
			draw->color_used = &(draw->left_color);
		else if (e->motion.state == SDL_BUTTON(3))
			draw->color_used = &(draw->right_color);
		draw->layer = layer;
		i_action = this->actions->actions.size();
		this->last_x = -1;
		this->last_y = -1;
		this->line(this->x_rel, this->y_rel,
			   rec.x, rec.y);
		Window::get_instance()->draw_area->draw_layers(this->actions);
	}
	else
		this->event_buttonup(e, l);
}

void	Line::pixel_brush(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	if (this->last_x == -1 ||
	    this->last_x < x_center - 1 ||
	    this->last_x > x_center + 1 ||
	    this->last_y < y_center - 1 ||
	    this->last_y > y_center + 1)
	{
		this->set_pixel(x_center, y_center);
		while (r > 0)
		{
			x = 0;
			y = r;
			d = r - 1;
			while (y >= x)
			{
				if (x == 0)
				{
					this->set_pixel(x_center, y + y_center);
					this->set_pixel(y + x_center, y_center);
					this->set_pixel(-y + x_center, y_center);
					this->set_pixel(x_center, -y + y_center);
				}
				else if (y == 0)
				{
					this->set_pixel(x + x_center, y_center);
					this->set_pixel(x_center, x + y_center);
					this->set_pixel(-x + x_center, y_center);
					this->set_pixel(x_center, -x + y_center);
				}
				else if (x != y)
				{
					this->set_pixel(x + x_center, -y + y_center);
					this->set_pixel(y + x_center, -x + y_center);
					this->set_pixel(y + x_center, x + y_center);
					this->set_pixel(x + x_center, y + y_center);
					this->set_pixel(-x + x_center, y + y_center);
					this->set_pixel(-y + x_center, x + y_center);
					this->set_pixel(-y + x_center, -x + y_center);
					this->set_pixel(-x + x_center, -y + y_center);
				}
				else if (x == y)
				{
					this->set_pixel(y + x_center, x + y_center);
					this->set_pixel(-x + x_center, y + y_center);
					this->set_pixel(x + x_center, -y + y_center);
					this->set_pixel(-x + x_center, -y + y_center);
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
	else if (this->last_y < y_center && this->last_x < x_center)
		this->_pixel_brush_1(x_center, y_center);
	else if (this->last_y < y_center && this->last_x == x_center)
		this->_pixel_brush_2(x_center, y_center);
	else if (this->last_y < y_center && this->last_x > x_center)
		this->_pixel_brush_3(x_center, y_center);
	else if (this->last_y == y_center && this->last_x > x_center)
		this->_pixel_brush_4(x_center, y_center);
	else if (this->last_y > y_center && this->last_x > x_center)
		this->_pixel_brush_5(x_center, y_center);
	else if (this->last_y > y_center && this->last_x == x_center)
		this->_pixel_brush_6(x_center, y_center);
	else if (this->last_y > y_center && this->last_x < x_center)
		this->_pixel_brush_7(x_center, y_center);
	else if (this->last_y == y_center && this->last_x < x_center)
		this->_pixel_brush_8(x_center, y_center);
	this->last_x = x_center;
	this->last_y = y_center;
}

void	Line::_pixel_brush_1(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, y + y_center);
			this->set_pixel(y + x_center, x + y_center);
			this->set_pixel(-x + x_center, y + y_center);
			this->set_pixel(y + x_center, -x + y_center);
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

void	Line::_pixel_brush_2(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(y + x_center, x + y_center);
			this->set_pixel(x + x_center, y + y_center);
			this->set_pixel(-x + x_center, y + y_center);
			this->set_pixel(-y + x_center, x + y_center);
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

void	Line::_pixel_brush_3(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, y + y_center);
			this->set_pixel(-x + x_center, y + y_center);
			this->set_pixel(-y + x_center, x + y_center);
			this->set_pixel(-y + x_center, -x + y_center);
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

void	Line::_pixel_brush_4(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(-x + x_center, y + y_center);
			this->set_pixel(-y + x_center, x + y_center);
			this->set_pixel(-y + x_center, -x + y_center);
			this->set_pixel(-x + x_center, -y + y_center);
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

void	Line::_pixel_brush_5(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, -y + y_center);
			this->set_pixel(-y + x_center, x + y_center);
			this->set_pixel(-y + x_center, -x + y_center);
			this->set_pixel(-x + x_center, -y + y_center);
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

void	Line::_pixel_brush_6(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, -y + y_center);
			this->set_pixel(y + x_center, -x + y_center);
			this->set_pixel(-y + x_center, -x + y_center);
			this->set_pixel(-x + x_center, -y + y_center);
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

void	Line::_pixel_brush_7(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, -y + y_center);
			this->set_pixel(y + x_center, -x + y_center);
			this->set_pixel(y + x_center, x + y_center);
			this->set_pixel(-x + x_center, -y + y_center);
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

void	Line::_pixel_brush_8(int x_center, int y_center)
{
	int	x;
	int	y;
	int	d;
	int	r = Draw::get_instance()->brush_size;

	while (r > Draw::get_instance()->brush_size - 2)
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			this->set_pixel(x + x_center, -y + y_center);
			this->set_pixel(y + x_center, -x + y_center);
			this->set_pixel(y + x_center, x + y_center);
			this->set_pixel(x + x_center, y + y_center);
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


void	Line::line(int x1, int y1, int x2, int y2)
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
					this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
							this->pixel_brush(x1, y1);
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
					this->pixel_brush(x1, y1);
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
					this->pixel_brush(x1, y1);
					++y1;
				}
			}
			else  // dy < 0 (et dx = 0) // vecteur vertical décroissant
			{
				while (y1 != y2)
				{
					this->pixel_brush(x1, y1);
					--y1;
				}
			}
		}
	}
	// le pixel final (x2, y2) n’est pas tracé.
}


