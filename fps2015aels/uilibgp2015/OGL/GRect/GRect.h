#ifndef	__GRECT_H__
#define	__GRECT_H__

#include "../Common.h"
#include "../Colors.h"
#include "../Drawable/Drawable.h"

namespace	ID
{
	class	GRect : public Drawable
	{
		public:
					GRect(int16_t w, int16_t h,
					      bool fulfil,
					      Color* color = (Color*)&(COLOR_BLACK));
					~GRect();

/*			inline void	SetInvalidate(bool invalidate)
			{
				this->_SetInvalidate(invalidate);
				this->_AddUpdateRect();
			}
*/			void		SetDimension(int16_t w, int16_t h);
			void		SetFulfil(bool fulfil);
			void		SetColor(uint32_t color);
			void		SetColor(Color color);
/*
			inline int16_t		GetWidth(void) const
			{
				return this->__w;
			}
			inline int16_t		GetHeight(void) const
			{
				return this->__h;
			}
*/			inline bool		GetFulfil(void) const
			{
				return this->__fulfil;
			}
			inline Color		GetColor(void) const
			{
				return this->__color;
			}

			virtual	int	RefreshToSurface(Surface* surface, int x, int y);
		protected:
/*			inline void	_AddUpdateRect()
			{
				ID::Window*	w;

				w = this->GetRealWindow();
				if (w == NULL)
					return ;
				ID::Rect	rect(0, 0, 0, 0);
				if (this->GetWidth() < 0)
				{
					rect.x = this->_offset_x + this->_x + this->GetWidth();
					rect.w = 0 - this->GetWidth() + 1;
				}
				else
				{
					rect.x = this->_offset_x + this->_x;
					rect.w = this->GetWidth() + 1;
				}
				if (this->GetHeight() < 0)
				{
					rect.y = this->_offset_y + this->_y + this->GetHeight();
					rect.h = 0 - this->GetHeight() + 1;
				}
				else
				{
					rect.y = this->_offset_y + this->_y;
					rect.h = this->GetHeight() + 1;
				}
				w->AddUpdate(&rect);
			}*/

		private:
	//		uint16_t		__w;
	//		uint16_t		__h;
			bool		__fulfil;
			Color		__color;
	};
};

#endif
