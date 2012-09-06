#ifndef	__GPOLYGON_H__
#define	__GPOLYGON_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Drawable/Drawable.h"

#ifndef	__MAKE_H
#include <vector>
#endif

namespace	ID
{
	class	GPolygon : public Drawable
	{
		public:
					GPolygon(int size, bool fulfil,
						 Color* color = (Color*)&(COLOR_BLACK));
					~GPolygon();

			void		AddPoint(int16_t x, int16_t y);
			void		AddPoint(Point* point);
			void		SetFulfil(bool fulfil);
			void		SetColor(uint32_t color);
			void		SetColor(Color color);

			std::vector<Point>*	GetPoints(void);
			bool		GetFulfil(void);
			Color		GetColor(void);

			virtual	int	RefreshToSurface(Surface* surface, int x, int y);
		private:
			std::vector<Point>	__points;
			bool			__size;
			bool			__fulfil;
			Color			__color;
	};
};

#endif
