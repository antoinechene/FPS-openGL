#ifndef __LABEL_H__
#define __LABEL_H__

#include "../Drawable/Drawable.h"
#include "../Surface.h"
#include "../Common.h"
#include "../Colors.h"
#include "../Font.h"

namespace ID
{
	class	Label : public Drawable
	{
		public:
					Label(void* font, char* text,
					      Color* fg = (Color*)&COLOR_BLACK);
					Label(const ID::Label& b);
			virtual		~Label();
			char*		GetText(void) const;
			void		SetText(char* Text);
			void		SetColor(Color fg);
			void		SetColor(uint32_t fg);
			Color		GetColor(void) const;
			void		SetFont(void* fond);
			void*		GetFont(void) const;
			virtual int	RefreshSurface(int x, int y);

		private:
			char*	__text;
			Color	__color;
			void*	__font;
	};
}

#endif
