#ifndef	__DRAW_GEOMETRY_CIRCLE_H__
#define	__DRAW_GEOMETRY_CIRCLE_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Singleton.hpp"

namespace	ID
{
	class	Surface;
	class	Draw_Geometry_Circle : public Singleton<Draw_Geometry_Circle>
	{
		friend class	Singleton<Draw_Geometry_Circle>;
		public:
			void		Draw(Surface* surface,
					     Circle* line,
					     bool fulfil,
					     Color* color = (Color*)&(COLOR_BLACK));
			void		Draw(Surface* surface,
					     int16_t x, int16_t y,
					     int radius,
					     bool fulfil,
					     Color* color = (Color*)&(COLOR_BLACK));
		private:
				Draw_Geometry_Circle();
				~Draw_Geometry_Circle();
			void	__Circle(int x, int y, int radius,
					 bool fulfil);
			float	__Distance(int xa, int ya,
					   int xb, int yb);
			float	__Sqrt(float n);

		private:
			Surface*	__target;
			Color*		__color;
	};
};

#endif
