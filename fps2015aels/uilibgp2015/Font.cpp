#include "Font.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "Wrapper/Wrapper_Interface_SDL.h"
#include <iostream>

ID::Font::Font()
{
}

ID::Font::~Font()
{
	std::vector<Police*>::iterator	it;
	std::vector<Police*>::iterator	end;

	it = this->_polices.begin();
	end = this->_polices.end();
	while (it != end)
	{
		delete *it;
		++it;
	}
	this->_polices.clear();
}

ID::Font::Police*	ID::Font::LoadFont(const char* path, int size)
{
	Police*	r_val;

	r_val = this->_SearchFont(path, size);
	if (r_val != 0)
		return r_val;
	r_val = new Police(path, size);
	this->_polices.push_back(r_val);
	return r_val;
}

ID::Surface*	ID::Font::TextRender(const char* text, Police* font, ID::Color* fg)
{
	ID::Surface*	r_val;
	SDL_Surface*	surface;
	SDL_Color	color;

	color.r = fg->r;
	color.g = fg->g;
	color.b = fg->b;
	color.unused = fg->a;
	if (text == NULL)
	{
		std::cout << "Text = NULL\n";
		return NULL;
	}
	surface = TTF_RenderText_Blended(font->font, text, color);
	if (surface == 0)
	{
		std::cout << "RenderText: Error\n";
		return NULL;
	}
	r_val = ID::Wrapper_Interface::GetInstance()->Morph_SDL_to_ID(surface);
	if (r_val == 0)
	{
		std::cout << "Morph: Error\n";
		return NULL;
	}
	SDL_FreeSurface(surface);
	return (r_val);
}

int		ID::Font::SizeText(TTF_Font* font, const char* text, int* w, int* h)
{
	return TTF_SizeText(font, text, w, h);
}

ID::Font::Police*	ID::Font::_SearchFont(const char* path, int size)
{
	std::vector<Police*>::iterator	it;
	std::vector<Police*>::iterator	end;

	it = this->_polices.begin();
	end = this->_polices.end();
	while (it != end)
	{
		if ((*it)->size == size &&
		    strcmp((*it)->path, path) == 0)
			return *it;
		++it;
	}
	return 0;
}

ID::Font::Police::Police(const char* path, int size)
{
	this->font = TTF_OpenFont(path, size);
	if (!(this->font))
	{
		std::cout << "Load_New_Font: " << TTF_GetError() << std::endl;
		throw 1000;
	}
	this->path = path;
	this->size = size;
}

ID::Font::Police::~Police()
{
	TTF_CloseFont(this->font);
}
