#ifndef	__DRAW_GEOMETRY_LINE_H__
#define	__DRAW_GEOMETRY_LINE_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Singleton.hpp"

namespace	ID
{
	class	Surface;
	class	Draw_Geometry_Line : public Singleton<Draw_Geometry_Line>
	{
		friend class	Singleton<Draw_Geometry_Line>;
		public:
			void		Draw(Surface* surface,
					     Line* line, int size,
					     Color* color = (Color*)&(COLOR_BLACK));
			void		Draw(Surface* surface,
					     int16_t x1, int16_t y1,
					     int16_t x2, int16_t y2,
					     int size,
					     Color* color = (Color*)&(COLOR_BLACK));
		private:
				Draw_Geometry_Line();
				~Draw_Geometry_Line();

		private:
			void	__Line(int x1, int y1, int x2, int y2);
			void	__PixelBrush(int x_center, int y_center);
			void	__PixelBrush_1(int x_center, int y_center);
			void	__PixelBrush_2(int x_center, int y_center);
			void	__PixelBrush_3(int x_center, int y_center);
			void	__PixelBrush_4(int x_center, int y_center);
			void	__PixelBrush_5(int x_center, int y_center);
			void	__PixelBrush_6(int x_center, int y_center);
			void	__PixelBrush_7(int x_center, int y_center);
			void	__PixelBrush_8(int x_center, int y_center);
		private:
			int		__lastX;
			int		__lastY;
			int		__size;
			Surface*	__target;
			Color*		__color;
	};
};

#endif
