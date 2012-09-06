#ifndef __FONT_H__
#define __FONT_H__

#ifndef	__MAKE_H
#include <vector>
#endif
#include "Surface.h"
#include "Common.h"
#include "Singleton.hpp"

namespace ID
{
	class	Font : public Singleton<Font>
	{
		friend class	Singleton<Font>;
		public:
			void	TextRender(const char* str, void* font, ID::Color* fg, int x, int y, int z);
			int		SizeText(void* font, const char* text, int* w, int* h);
		private:
			Font();
			~Font();
	};
}

#endif

