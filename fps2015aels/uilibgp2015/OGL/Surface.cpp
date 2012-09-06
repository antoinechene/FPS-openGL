#include "Surface.h"
#include <SDL/SDL_ttf.h>
#include "Wrapper/Wrapper_Interface_OGL.h"
#include "Texture_Manager.h"

ID::Surface::Surface() : w(__w), h(__h), txtID(__txtID), color(__color),
			 __blend(false),
			 __w(0), __h(0), __txtID(0)
{
	this->__color[0] = 0.0f;
	this->__color[1] = 0.0f;
	this->__color[2] = 0.0f;
	this->__color[3] = 1.0f;
}

ID::Surface::Surface(uint16_t w, uint16_t h) : w(__w), h(__h),
					       txtID(__txtID), color(__color),
					       __blend(false),
					       __w(w), __h(h), __txtID(0)
{
	this->__color[0] = 0.0f;
	this->__color[1] = 0.0f;
	this->__color[2] = 0.0f;
	this->__color[3] = 1.0f;
}

ID::Surface::Surface(const char* img) : w(__w), h(__h),
					txtID(__txtID), color(__color),
					__blend(false),
					__w(0), __h(0), __txtID(0)
{
	this->__color[0] = 0.0f;
	this->__color[1] = 0.0f;
	this->__color[2] = 0.0f;
	this->__color[3] = 1.0f;
	if (this->LoadImage(img) == -1)
		throw 330;
}
/*
ID::Surface::Surface(const ID::Surface& s) : flags(__flags), w(__w), h(__h),
					     pitch(__pitch), pixels(0)
{
	WI_GI->CreateSurface(this, s.w, s.h, s.flags);
}*/

ID::Surface::~Surface()
{
	WI_GI->DeleteSurface(this);
}

ID::Surface&	ID::Surface::operator=(const ID::Surface& s)
{
	this->__w = s.__w;
	this->__h = s.__h;
	this->__txtID = s.__txtID;
	this->__color[0] = s.__color[0];
	this->__color[1] = s.__color[1];
	this->__color[2] = s.__color[2];
	this->__color[3] = s.__color[3];
	return *this;
}

ID::Surface*	ID::Surface::Clone()
{
	ID::Surface*	clone;

	clone = new ID::Surface(this->w, this->h);
	if (clone == 0)
		return NULL;
//	this->BlitSurface(NULL, clone, 0, 0);
	return clone;
}

int		ID::Surface::Resize(uint16_t w, uint16_t h)
{
	this->__w = w;
	this->__h = h;
//	tmp.BlitSurface(0, this, 0, 0);
	return 0;
}

int	ID::Surface::LoadImage(const char* img)
{
	return ID::Texture_Manager::GetInstance()->LoadTexture(img, &(this->__txtID));
//	return WI_GI->LoadImage(this, img);
}

void	ID::Surface::SetColor(float r, float g, float b, float a)
{
	this->__color[0] = r;
	this->__color[1] = g;
	this->__color[2] = b;
	this->__color[3] = a;
}

void	ID::Surface::SetColor(float* color)
{
	this->__color[0] = color[0];
	this->__color[1] = color[1];
	this->__color[2] = color[2];
	this->__color[3] = color[3];
}

void	ID::Surface::SetPixel(uint16_t x, uint16_t y, uint32_t color)
{
	if (x < this->__w && y < this->__h)
		WI_GI->SetPixel(this, x, y, color);
}

void	ID::Surface::SetPixel(uint16_t x, uint16_t y, Color* color)
{
	if (x < this->__w && y < this->__h)
		WI_GI->SetPixel(this, x, y, color->ConvertToInt());
}

uint32_t	ID::Surface::GetPixel(uint16_t x, uint16_t y)
{
	return (WI_GI->GetPixel(this, x, y));
}

int	ID::Surface::FillRect(ID::Rect* rect, ID::Color* struct_color)
{
	uint32_t	int_color;

	int_color = 0;
	int_color = struct_color->r << 16 |
		    struct_color->g << 8 |
		    struct_color->b;
	return (WI_GI->FillRect(this, rect, int_color));
}

int	ID::Surface::FillRect(ID::Rect* rect, uint32_t color)
{
	return (WI_GI->FillRect(this, rect, color));
}

int	ID::Surface::BlitSurface(
				 int dest_x, int dest_y)
{
	return (WI_GI->BlitSurface(this, dest_x, dest_y));
}

void	ID::Surface::SetBlend(bool b)
{
	this->__blend = b;
}

bool	ID::Surface::GetBlend(void) const
{
	return this->__blend;
}

