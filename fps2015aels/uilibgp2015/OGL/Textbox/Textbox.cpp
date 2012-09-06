#include "Textbox.h"
#include "../Keyboard_Manager.h"
#include "../Env.h"
#include "../Draw_Geometry/Draw_Geometry_Line.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

void	__id_textboxFocusEnter(ID::Control* _tb, ID::Event*, void*)
{
	ID::Drawable*	tb;

	tb = (ID::Drawable*)_tb;
}

void	__id_textboxFocusLeave(ID::Control* _tb, ID::Event*, void*)
{
	ID::Drawable*	tb;

	tb = (ID::Drawable*)_tb;
}

void	__id_textboxClickDown(ID::Control* _tb, ID::Event*, void*)
{
	ID::Env::GetInstance()->SetDrawableFocused((ID::Drawable*)_tb);
}

void	__id_textboxKeyDown(ID::Control* _tb, ID::Event* e, void*)
{
	ID::Textbox*	tb;

	tb = (ID::Textbox*)_tb;
	if (e->keyDown.keysym.sym == ID::KEY_RETURN ||
	    e->keyDown.keysym.sym == ID::KEY_KP_ENTER)
	{
		tb->Action(e);
		return ;
	}
	ID::Keyboard_Manager::GetInstance()->Write(tb->__text,
						   e->keyDown.keysym.mod,
						   e->keyDown.keysym.sym,
						   tb->GetMaxLength());
}

ID::Textbox::Textbox(void) : Drawable()
{
}

ID::Textbox::Textbox(uint16_t w, uint16_t h, void* font,
		     Color* fg) : Drawable(w, h),
				 _cbAction(NULL),
				 _cbActionData(NULL),
				 __maxLength(100)
{
	this->__text = new char[this->__maxLength + 1];
	if (this->__text == NULL)
		throw 710;
	this->__text[0] = 0;
	this->__color = *fg;
	this->__font = font;
	this->SetCbClickDown(__id_textboxClickDown, 0);
	this->SetCbKeyDown(__id_textboxKeyDown, 0);
}

ID::Textbox::Textbox(const ID::Textbox& t) : Drawable(t),
					     __maxLength(t.__maxLength),
					     __text(NULL),
					     __color(t.__color),
					     __font(t.__font)
{
	unsigned int	i;

	this->__text = new char[this->__maxLength + 1];
	if (this->__text == NULL)
		throw 711;
	i = 0;
	while (i < this->__maxLength)
	{
		this->__text[i] = t.__text[i];
		++i;
	}
}

ID::Textbox::~Textbox(void)
{
	delete[] this->__text;
}

void	ID::Textbox::SetText(char* text)
{
	unsigned int	i;

	i = 0;
	while (text[i] != 0 && i < this->__maxLength)
	{
		this->__text[i] = text[i];
		++i;
	}
	this->__text[i] = 0;
}

char*	ID::Textbox::GetText(void)
{
	return this->__text;
}

void	ID::Textbox::SetColor(ID::Color fg)
{
	this->__color = fg;
}

void	ID::Textbox::SetColor(uint32_t fg)
{
	this->__color = fg;
}

ID::Color	ID::Textbox::GetColor(void) const
{
	return this->__color;
}

void	ID::Textbox::SetFont(void* font)
{
	this->__font = font;
}

void*	ID::Textbox::GetFont(void) const
{
	return this->__font;
}

int	ID::Textbox::SetMaxLength(unsigned int maxLength)
{
	this->__maxLength = maxLength;
	delete this->__text;
	this->__text = new char[this->__maxLength + 1];
	if (this->__text == NULL)
		return -1;
	this->__text[0] = 0;
	return 0;
}

unsigned int	ID::Textbox::GetMaxLength(void) const
{
	return this->__maxLength;
}

int	ID::Textbox::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->_surface->BlitSurface(x + this->_x, y + this->_y) == -1)
		return -1;
//	if (this->GetInvalidate() == true)
	{
		ID::Font*	font;
		ID::Rect	rect;
		int		i;

		font = Font::GetInstance();
//		if (font->SizeText(this->__police->font, this->__text, &w, NULL) == -1)
//			return -1;
		i = 0;
		// Force width to GLUT_BITMAP_9_BY_15
		while (this->__text[i] != 0 &&
		       strlen(&(this->__text[i])) * 9 > this->GetWidth())
			++i;
		if (i > 0)
			--i;
//		this->_RefreshBackground();
		if (strlen(&(this->__text[i])) > 0)
		{
			font->TextRender(&(this->__text[i]),
					 this->__font,
					 &(this->__color),
					 x + this->_x,
					 glutGet(GLUT_WINDOW_HEIGHT) -
					 (y + this->_y + this->GetSurface()->h - 15 / 2), 0);
		}
/*		if (textSurface != NULL)
		{
			Draw_Geometry_Line*	dgl;
//			Window*			w;
			int			yDest;

			dgl = Draw_Geometry_Line::GetInstance();
			rect.h = textSurface->h;
			if (textSurface->h > this->_surface->h)
			{
				rect.h = this->_surface->h;
				rect.y = (textSurface->h >> 1) - (this->_surface->h >> 1);
				yDest = 0;
			}
			else
			{
				rect.h = textSurface->h;
				rect.y = 0;
				yDest = (this->_surface->h >> 1) - (textSurface->h >> 1);
			}
			if (textSurface->w > this->_surface->w)
			{
				rect.w = this->_surface->w;
				rect.x = textSurface->w - this->_surface->w;
			}
			else
			{
				rect.w = textSurface->w;
				rect.x = 0;
			}
			textSurface->BlitSurface(&rect, this->_surface, 0, yDest);
//			w = this->GetRealWindow();
//			if (w != NULL && w->GetDrawableFocused() == this)
				dgl->Draw(this->_surface, rect.w + 1, 2, rect.w + 1, rect.h - 1, 0);
			delete textSurface;
		}
*/	}
/*	if (s != NULL &&
	    this->_surface->BlitSurface(this->_visibleRect, s, x + this->_x, y + this->_y) == -1)
		return -1;*/
	if (this->_cbUpdate != NULL)
		this->_cbUpdate(this, this->__cbUpdateData);
	return 0;
}

int	ID::Textbox::Action(Event* e)
{
	if (this->_cbAction != NULL)
		this->_cbAction(this, e, this->_cbActionData);
	return 0;
}

void	ID::Textbox::SetCbAction(ID::cbEvent cb, void* data)
{
	this->_cbAction = cb;
	this->_cbActionData = data;
}

ID::cbEvent	ID::Textbox::GetCbAction(void) const
{
	return this->_cbAction;
}

