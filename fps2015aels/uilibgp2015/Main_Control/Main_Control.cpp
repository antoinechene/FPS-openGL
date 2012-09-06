#include "Main_Control.h"
#include "../Window/Window.h"

ID::Main_Control::Main_Control(uint16_t w, uint16_t h, uint32_t f,
			       uint32_t r, uint32_t g, uint32_t b, uint32_t a) : Drawable(w, h, f,
											  r, g, b, a)
{
}

ID::Main_Control::Main_Control(const ID::Main_Control& mc) : Drawable(mc)
{
}

ID::Main_Control::~Main_Control()
{
}

ID::Main_Control&	ID::Main_Control::operator=(const ID::Main_Control& mc)
{
	*this = mc;
	return *this;
}

void	ID::Main_Control::_SetInvalidate(bool i)
{
	this->_isInvalidate = i;
	if (i == true && this->_window != NULL)
		this->_window->SetInvalidate(true);
}

bool	ID::Main_Control::GetInvalidate(void) const
{
	return this->_isInvalidate;
}

int	ID::Main_Control::RefreshToSurface(Surface* s, int, int)
{
	std::list<Drawable*>::iterator	it;
	std::list<Drawable*>::iterator	end;

	if (this->GetOnScreen() == false)
		return 0;
	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if ((*it)->RefreshToSurface(s, this->_x, this->_y) == -1)
			return -1;
		++it;
	}
	this->SetInvalidate(false);
	return 0;
}

