#include "Drawable.h"
#include "../Window/Window.h"
#include <iostream>

ID::Drawable::Drawable(void) : _surface(NULL),
			       _bgSurface(NULL),
			       _bgColor(),
			       _onScreen(true),
			       _isEnable(true),
			       _isInvalidate(true),
			       _abstractParent(false),
			       _enableBg(true),
			       _relPos(ID::REL_POS_NONE),
			       _x(0), _y(0),
			       _visibleRect(NULL),
			       _bgRect(NULL),
			       _offset_x(0),
			       _offset_y(0),
			       _borderColor(),
			       _border(),
			       _w(0),
			       _h(0)
{
	this->_lastClickDown.tv_sec = 0;
	this->_lastClickDown.tv_usec = 0;
	this->_lastClick.tv_sec = 0;
	this->_lastClick.tv_usec = 0;
}

ID::Drawable::Drawable(uint16_t w, uint16_t h, uint32_t f,
		       uint32_t rmask, uint32_t gmask,
		       uint32_t bmask, uint32_t amask) : _surface(NULL),
							 _bgSurface(NULL),
							 _bgColor(),
							 _onScreen(true),
							 _isEnable(true),
							 _isInvalidate(true),
							 _abstractParent(false),
							 _enableBg(true),
							 _relPos(ID::REL_POS_NONE),
							 _x(0), _y(0),
							 _visibleRect(NULL),
							 _bgRect(NULL),
							 _offset_x(0),
							 _offset_y(0),
							 _borderColor(),
							 _border(),
							 _w(w),
							 _h(h)
{
	this->_surface =  new ID::Surface(w, h, f,
					  rmask, gmask,
					  bmask, amask);
	if (this->_surface == NULL)
		throw 60;
}

ID::Drawable::~Drawable(void)
{
	ID::Window*	w;

	w = this->GetRealWindow();
	if (w != NULL)
	{
		if (w->GetDrawableFocused() == this)
			w->SetDrawableFocused(NULL);
		if (w->GetDrawableEnter() == this)
			w->SetDrawableEnter(NULL);
	}
	delete this->_surface;
	delete this->_visibleRect;
}

ID::Drawable::Drawable(const ID::Drawable& c) : Control(),
						_surface(new ID::Surface(*(c._surface))),
						_bgSurface(c._bgSurface),
						_bgColor(c._bgColor),
						_onScreen(c._onScreen),
						_isEnable(c._isEnable),
						_isInvalidate(c._isInvalidate),
						_abstractParent(c._abstractParent),
						_enableBg(c._enableBg),
						_relPos(c._relPos),
						_x(c._x), _y(c._y),
						_offset_x(c._offset_x),
						_offset_y(c._offset_y),
						_borderColor(c._borderColor),
						_border(c._border),
						_w(c._w),
						_h(c._h)
{
	if (c._visibleRect != NULL)
		this->_visibleRect = new ID::Rect(*(c._visibleRect));
	if (c._bgRect != NULL)
		this->_bgRect = new ID::Rect(*(c._bgRect));
}

ID::Drawable&	ID::Drawable::operator=(const ID::Drawable& c)
{
	this->_surface = new ID::Surface(*(c._surface));
	this->_bgSurface = c._bgSurface;
	this->_bgColor = c._bgColor;
	this->_onScreen = c._onScreen;
	this->_isEnable = c._isEnable;
	this->_isInvalidate = c._isInvalidate;
	this->_abstractParent = c._abstractParent;
	this->_enableBg = c._enableBg;
	this->_relPos = c._relPos;
	this->_x = c._x;
	this->_y = c._y;
	if (c._visibleRect != NULL)
		this->_visibleRect = new ID::Rect(*(c._visibleRect));
	if (c._bgRect != NULL)
		this->_bgRect = new ID::Rect(*(c._bgRect));
	this->_offset_x = c._offset_x;
	this->_offset_y = c._offset_y;
	this->_borderColor = c._borderColor;
	this->_border = c._border;
	this->_w = c._w;
	this->_h = c._h;
	return *this;
}
/*
void		ID::Drawable::SetOnScreen(bool visible)
{
	ID::Event	event;

	this->_onScreen = visible;
	event.type = EVENT_SCREEN_CHANGE;
	event.screenChange.type = EVENT_SCREEN_CHANGE;
	event.screenChange.isOnScreen = visible;
	this->ScreenChange(&event);
	if (this->GetParent() != NULL)
		this->GetParent()->SetInvalidate(true);
}

void		ID::Drawable::SetEnable(bool enable)
{
	ID::Event	event;

	this->_isEnable = enable;
	event.type = EVENT_ENABLE_CHANGE;
	event.enableChange.type = EVENT_ENABLE_CHANGE;
	event.enableChange.isEnable = enable;
	this->EnableChange(&event);
	if (this->GetParent() != NULL)
		this->GetParent()->SetInvalidate(true);
}

void		ID::Drawable::SetInvalidate(bool invalidate)
{
	this->_SetInvalidate(invalidate);
	if (invalidate == true)
		this->_AddUpdateRect();
}

void		ID::Drawable::_SetInvalidate(bool invalidate)
{
	if (invalidate == true)
	{
		if (this->_parent != NULL &&
		    this->_parent->GetInvalidate() == false)
			this->_parent->_SetInvalidate(true);
	}
	this->_isInvalidate = invalidate;
}

void		ID::Drawable::SetSurface(ID::Surface* new_surface)
{
	this->_surface = new_surface;
	this->SetInvalidate(true);
}

void		ID::Drawable::SetPos(int16_t new_x, int16_t new_y)
{
	this->SetInvalidate(true);
	this->_relPos = ID::REL_POS_NONE;
	this->_x = new_x;
	this->_y = new_y;
	this->_RefreshOffset();
	this->SetInvalidate(true);
}

void		ID::Drawable::SetPos(ID::REL_POS_TYPE relPos)
{
	this->SetInvalidate(true);
	this->_relPos = relPos;
	this->_CalculRelativePosition(&(this->_x), &(this->_y));
	this->_RefreshOffset();
}

int		ID::Drawable::SetBackground(ID::Surface* surface)
{
	this->_bgSurface = surface;
	this->SetInvalidate(true);
	return 0;
}

int		ID::Drawable::SetBackground(ID::Color* struct_c)
{
	this->_bgColor = *struct_c;
	this->_bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

int		ID::Drawable::SetBackground(uint32_t c)
{
	this->_bgColor = c;
	this->_bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

void		ID::Drawable::SetVisibleRect(Rect* rect)
{
	if (this->_visibleRect != NULL)
		delete this->_visibleRect;
	this->_visibleRect = new ID::Rect(*rect);
}

void		ID::Drawable::SetBgRect(Rect* rect)
{
	if (this->_bgRect != NULL)
		delete this->_bgRect;
	this->_bgRect = new ID::Rect(*rect);
}

int		ID::Drawable::SetBorderColor(ID::Color* struct_c)
{
	this->_borderColor = *struct_c;
	this->SetInvalidate(true);
	return 0;
}

int		ID::Drawable::SetBorderColor(uint32_t c)
{
	this->_borderColor = c;
	this->SetInvalidate(true);
	return 0;
}

void		ID::Drawable::SetBorder(Border* b)
{
	this->_border = *b;
}

void		ID::Drawable::SetBorder(uint16_t all)
{
	this->_border.top = all;
	this->_border.bot = all;
	this->_border.left = all;
	this->_border.right = all;
}

void		ID::Drawable::SetBorder(uint16_t top, uint16_t bot,
					uint16_t left, uint16_t right)
{
	this->_border.top = top;
	this->_border.bot = bot;
	this->_border.left = left;
	this->_border.right = right;
}

bool		ID::Drawable::GetOnScreen(void) const
{
	return this->_onScreen;
}

bool		ID::Drawable::GetEnable(void) const
{
	return this->_isEnable;
}

bool		ID::Drawable::GetInvalidate(void) const
{
	return this->_isInvalidate;
}

ID::Surface*	ID::Drawable::GetSurface(void) const
{
	return this->_surface;
}

void	ID::Drawable::GetPos(int16_t* x, int16_t* y) const
{
	if (x != NULL)
		*x = this->_x;
	if (y != NULL)
		*y = this->_y;
}

ID::REL_POS_TYPE	ID::Drawable::GetRelPos(void) const
{
	return this->_relPos;
}

void	ID::Drawable::GetOffset(int* offset_x, int* offset_y) const
{
	if (offset_x != NULL)
		*offset_x = this->_offset_x;
	if (offset_y != NULL)
		*offset_y = this->_offset_y;
}

ID::Color		ID::Drawable::GetBorderColor(void) const
{
	return this->_borderColor;
}

ID::Border		ID::Drawable::GetBorder(void) const
{
	return this->_border;
}

void		ID::Drawable::GetBorder(uint16_t* top, uint16_t* bot,
					uint16_t* left, uint16_t* right)
{
	if (top != NULL)
		*top = this->_border.top;
	if (bot != NULL)
		*bot = this->_border.bot;
	if (left != NULL)
		*left = this->_border.left;
	if (right != NULL)
		*right = this->_border.right;
}


uint16_t	ID::Drawable::GetWidth(void) const
{
	return (this->_surface != 0) ? this->_surface->w : 0;
}

uint16_t	ID::Drawable::GetHeight(void) const
{
	return (this->_surface != 0) ? this->_surface->h : 0;
}

ID::Rect*	ID::Drawable::GetVisibleRect(void) const
{
	return this->_visibleRect;
}

ID::Rect*	ID::Drawable::GetBgRect(void) const
{
	return this->_bgRect;
}

ID::Window*	ID::Drawable::GetRealWindow(void)
{
	ID::Drawable*	draw;

	draw = this;
	while (draw->GetParent() != NULL)
		draw = draw->GetParent();
	return draw->GetWindow();
}

int	ID::Drawable::BlitSurface(ID::Rect* rect, ID::Surface* target, int x, int y)
{
	return this->_surface->BlitSurface(rect, target, x, y);
}

int		ID::Drawable::RefreshToSurface(ID::Surface* s, int x, int y)
{
	std::list<Drawable*>::iterator	it;
	int				i;

	if (this->GetOnScreen() == false || this->_surface == NULL)
		return 0;
	if (this->GetInvalidate() == true)
	{
		PRINT_DBG("Refreshing")
		if (this->GetName() != NULL)
			PRINT_DBG(" " << this->GetName() << "\n")
		this->_RefreshBackground();
		it = this->_childrenDrawable.begin();
		i = this->_childrenDrawable.size();
		while (i > 0)
		{
			if ((*it)->RefreshToSurface(this->GetSurface(), 0, 0) == -1)
				return -1;
			--i;
			++it;
		}
	}
	PRINT_DBG("Draw RefToSur" << x + this->_x << "," << y + this->_y << "\n")
	if (this->GetName() != NULL)
		PRINT_DBG(" " << this->GetName() << "\n")
	if (this->_surface->BlitSurface(this->_visibleRect,
					s,
					x + this->_x,
					y + this->_y) == -1)
		return -1;
	this->SetInvalidate(false);
	return 0;
}


int	ID::Drawable::Resize(uint16_t w, uint16_t h, uint32_t f,
		       	     uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	if (this->_surface == NULL)
	{
		this->_surface = new ID::Surface(w, h, f,
						 r, g,
						 b, a);
		if (this->_surface == 0)
			return -1;
	}
	else if (this->_surface->Resize(w, h, f, r, g, b, a) == -1)
		return -1;
	return 0;
}


void	ID::Drawable::_RefreshBackground(void)
{
	ID::Rect	bg;

	if (this->_surface == NULL)
		return ;
	if (this->_bgSurface != NULL)
	{
		this->_bgSurface->BlitSurface(this->_bgRect, this->_surface, this->_border.top, this->_border.left);
		return ;
	}
	else
		this->_surface->FillRect(NULL, &(this->_bgColor));
	if (this->_border.top != 0)
	{
		bg.x = 0;
		bg.y = 0;
		bg.w = this->GetWidth();
		bg.h = this->_border.top;
		this->_surface->FillRect(&bg, &(this->_borderColor));
	}
	if (this->_border.bot != 0)
	{
		bg.x = 0;
		bg.y = this->GetHeight() - this->_border.bot;
		bg.w = this->GetWidth();
		bg.h = this->_border.bot;
		this->_surface->FillRect(&bg, &(this->_borderColor));
	}
	if (this->_border.left != 0)
	{
		bg.x = 0;
		bg.y = 0;
		bg.w = this->_border.left;
		bg.h = this->GetHeight();
		this->_surface->FillRect(&bg, &(this->_borderColor));
	}
	if (this->_border.right != 0)
	{
		bg.x = this->GetWidth() - this->_border.right;
		bg.y = 0;
		bg.w = this->_border.right;
		bg.h = this->GetHeight();
		this->_surface->FillRect(&bg, &(this->_borderColor));
	}
}

int	ID::Drawable::_BlitToParent(void)
{
	if (this->_parent != 0 &&
	    this->_surface->BlitSurface(this->_visibleRect,
					this->_parent->_surface,
					this->_x, this->_y) == 0)
		return 0;
//	if (this->_window != 0 &&
//	    this->_surface->BlitSurface(this->_visibleRect,
//					this->_window->GetSurface(),
//					x, y) == 0)
//		return 0;
	return -1;
}

void	ID::Drawable::_AddUpdateRect()
{
	ID::Drawable*	draw;

	ID::Rect rect(this->_offset_x + this->_x,
		      this->_offset_y + this->_y,
		      this->GetWidth(), this->GetHeight());
	draw = this;
	while (draw != NULL)
	{
		if (draw->_window != NULL)
			draw->_window->AddUpdate(&rect);
		draw = draw->_parent;
	}
}

void	ID::Drawable::_RefreshOffset()
{
	ID::Drawable*			dad;
	std::list<Drawable*>::iterator	it;
	int				i;

	dad = this->_parent;
	this->_offset_x = 0;
	this->_offset_y = 0;
	while (dad != 0)
	{
		this->_offset_x += dad->_x;
		this->_offset_y += dad->_y;
		dad = dad->_parent;
	}
	it = this->_childrenDrawable.begin();
	i = this->_childrenDrawable.size();
	while (i > 0)
	{
		(*it)->_RefreshOffset();
		--i;
		++it;
	}
}

void	ID::Drawable::_CalculRelativePosition(int16_t* x, int16_t* y)
{
	int	parentWidth;
	int	parentHeight;

	if (this->_relPos & ID::REL_POS_NONE)
	{
		*x = this->_x;
		*y = this->_y;
		return ;
	}
	if (this->_parent != NULL)
	{
		parentWidth = this->_parent->GetWidth();
		parentHeight = this->_parent->GetHeight();
	}
	else if (this->_window != NULL)
	{
		parentWidth = this->_window->GetWidth();
		parentHeight = this->_window->GetHeight();
	}
	*x = 0;
	*y = 0;
	if (!(this->_relPos & (ID::REL_POS_BOT | ID::REL_POS_TOP)))
		*y = (parentHeight - this->GetHeight()) >> 1;
	else
	{
		if (this->_relPos & ID::REL_POS_BOT)
			*y = parentHeight  - this->GetHeight();
		if (this->_relPos & ID::REL_POS_TOP && *y != 0)
			*y = *y >> 1;
	}
	if (!(this->_relPos & (ID::REL_POS_LEFT | ID::REL_POS_RIGHT)))
		*x = (parentWidth - this->GetWidth()) >> 1;
	else
	{
		if (this->_relPos & ID::REL_POS_RIGHT)
			*x = parentWidth - this->GetWidth();
		if (this->_relPos & ID::REL_POS_LEFT && *x != 0)
			*x = *x >> 1;
	}
}
*/
