#ifndef	__DRAW_GEOMETRY_RECT_H__
#define	__DRAW_GEOMETRY_RECT_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Singleton.hpp"
#include "../Surface.h"

namespace	ID
{
	class	Surface;
	class	Draw_Geometry_Rect : public Singleton<Draw_Geometry_Rect>
	{
		friend class	Singleton<Draw_Geometry_Rect>;
		public:
			void		Draw(Surface* surface,
					     Rect* line,
					     bool fulfil,
					     uint32_t color = COLOR_BLACK.ConvertToInt());
			void		Draw(Surface* surface,
					     int16_t x, int16_t y,
					     int16_t width, int16_t height,
					     bool fulfil,
					     uint32_t color = COLOR_BLACK.ConvertToInt());
		private:
				Draw_Geometry_Rect();
				~Draw_Geometry_Rect();
			#include "Draw_Geometry_Rect_inline.hpp"

		private:
			Surface*	__target;
			uint32_t	__color;
	};
};

#endif
