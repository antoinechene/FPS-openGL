#include "Label.h"
#include <iostream>
#include <SDL/SDL_ttf.h>
#include "../Wrapper/Wrapper_Interface_SDL.h"

ID::Label::Label(const char* font_path, int font_size, char* text,
		 ID::Color* fg) : Drawable()
{
	this->__text = strdup(text);
	this->__color = *fg;
	this->__police = ID::Font::GetInstance()->LoadFont(font_path, font_size);
	if (this->__police == NULL)
		throw 340;
	this->_surface = Font::GetInstance()->TextRender(this->__text,
							 this->__police,
							 &(this->__color));
	if (this->_surface == NULL)
		throw 360;
	this->SetInvalidate(false);
}

ID::Label::Label(const ID::Label& b) : ID::Drawable(b)
{
	this->__text = strdup(b.__text);
	this->__color = b.__color;
	this->__police = b.__police;
}

ID::Label::~Label()
{
	delete this->__text;
}

char*	ID::Label::GetText(void) const
{
	return this->__text;
}

void	ID::Label::SetText(char* text)
{
	delete this->__text;
	this->__text = strdup(text);
	this->SetInvalidate(true);
}

void	ID::Label::SetColor(ID::Color fg)
{
	this->__color = fg;
	this->SetInvalidate(true);
}

void	ID::Label::SetColor(uint32_t fg)
{
	this->__color = fg;
	this->SetInvalidate(true);
}

ID::Color	ID::Label::GetColor(void) const
{
	return this->__color;
}

void	ID::Label::SetPolice(ID::Font::Police* police)
{
	this->__police = police;
	this->SetInvalidate(true);
}

ID::Font::Police*	ID::Label::GetPolice(void) const
{
	return this->__police;
}

int	ID::Label::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->GetInvalidate() == true)
	{
		ID::REL_POS_TYPE	relPos;

		if (this->GetSurface() != NULL)
			delete this->GetSurface();
		if (this->__text != NULL)
		//	this->_surface = Font::GetInstance()->TextRender(this->__text,
//									 this->__police,
//									 &(this->__color));
			this->SetSurface(Font::GetInstance()->TextRender(this->__text,
									 this->__police,
									 &(this->__color)));
		if (this->GetSurface() == NULL)
			return -1;
		relPos = this->GetRelPos();
		if (relPos != ID::REL_POS_NONE)
			this->SetPos(relPos);
	}
	if (s != NULL &&
	    this->GetSurface()->BlitSurface(this->_visibleRect, s, x + this->_x, y + this->_y) == -1)
		return -1;
	this->SetInvalidate(false);
	return 0;
}

