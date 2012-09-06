#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	Button : public Drawable
	{
	public:
				Button(void);
				Button(uint16_t w, uint16_t h);
				Button(const ID::Button& button);
		virtual		~Button(void);
		virtual int	RefreshSurface(int x, int y);
	};
}

#endif

