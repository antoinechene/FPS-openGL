#ifndef	__GLINE_H__
#define	__GLINE_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Drawable/Drawable.h"

namespace	ID
{
	class	GLine : public Drawable
	{
		public:
					GLine(int16_t x, int16_t y,
					      int size,
					      Color* color = (Color*)&(COLOR_BLACK));
					~GLine();

			void		SetVector(int16_t vX, int16_t vY);
			void		SetSize(uint16_t size);
			void		SetColor(uint32_t color);
			void		SetColor(Color color);

			Point		GetVector(void);
			uint16_t	GetSize(void);
			Color		GetColor(void);

			virtual	int	RefreshToSurface(Surface* surface, int x, int y);
		private:
			Point		__point;
			int		__size;
			Color		__color;
	};
};

#endif
