#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	Button : public Drawable
	{
	public:
				Button(void);
				Button(uint16_t w, uint16_t h, uint16_t f,
				       uint32_t rmask, uint32_t gmask,
				       uint32_t bmask, uint32_t amask);
				Button(const ID::Button& button);
		virtual		~Button(void);
		virtual int	RefreshToSurface(Surface* surface, int x, int y);
	};
}

#endif

