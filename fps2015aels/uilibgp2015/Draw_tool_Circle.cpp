#include "Draw_tool_Circle.h"
#include "Container_Window.h"
#include "Draw.h"
#include <iostream>

Circle::Circle(void): x_center(0), y_center(0)
{
}

Circle::~Circle(void)
{
}

void	Circle::event_buttonup(SDL_Event*, void*)
{
	Draw*		draw;

	if (this->actions == NULL)
		return ;
	draw = Draw::get_instance();
	draw->add_action(this->actions);
	this->actions->redo(draw->layer->surface);
	draw->preview->set_background(draw->preview->bgcolor);
	Window::get_instance()->draw_area->draw_layers(this->actions);
	this->x_center = 0;
	this->y_center = 0;
	this->actions = NULL;
}

void	Circle::event_buttondown(SDL_Event* e, void* l)
{
	SDL_Rect	rec;
	Draw*		draw;
	Layer*		layer;

	layer = (Layer*)l;
	draw = Draw::get_instance();
	if (this->actions != NULL)
	{;
		draw->preview->set_background(0);
		Window::get_instance()->draw_area->draw_layers(this->actions);
		delete this->actions;
		this->actions = NULL;
		return ;
	}
	rec = this->get_realpos(e->button.x, e->button.y, layer);

	if (e->button.button == SDL_BUTTON_LEFT)
		draw->color_used = &(draw->left_color);
	else if (e->button.button == SDL_BUTTON_RIGHT)
		draw->color_used = &(draw->right_color);
	draw->layer = layer;

	this->x_center = rec.x;
	this->y_center = rec.y;

	this->actions = new URAction(draw->layer->surface);
}

void	Circle::event_motion(SDL_Event* e, void* l)
{
	SDL_Rect	rec;
	Layer*		layer;

	layer = (Layer*)l;
	rec = this->get_realpos(e->motion.x, e->motion.y, layer);

	this->refresh_status(&rec, e);
	if (this->actions == NULL)
		return ;
	if (this->actions != NULL && (e->motion.state == SDL_BUTTON(1) ||
				      e->motion.state == SDL_BUTTON(3)))
	{
		Draw*	draw;

		draw = Draw::get_instance();
		this->actions->undo(draw->preview->surface);
		Window::get_instance()->draw_area->draw_layers(this->actions);
		this->actions->clear_actions();
		if (e->motion.state == SDL_BUTTON(1))
			draw->color_used = &(draw->left_color);
		else if (e->motion.state == SDL_BUTTON(3))
			draw->color_used = &(draw->right_color);
		draw->layer = layer;
		this->draw_circle(this->x_center, this->y_center, rec.x, rec.y);
		Window::get_instance()->draw_area->draw_layers(this->actions);
	}
	else
		this->event_buttonup(e, l);
}

void	Circle::set_pixel(int x, int y)
{
	Draw*	draw;
	Uint8*	p;

	draw = Draw::get_instance();
	if (0 > y || y >= draw->layer->surface->clip_rect.h ||
	    0 > x || x >= draw->layer->surface->clip_rect.w)
		return ;
	if (draw->layer->surface->format->BytesPerPixel != 4)
		return ;
	p = (Uint8*)draw->layer->surface->pixels +
	    y * draw->layer->surface->pitch +
	    x * draw->layer->surface->format->BytesPerPixel;
	if (this->actions != NULL)
		this->actions->add(x, y, *(Uint32*)p, *(draw->color_used));
	*(Uint32*)((Uint8*)draw->preview->surface->pixels +
		   y * draw->preview->surface->pitch +
		   x * draw->preview->surface->format->BytesPerPixel) = *(draw->color_used);
}

void	Circle::draw_circle(int x1, int y1, int x2, int y2)
{
	int	x;
	int	y;
	int	d;
	int	true_r;
	int	s = Draw::get_instance()->brush_size;
	int	r;

	true_r = this->segment_length(x1, y1, x2, y2);
	r = true_r;
	r -= (s + s);
	while (r <= (true_r))
	{
		x = 0;
		y = r;
		d = r - 1;
		while (y >= x)
		{
			if (x == 0)
			{
				this->set_pixel(y + x1, y1);
				this->set_pixel(x1, -y + y1);
				this->set_pixel(x1, y + y1);
				this->set_pixel(-y + x1, y1);
			}
			else if (y == 0)
			{
				this->set_pixel(x + x1, y1);
				this->set_pixel(-x + x1, y1);
				this->set_pixel(x1, x + y1);
				this->set_pixel(x1, -x + y1);
			}
			else if (x != y)
			{
				this->set_pixel(y + x1, x + y1);
				this->set_pixel(y + x1, -x + y1);
				this->set_pixel(x + x1, -y + y1);
				this->set_pixel(x + x1, y + y1);
				this->set_pixel(-x + x1, y + y1);
				this->set_pixel(-x + x1, -y + y1);
				this->set_pixel(-y + x1, x + y1);
				this->set_pixel(-y + x1, -x + y1);
			}
			else if (x == y)
			{
				this->set_pixel(y + x1, x + y1);
				this->set_pixel(x + x1, -y + y1);
				this->set_pixel(-x + x1, y + y1);
				this->set_pixel(-x + x1, -y + y1);
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

float	Circle::segment_length(int xa, int ya, int xb, int yb)
{
	return this->mysqrt((float)(this->square((float)(xb - xa)) + this->square((float)(yb - ya))));
}

float	Circle::mysqrt(float n) // Thx John
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

float	Circle::square(float a)
{
	return a * a;
}

