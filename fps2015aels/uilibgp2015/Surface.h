#ifndef __SURFACE_H__
#define __SURFACE_H__

#ifdef	__SDL
#ifndef	__MAKE_H
#include <SDL/SDL.h>
#endif

#define	WRAPPER_SURFACE		SDL_Surface
#define	ID_DEFAULT_FLAGS	SDL_SWSURFACE
#endif

#include "Common.h"

#define	WI_GI	ID::Wrapper_Interface::GetInstance()

namespace ID
{
	class Surface
	{
		friend class		Wrapper_Interface;
		typedef WRAPPER_SURFACE	surface;

		public:
					Surface(void);
					Surface(uint16_t width, uint16_t height, uint32_t flags,
						uint32_t rmask, uint32_t gmask,
						uint32_t bmask, uint32_t amask);
					Surface(uint16_t width, uint16_t height, uint32_t flags,
						bool is_set_video_mode);
					Surface(const char* img_to_load);
					~Surface();
			Surface&	operator=(const Surface& surface);
			int		Update(Rect* rect);
			Surface*	Clone(void);
			int		Resize(uint16_t width, uint16_t height, uint32_t flags = ID_DEFAULT_FLAGS,
					       uint32_t rmask = 0, uint32_t gmask = 0, uint32_t bmask = 0, uint32_t amask = 0);
			int		ResizeVideoMode(uint16_t width, uint16_t height);
			int		LoadImage(const char* img_to_load,
						  int x = 0, int y = 0,
						  bool resize = true);
			void		SetPixelTrans(uint16_t x, uint16_t y, Color* c);
			void		SetPixelTrans(uint16_t x, uint16_t y, uint32_t color);
			void		SetPixel(uint16_t x, uint16_t y, uint32_t color);
			void		SetPixel(uint16_t x, uint16_t y, Color* color);
			uint32_t	GetPixel(uint16_t x, uint16_t y);
			int		FillRect(Rect* rect, Color* color);
			int		FillRect(Rect* rect, uint32_t color);
			int		BlitSurface(Rect* src_rect,
						    Surface* dest,
						    int dest_x, int dest_y);
			int		SetColorKey(uint32_t flags, uint32_t key);
			int		TTF_New_Text(const char* font_path, int font_size,
						     const char* text, Color fg, int x,
						     int y);
			void		GetRGBA(uint32_t color, Color* s_color);
			uint32_t	MapRGBA(uint8_t red, uint8_t green,
						uint8_t blue, uint8_t alpha);
			int		SetAlpha(uint32_t flags, uint8_t alpha);
			uint32_t	GetRmask(void);
			uint32_t	GetGmask(void);
			uint32_t	GetBmask(void);
			uint32_t	GetAmask(void);

		public:
			const uint32_t&		flags;
			const uint16_t&		w;
			const uint16_t&		h;
			const uint16_t&		pitch;
			void*			pixels;

		private:
			uint32_t		__flags;
			uint16_t		__w;
			uint16_t		__h;
			uint16_t		__pitch;
			bool			__isSetVideoMode;
			surface*		__surface;
	};
}

#endif
