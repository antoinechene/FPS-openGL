#include "Button.h"

ID::Button::Button(void) : Drawable()
{
}

ID::Button::Button(uint16_t w, uint16_t h, uint16_t f,
		   uint32_t rmask, uint32_t gmask,
		   uint32_t bmask, uint32_t amask) : Drawable(w, h, f,
							      rmask, gmask, bmask, amask)
{
}

ID::Button::Button(const ID::Button&) : Drawable()
{
}

ID::Button::~Button(void)
{
}

int	ID::Button::RefreshToSurface(ID::Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->GetInvalidate() == true)
		this->_RefreshBackground();
	if (s != NULL &&
	    this->_surface->BlitSurface(this->_visibleRect, s, x + this->_x, y + this->_y) == -1)
		return -1;
	this->SetInvalidate(false);
	return 0;
}

