#ifndef	__WRAPPER_INTERFACE_SDL_INLINE_HPP__
#define	__WRAPPER_INTERFACE_SDL_INLINE_HPP__

inline virtual int		Init(void)
{
	return 0;
}

inline virtual void		Destroy(void)
{
}

inline virtual int		Update(Surface* s, ID::Rect* r)
{
	if (r == 0)
		SDL_UpdateRect(s->__surface, 0, 0, 0, 0);
	else
		SDL_UpdateRect(s->__surface, r->x, r->y, r->w, r->h);
	return 0;
}

inline virtual int	LoadImage(Surface* s, const char* path,
				  int x, int y, bool )
{
//	Surface*	surf;
	ID::Rect	size(x, y);

//	surf = new Surface();
//	if (surf == 0)
//		return (-1);
	s->__surface = SDL_LoadBMP(path);
	if (s->__surface == NULL)
		return (-1);
	s->__w = s->__surface->w;
	s->__h = s->__surface->h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;
	size.w = s->w;
	size.h = s->h;
/*	if (s->w != s->w + x ||
	    s->h != s->h + y)
		if (s->Resize(size.w, size.h) == -1)
			return (-1);
	if (resize == true)
	{
		//all-michael: APPELLE A L'ALGO DE RESIZE ICI
	}*/
//	if (this->BlitSurface(surf, &size, s, 0, 0) == -1)
//		return (-1);
//	*s = *surf;
	return (0);
}

inline virtual int	CreateSurface(Surface* s, uint16_t w,
				      uint16_t h, uint32_t f,
				      uint32_t rmask, uint32_t gmask,
				      uint32_t bmask, uint32_t amask)
{
	s->__surface = SDL_CreateRGBSurface(f, w, h, 32,
					    rmask, gmask,
					    bmask, amask);
	if (s->__surface == NULL)
		return -1;
	s->__flags = f;
	s->__w = w;
	s->__h = h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;
	return 0;
}

inline virtual int	SetVideoMode(Surface* s, uint16_t w, uint16_t h, uint32_t f)
{
	s->__surface = SDL_SetVideoMode(w, h, 32, f);
	if (s->__surface == NULL)
		return -1;
	s->__flags = f;
	s->__w = w;
	s->__h = h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;
	return 0;
}

inline virtual void	DeleteSurface(Surface* s)
{
	SDL_FreeSurface(s->__surface);
}

inline virtual uint32_t	GetPixel(Surface* s, uint16_t x, uint16_t y)
{
	int		bpp;
	uint8_t*	p;

	bpp = s->__surface->format->BytesPerPixel;
	p = (uint8_t*)s->__surface->pixels + y * s->__surface->pitch + x * bpp;
	if (bpp == 1)
		return *p;
	if (bpp == 2)
		return *(uint16_t*)p;
	if (bpp == 3)
	{
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	}
	if (bpp == 4)
		return *(uint32_t*)p;
	return 0;
}

inline virtual void	SetPixel(Surface* s,
				 uint16_t x, uint16_t y, uint32_t c)
{
	int		bpp;
	uint8_t*	p;

	bpp = s->__surface->format->BytesPerPixel;
	p = (uint8_t*)s->pixels + y * s->__pitch + x * bpp;
	if (bpp == 1)
		*p = c;
	else if (bpp == 2)
		*(uint16_t*)p = c;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (c >> 16) & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = c & 0xff;
		}
		else
		{
			p[0] = c & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = (c >> 16) & 0xff;
		}
	}
	else
		*(uint32_t*)p = c;
}

inline virtual int	FillRect(Surface* s, ID::Rect* r,
				 uint32_t c)
{
	return SDL_FillRect(s->__surface, (SDL_Rect*)r, c);
}

inline virtual int	SetColorKey(Surface* s, uint32_t f, uint32_t k)
{
	return SDL_SetColorKey(s->__surface, f, k);
}

inline virtual int	BlitSurface(Surface* s, ID::Rect* src_r,
				    Surface* dest, int dest_x, int dest_y)
{
	SDL_Rect	dst_r;

	dst_r.x = dest_x;
	dst_r.y = dest_y;
	return SDL_BlitSurface(s->__surface, (SDL_Rect*)src_r, dest->__surface, &dst_r);
}

inline void	GetRGBA(Surface* surface,
				uint32_t color, ID::Color* s_color)
{
	SDL_GetRGBA(color, surface->__surface->format,
		    &(s_color->r), &(s_color->g), &(s_color->b), &(s_color->a));
}

inline uint32_t	MapRGBA(Surface* surface,
				uint8_t red, uint8_t green,
				uint8_t blue, uint8_t alpha)
{
	return SDL_MapRGBA(surface->__surface->format, red, green, blue, alpha);
}

inline Surface*	Morph_SDL_to_ID(SDL_Surface* SDL_s)
{
	Surface*	ID_s;

	ID_s = new Surface(SDL_s->w, SDL_s->h, SDL_s->flags,
			       0xFF0000, 0xFF00, 0xFF, 0xFF000000);
	if (ID_s == 0)
		return (0);
	this->CopyPixelsByByte(SDL_s, ID_s);
	return ID_s;
}

inline uint8_t	GetColorWithAlpha(uint8_t src_color, uint8_t dst_color, uint8_t alpha)
{
	return (src_color * alpha + (256 - alpha) * dst_color) >> 8;
}

inline void	SetPixelWithAlpha(uint8_t* dst, uint8_t* src, int sbpp)
{
	uint32_t	src_color;

	src_color = *(uint32_t*)src;
	if (sbpp == 4)
	{
		if ((src_color >> 24 & 0xFF) == 0xFF)
			*(uint32_t*)dst = src_color;
		else if ((src_color >> 24 & 0xFF) == 0)
			return ;
		else if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			dst[0] = this->GetColorWithAlpha(src_color >> 16 & 0xFF,
							 dst[0],
							 src_color >> 24 & 0xFF);
			dst[1] = this->GetColorWithAlpha(src_color >> 8 & 0xFF,
							 dst[1],
							 src_color >> 24 & 0xFF);
			dst[2] = this->GetColorWithAlpha(src_color & 0xFF,
							 dst[2],
							 src_color >> 24 & 0xFF);
		}
		else
		{
			dst[0] = this->GetColorWithAlpha(src_color & 0xFF,
							 dst[0],
							 src_color >> 24 & 0xFF);
			dst[1] = this->GetColorWithAlpha(src_color >> 8 & 0xFF,
							 dst[1],
							 src_color >> 24 & 0xFF);
			dst[2] = this->GetColorWithAlpha(src_color >> 16 & 0xFF,
							 dst[2],
							 src_color >> 24 & 0xFF);
		}
	}
	else if (sbpp == 1)
		*dst = *src;
	else if (sbpp == 2)
		*(uint16_t*)dst = *(uint16_t*)src;
	else if (sbpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			dst[0] = (src_color >> 16) & 0xff;
			dst[1] = (src_color >> 8) & 0xff;
			dst[2] = src_color & 0xff;
		}
		else
		{
			dst[0] = src_color & 0xff;
			dst[1] = (src_color >> 8) & 0xff;
			dst[2] = (src_color >> 16) & 0xff;
		}
	}
}

inline void	CopyPixelsByByte(SDL_Surface* SDL, Surface* ID)
{
	int			x;
	int			y;
	int			w;
	int			h;
	int			sbpp;
	int			dbpp;
	uint8_t*		dp;
	uint8_t*		sp;
	uint16_t		spitch;
	uint16_t		dpitch;

	sbpp = SDL->format->BytesPerPixel;
	spitch = SDL->pitch;
	h = SDL->h;
	w = SDL->w;
	sp = (uint8_t*)(SDL->pixels);
	if (h > ID->h)
		h = ID->h;
	if (w > ID->w)
		w = ID->w;
	if (h <= 0 || w <= 0)
		return ;
	y = 0;
	dbpp = ID->__surface->format->BytesPerPixel;
	dpitch = ID->__surface->pitch;
	dp = (uint8_t*)(ID->__surface->pixels);
	uint32_t	c;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			//this->SetPixelColorWithAlpha(dp, sp, sbpp);
			c = *(uint32_t*)sp;
			*(uint32_t*)dp = c;
			++x;
			dp = (uint8_t*)dp + dbpp;
			sp = (uint8_t*)sp + sbpp;
		}
		++y;
		dp = (uint8_t*)dp + dpitch - dbpp * x;
		sp = (uint8_t*)sp + spitch - sbpp * x;
	}
}


inline int	SetAlpha(Surface* surface, uint32_t flags, uint8_t alpha)
{
	return SDL_SetAlpha(surface->__surface, flags, alpha);
}

inline void	WM_SetCaption(const char* title, const char* icon)
{
	SDL_WM_SetCaption(title, icon);
}

inline int	WM_IconifyWindow(void)
{
	if (SDL_WM_IconifyWindow() != 0)
		return 0;
	return -1;
}

inline int	WM_ToggleFullScreen(Surface* surface)
{
	return !SDL_WM_ToggleFullScreen(surface->__surface);
}

inline void	WM_SetIcon(Surface* icon, uint8_t* mask)
{
	SDL_WM_SetIcon(icon->__surface, mask);
}

#endif
