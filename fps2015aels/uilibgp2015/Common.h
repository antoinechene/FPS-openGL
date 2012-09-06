#ifndef __COMMON_H__
#define __COMMON_H__

#ifndef	__MAKE_H
#include <stdint.h>
#endif

#ifdef	SHOW_DBG
#define	PRINT_DBG(x)	{std::cout << x;}
#else
#define	PRINT_DBG(x)	{}
#endif

namespace	ID
{
	struct Point
	{
		Point(int16_t _x = 0, int16_t _y = 0) : x(_x), y(_y)
		{
		}

		Point(const Point& p) : x(p.x), y(p.y)
		{
		}

		Point&	operator=(const Point& p)
		{
			this->x = p.x;
			this->y = p.y;
			return *this;
		}

		int16_t		x;
		int16_t		y;
	};

	struct Line
	{
		Line(int16_t x1 = 0, int16_t y1 = 0, int16_t x2 = 0, int16_t y2 = 0) : p1(x1, y1), p2(x2, y2)
		{
		}

		Line(Point _p1, Point _p2) : p1(_p1), p2(_p2)
		{
		}

		Line(const Line& l) : p1(l.p1), p2(l.p2)
		{
		}

		Line&	operator=(const Line& l)
		{
			this->p1 = l.p1;
			this->p2 = l.p2;
			return *this;
		}

		Point	p1;
		Point	p2;
	};

	struct Circle
	{
		Circle(int16_t _x = 0, int16_t _y = 0, double _radius = 0) : center(_x, _y), radius(_radius)
		{
		}

		Circle(Point p, double _radius = 0) : center(p), radius(_radius)
		{
		}

		Circle(const Circle& c) : center(c.center), radius(c.radius)
		{
		}

		Circle&	operator=(const Circle& c)
		{
			this->center = c.center;
			this->radius = c.radius;
			return *this;
		}

		Point	center;
		double	radius;
	};

	struct	Rect
	{
		Rect(int16_t _x = 0, int16_t _y = 0,
		     uint16_t _w = 0, uint16_t _h = 0) : x(_x), y(_y),
							 w(_w), h(_h)
		{
		}

		Rect(const Rect& r) : x(r.x), y(r.y),
				      w(r.w), h(r.h)
		{
		}

		Rect&	operator=(const Rect& r)
		{
			this->x = r.x;
			this->y = r.y;
			this->w = r.w;
			this->h = r.h;
			return *this;
		}

		int16_t		x;
		int16_t		y;
		uint16_t	w;
		uint16_t	h;
	};

	typedef struct	Cardinal_Size
	{
		Cardinal_Size(uint16_t _top = 0, uint16_t _bot = 0,
			      uint16_t _left = 0, uint16_t _right = 0) : top(_top), bot(_bot),
							 left(_left), right(_right)
		{
		}

		Cardinal_Size(const Cardinal_Size& cs) : top(cs.top), bot(cs.bot),
							 left(cs.left), right(cs.right)
		{
		}

		Cardinal_Size&	operator=(const Cardinal_Size& cs)
		{
			this->top = cs.top;
			this->bot = cs.bot;
			this->left = cs.left;
			this->right = cs.right;
			return *this;
		}

		uint16_t	top;
		uint16_t	bot;
		uint16_t	left;
		uint16_t	right;
	}		Border;

	struct	Color
	{
		Color(void) : r(0), g(0), b(0), a(0)
		{
		}

		Color(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) : r(_r), g(_g), b(_b), a(_a)
		{
		}

		Color&	operator=(const Color& c)
		{
			this->r = c.r;
			this->g = c.g;
			this->b = c.b;
			this->a = c.a;
			return *this;
		}

		Color&	operator=(uint32_t& c)
		{
			this->r = c >> 24;
			this->g = c >> 16;
			this->b = c >> 8;
			this->a = c;
			return *this;
		}

		inline uint32_t	ConvertToInt(uint8_t rShift = 16,
					     uint8_t gShift = 8,
					     uint8_t bShift = 0,
					     uint8_t aShift = 24) const
		{
			uint32_t c;

			c = (this->r << rShift) |
			    (this->g << gShift) |
			    (this->b << bShift) |
			    (this->a << aShift);
			return c;
		}
		uint8_t		r;
		uint8_t		g;
		uint8_t		b;
		uint8_t		a;
	};
};

#endif

