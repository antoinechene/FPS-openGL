#ifndef __FONT_H__
#define __FONT_H__

#ifndef	__MAKE_H
#include <SDL/SDL_ttf.h>
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
			class	Police
			{
				public:
					Police(const char* path, int size);
					~Police();
					TTF_Font*	font;
					const char*	path;
					int		size;
			};
		public:
			Police*		LoadFont(const char* path, int size);
			ID::Surface*	TextRender(const char* text, Police* font, ID::Color* fg);
			int		SizeText(TTF_Font* font, const char* text, int* w, int* h);
		protected:
			Police*		_SearchFont(const char* font_path, int font_size);
		private:
			Font();
			~Font();
		private:
			std::vector<Police*>	_polices;
	};
}

#endif

