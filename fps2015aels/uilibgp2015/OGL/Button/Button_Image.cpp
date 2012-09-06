#include "Button_Image.h"

ID::Button_Image::Button_Image(uint16_t w, uint16_t h) : Button(w, h),
							 __imgX(0),
							 __imgY(0)
{
}

ID::Button_Image::Button_Image(const char* img) : Button(),
						  __imgX(0),
						  __imgY(0),
						  __imgRect(NULL)
{
	if (this->Resize(this->__image->w, this->__image->h))
		throw 205;
}

ID::Button_Image::Button_Image(const ID::Button_Image& b) : Button(b),
							    __imgX(b.__imgX),
							    __imgY(b.__imgY)
{
	this->__imgRect = new ID::Rect(*(b.__imgRect));
	if (this->__imgRect == NULL)
		throw 220;
}

ID::Button_Image::~Button_Image(void)
{
	delete this->__imgRect;
}

void	ID::Button_Image::SetImage(ID::Surface* surface)
{
	this->__image = surface;
}

ID::Surface*	ID::Button_Image::GetImage(void) const
{
	return this->__image;
}

void		ID::Button_Image::SetImagePosition(int x, int y)
{
	this->__imgX = x;
	this->__imgY = y;
}

int	ID::Button_Image::SetImageVisible(ID::Rect* rect)
{
	if (this->__imgRect != NULL)
		delete this->__imgRect;
	this->__imgRect = new ID::Rect(*rect);
	if (this->__imgRect == NULL)
		return -1;
	return 0;
}

void	ID::Button_Image::GetImageVisible(ID::Rect* rect) const
{
	*rect = *this->__imgRect;
}

int	ID::Button_Image::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
//	if (this->GetInvalidate() == true)
	{
		this->_RefreshBackground();
		if (this->__image != NULL)
			this->__image->BlitSurface(this->__imgRect, this->_surface,
						   this->__imgX, this->__imgY);
	}
	if (s != NULL &&
	    this->_surface->BlitSurface(this->_visibleRect, s, x + this->_x, y + this->_y) == -1)
		return -1;
	if (this->_cbUpdate != NULL)
		this->_cbUpdate(this, this->__cbUpdateData);
	return 0;
}

