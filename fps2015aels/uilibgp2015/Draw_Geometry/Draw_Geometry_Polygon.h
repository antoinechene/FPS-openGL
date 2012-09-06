#ifndef	__DRAW_GEOMETRY_POLYGON_H__
#define	__DRAW_GEOMETRY_POLYGON_H__

#include "../Common.h"
#include "../Colors.h"
#include "../GPolygon/GPolygon.h"
#include "../Singleton.hpp"

#ifndef	__MAKE_H
#include <vector>
#include <list>
#include <map>
#endif

namespace	ID
{
	class	Surface;
	class	Draw_Geometry_Polygon : public Singleton<Draw_Geometry_Polygon>
	{
		friend class	Singleton<Draw_Geometry_Polygon>;
		public:
			void		Draw(Surface* surface,
					     int16_t x, int16_t y,
					     GPolygon* polygon,
					     int size,
					     bool fulfil,
					     Color* color = (Color*)&(COLOR_BLACK));
			void		Draw(Surface* surface,
					     int16_t x, int16_t y,
					     std::vector<Point>* v,
					     int size,
					     bool fulfil,
					     Color* color = (Color*)&(COLOR_BLACK));
		private:
				Draw_Geometry_Polygon();
				~Draw_Geometry_Polygon();
			void	__Polygon(int16_t originX, int16_t originY, std::vector<Point>* list, bool fulfil);
			void	__Fill(void);
			void	__SetPixelTrans(uint16_t x, uint16_t y);
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
			int				__lastX;
			int				__lastY;
			int				__size;
			Surface*			__target;
			Color*				__color;
			std::map<int, std::list<int> >	__points;
	};
};

#endif
