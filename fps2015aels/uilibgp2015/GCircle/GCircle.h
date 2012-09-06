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

			inline void	SetInvalidate(bool i)
			{
				this->_SetInvalidate(i);
				this->_AddUpdateRect();
			}

			void		SetColor(uint32_t color);
			void		SetColor(Color* color);
			void		SetRadius(uint32_t radius);
			void		SetFulfil(bool fulfil);

			Color		GetColor(void);
			uint32_t	GetRadius(void);
			bool		GetFulfil(void);

			virtual	int	RefreshToSurface(Surface* surface, int x, int y);
		protected:
			inline void	_AddUpdateRect()
			{
				ID::Window*	w;

				w = this->GetRealWindow();
				if (w == NULL)
					return ;
				ID::Rect	rect(this->_offset_x + this->_x - this->GetWidth(),
						     this->_offset_y + this->_y - this->GetHeight(),
						     (this->GetWidth() << 1) + 1,
						     (this->GetHeight() << 1) + 1);
				w->AddUpdate(&rect);
			}

		private:
			uint32_t	__radius;
			Color		__color;
			bool		__fulfil;
	};
};

#endif
