#include "Label.h"
#include <iostream>
#include <string.h>
#include "../Wrapper/Wrapper_Interface_OGL.h"

ID::Label::Label(void* font, char* text,
		 ID::Color* fg) : Drawable(9 * strlen(text), 15)
{
	this->__text = strdup(text);
	this->__color = *fg;
	this->__font = font;
}

ID::Label::Label(const ID::Label& b) : ID::Drawable(b)
{
	this->__text = strdup(b.__text);
	this->__color = b.__color;
	this->__font = b.__font;
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
}

void	ID::Label::SetColor(ID::Color fg)
{
	this->__color = fg;
}

void	ID::Label::SetColor(uint32_t fg)
{
	this->__color = fg;
}

ID::Color	ID::Label::GetColor(void) const
{
	return this->__color;
}

void	ID::Label::SetFont(void* font)
{
	this->__font = font;
}

void*	ID::Label::GetFont(void) const
{
	return this->__font;
}

int	ID::Label::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
//	if (this->GetInvalidate() == true)
	{
		ID::REL_POS_TYPE	relPos;

		Font::GetInstance()->TextRender(this->__text,
						this->__font,
						&(this->__color),
						x + this->_x,
						glutGet(GLUT_WINDOW_HEIGHT) -
						(y + this->_y + 15),
						0);
		relPos = this->GetRelPos();
		if (relPos != ID::REL_POS_NONE)
			this->SetPos(relPos);
	}
//	if (s != NULL &&
//	    this->GetSurface()->BlitSurface(this->_visibleRect, s, x + this->_x, y + this->_y) == -1)
//		return -1;
	return 0;
}

