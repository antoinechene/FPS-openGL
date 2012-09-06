#include "Surface.h"
#include <SDL/SDL_ttf.h>
#include "Wrapper/Wrapper_Interface_SDL.h"

ID::Surface::Surface() : flags(__flags), w(__w), h(__h),
			 pitch(__pitch), pixels(NULL),
			 __isSetVideoMode(false),
			 __surface(NULL)
{
}

ID::Surface::Surface(uint16_t w, uint16_t h, uint32_t f,
		     uint32_t rmask, uint32_t gmask,
		     uint32_t bmask, uint32_t amask) : flags(__flags), w(__w), h(__h),
						       pitch(__pitch), pixels(0),
						       __w(w), __h(h),
						       __isSetVideoMode(false)
{
	WI_GI->CreateSurface(this, w, h, f, rmask, gmask, bmask, amask);
}

ID::Surface::Surface(uint16_t w, uint16_t h,
		     uint32_t f, bool) : flags(__flags), w(__w), h(__h),
					 pitch(__pitch), pixels(0),
					 __w(w), __h(h),
					 __isSetVideoMode(true)
{
	WI_GI->SetVideoMode(this, w, h, f);
}

ID::Surface::Surface(const char* img) : flags(__flags), w(__w), h(__h),
					pitch(__pitch), pixels(0),
					__w(w), __h(h),
					__surface(NULL)
{
	if (this->LoadImage(img, 0, 0, false) == -1)
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
	if (this->__isSetVideoMode == false)
		WI_GI->DeleteSurface(this);
}

ID::Surface&	ID::Surface::operator=(const ID::Surface& s)
{
	this->__flags = s.__flags;
	this->__w = s.__w;
	this->__h = s.__h;
	this->__pitch = s.__pitch;
	this->pixels = s.pixels;
	this->__surface = s.__surface;
	return *this;
}

int		ID::Surface::Update(Rect* rect)
{
	return WI_GI->Update(this, rect);
}

ID::Surface*	ID::Surface::Clone()
{
	ID::Surface*	clone;

	clone = new ID::Surface(this->w, this->h, this->flags,
				this->__surface->format->Rmask,
				this->__surface->format->Gmask,
				this->__surface->format->Bmask,
				this->__surface->format->Amask);
	if (clone == 0)
		return NULL;
	this->BlitSurface(NULL, clone, 0, 0);
	return clone;
}

int		ID::Surface::Resize(uint16_t w, uint16_t h, uint32_t f, uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	ID::Surface		tmp = *this;

	if (this->__surface != NULL &&
	    WI_GI->CreateSurface(this, w, h, this->__flags,
					   this->__surface->format->Rmask,
					   this->__surface->format->Gmask,
					   this->__surface->format->Bmask,
					   this->__surface->format->Amask) == -1)
		return -1;
	else if (WI_GI->CreateSurface(this, w, h, f, r, g, b, a) == -1)
		return -1;
	tmp.BlitSurface(0, this, 0, 0);
	return 0;
}

int	ID::Surface::ResizeVideoMode(uint16_t w, uint16_t h)
{
	return WI_GI->SetVideoMode(this, w, h, this->__flags);
}

int	ID::Surface::LoadImage(const char* img, int x, int y, bool resize)
{
	return (WI_GI->LoadImage(this, img, x, y, resize));
}

void	ID::Surface::SetPixelTrans(uint16_t x, uint16_t y, Color* c)
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


void	ID::Surface::SetPixelTrans(uint16_t x, uint16_t y, uint32_t c)
{
	if (x < this->__w && y < this->__h)
	{
		uint8_t*	src;

		src = (uint8_t*)this->pixels + this->pitch * y +
		      this->__surface->format->BytesPerPixel * x;
		WI_GI->SetPixelWithAlpha(src, (uint8_t*)&c, 4);
	}
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

int	ID::Surface::BlitSurface(ID::Rect* src_rect,
					 ID::Surface* dest,
					 int dest_x, int dest_y)
{
	return (WI_GI->BlitSurface(this, src_rect, dest, dest_x, dest_y));
}

int	ID::Surface::SetColorKey(uint32_t f, uint32_t k)
{
	return (WI_GI->SetColorKey(this, f, k));
}

int	ID::Surface::TTF_New_Text(const char* font_path, int font_size, const char* text, ID::Color fg,
				  int x, int y)
{
	TTF_Font*	font;
	SDL_Color	sdl_fg;
	SDL_Surface*	n_surface;
	SDL_Rect	rect_surface;

	sdl_fg.r = fg.r;
	sdl_fg.g = fg.g;
	sdl_fg.b = fg.b;
	rect_surface.x = x;
	rect_surface.y = y;
	rect_surface.w = this->__w - x;
	rect_surface.h = this->__h - y;
	font = TTF_OpenFont(font_path, font_size);
	if (font == NULL)
		return (1);
	n_surface = TTF_RenderText_Solid(font, text, sdl_fg);
	SDL_BlitSurface(n_surface, &rect_surface, this->__surface, 0);
	SDL_FreeSurface(n_surface);
	TTF_CloseFont(font);
	return (0);
}

void		ID::Surface::GetRGBA(uint32_t color, Color* s_color)
{
	WI_GI->GetRGBA(this, color, s_color);
}

uint32_t	ID::Surface::MapRGBA(uint8_t red, uint8_t green,
		uint8_t blue, uint8_t alpha)
{
	return WI_GI->MapRGBA(this, red, green, blue, alpha);
}

int		ID::Surface::SetAlpha(uint32_t flags, uint8_t alpha)
{
	return WI_GI->SetAlpha(this, flags, alpha);
}

uint32_t	ID::Surface::GetRmask(void)
{
	return this->__surface->format->Rmask;
}

uint32_t	ID::Surface::GetGmask(void)
{
	return this->__surface->format->Gmask;
}

uint32_t	ID::Surface::GetBmask(void)
{
	return this->__surface->format->Bmask;
}

uint32_t	ID::Surface::GetAmask(void)
{
	return this->__surface->format->Amask;
}
