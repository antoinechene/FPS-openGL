#ifndef	__GCIRCLE_H__
#define	__GCIRCLE_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Drawable/Drawable.h"

namespace	ID
{
	class	GCircle : public Drawable
	{
		public:
					GCircle(uint32_t radius,
						bool fulfil = true,
						Color* color = (Color*)&(COLOR_BLACK));
					~GCircle();

			void		SetColor(uint32_t color);
			void		SetColor(Color* color);
			void		SetRadius(uint32_t radius);
			void		SetFulfil(bool fulfil);

			Color		GetColor(void);
			uint32_t	GetRadius(void);
			bool		GetFulfil(void);

			virtual	int	RefreshToSurface(Surface* surface, int x, int y);
		private:
			uint32_t	__radius;
			Color		__color;
			bool		__fulfil;
	};
};

#endif
