#include "Button.h"

ID::Button::Button(void) : Drawable()
{
}

ID::Button::Button(uint16_t w, uint16_t h) : Drawable(w, h)
{
}

ID::Button::Button(const ID::Button&) : Drawable()
{
}

ID::Button::~Button(void)
{
}

int	ID::Button::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
//	if (this->GetInvalidate() == true)
//		this->_RefreshBackground();
	if (this->_surface->BlitSurface(x + this->_x, y + this->_y) == -1)
		return -1;
	return 0;
}

