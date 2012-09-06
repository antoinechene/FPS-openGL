#ifndef __SURFACE_H__
#define __SURFACE_H__

#ifdef	__OGL

#ifndef	__MAKE_H
#include <GL/glut.h>
#endif

#define	WRAPPER_SURFACE		void
#define	ID_DEFAULT_FLAGS	NULL

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
					Surface(uint16_t width, uint16_t height);
					Surface(const char* img_to_load);
					~Surface();
			Surface&	operator=(const Surface& surface);
			Surface*	Clone(void);
			int		Resize(uint16_t width, uint16_t height);
			int		LoadImage(const char* img_to_load);
			void		SetColor(float r, float g, float b, float a);
			void		SetColor(float* color);
			void		SetPixel(uint16_t x, uint16_t y, uint32_t color);
			void		SetPixel(uint16_t x, uint16_t y, Color* color);
			uint32_t	GetPixel(uint16_t x, uint16_t y);
			int		FillRect(Rect* rect, Color* color);
			int		FillRect(Rect* rect, uint32_t color);
			int		BlitSurface(int dest_x, int dest_y);
			void		SetBlend(bool);
			bool		GetBlend(void) const;

		public:
			const uint16_t&		w;
			const uint16_t&		h;
			const uint32_t&		txtID;
			const float*		color;

		private:
			bool			__blend;
			uint16_t		__w;
			uint16_t		__h;
			uint32_t		__txtID;
			float			__color[4];
	};
}

#endif
