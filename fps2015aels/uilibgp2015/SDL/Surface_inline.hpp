#ifndef	__SURFACE_INLINE_HPP
#define	__SURFACE_INLINE_HPP

int		Update(Rect* rect)
{
	return WI_GI->Update(this, rect);
}

int	ResizeVideoMode(uint16_t w, uint16_t h)
{
	return WI_GI->SetVideoMode(this, w, h, this->__flags);
}

int	LoadImage(const char* img, int x, int y, bool resize)
{
	return (WI_GI->LoadImage(this, img, x, y, resize));
}

void	SetPixelTrans(uint16_t x, uint16_t y, Color* c)
{
	if (x < this->__w && y < this->__h)
	{
		uint8_t*	src;
		uint32_t	color;

		src = (uint8_t*)this->pixels + this->pitch * y +
		      this->__surface->format->BytesPerPixel * x;
		color = c->ConvertToInt();
		WI_GI->SetPixelWithAlpha(src,
					 (uint8_t*)&color, 4);
	}
}


void	SetPixelTrans(uint16_t x, uint16_t y, uint32_t c)
{
	if (x < this->__w && y < this->__h)
	{
		uint8_t*	src;

		src = (uint8_t*)this->pixels + this->pitch * y +
		      this->__surface->format->BytesPerPixel * x;
		WI_GI->SetPixelWithAlpha(src, (uint8_t*)&c, 4);
	}
}

void	SetPixel(uint16_t x, uint16_t y, uint32_t color)
{
	if (x < this->__w && y < this->__h)
		WI_GI->SetPixel(this, x, y, color);
}

void	SetPixel(uint16_t x, uint16_t y, Color* color)
{
	if (x < this->__w && y < this->__h)
		WI_GI->SetPixel(this, x, y, color->ConvertToInt());
}

uint32_t	GetPixel(uint16_t x, uint16_t y)
{
	return (WI_GI->GetPixel(this, x, y));
}

int	FillRect(Rect* rect, Color* struct_color)
{
	return (WI_GI->FillRect(this, rect, int_color->ConvertToInt()));
}

int	FillRect(Rect* rect, uint32_t color)
{
	return (WI_GI->FillRect(this, rect, color));
}

int	BlitSurface(Rect* src_rect,
		 Surface* dest,
		 int dest_x, int dest_y)
{
	return (WI_GI->BlitSurface(this, src_rect, dest, dest_x, dest_y));
}

int	SetColorKey(uint32_t f, uint32_t k)
{
	return (WI_GI->SetColorKey(this, f, k));
}

void		GetRGBA(uint32_t color, Color* s_color)
{
	WI_GI->GetRGBA(this, color, s_color);
}

uint32_t	MapRGBA(uint8_t red, uint8_t green,
		uint8_t blue, uint8_t alpha)
{
	return WI_GI->MapRGBA(this, red, green, blue, alpha);
}

int		SetAlpha(uint32_t flags, uint8_t alpha)
{
	return WI_GI->SetAlpha(this, flags, alpha);
}

uint32_t	GetRmask(void)
{
	return this->__surface->format->Rmask;
}

uint32_t	GetGmask(void)
{
	return this->__surface->format->Gmask;
}

uint32_t	GetBmask(void)
{
	return this->__surface->format->Bmask;
}

uint32_t	GetAmask(void)
{
	return this->__surface->format->Amask;
}

#endif
