#ifndef	__DRAWABLE_INLINE_HPP__
#define	__DRAWABLE_INLINE_HPP__

inline void		SetOnScreen(bool visible)
{
	ID::Event	event;

	this->_onScreen = visible;
	event.type = EVENT_SCREEN_CHANGE;
	event.screenChange.type = EVENT_SCREEN_CHANGE;
	event.screenChange.isOnScreen = visible;
	this->ScreenChange(&event);
	this->SetInvalidate(true);
//	if (this->GetParent() != NULL)
//		this->GetParent()->SetInvalidate(true);
}

inline void		SetEnable(bool enable)
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

inline void		SetInvalidate(bool invalidate)
{
	this->_SetInvalidate(invalidate);
	if (invalidate == true)
		this->_AddUpdateRect();
}

inline void		SetAbstractParent(bool ap)
{
	this->_abstractParent = ap;
	this->SetInvalidate(true);
}

inline void		SetEnableBg(bool ebg)
{
	this->_enableBg = ebg;
	this->SetInvalidate(true);
}

inline void		SetSurface(ID::Surface* new_surface)
{
	this->_surface = new_surface;
	this->_w = this->_surface->w;
	this->_h = this->_surface->h;
	this->SetInvalidate(true);
}

inline void		SetPos(int16_t new_x, int16_t new_y)
{
	this->SetInvalidate(true);
	this->_relPos = ID::REL_POS_NONE;
	this->_x = new_x;
	this->_y = new_y;
	this->_RefreshOffset();
	this->SetInvalidate(true);
}

inline void		SetPos(ID::REL_POS_TYPE relPos)
{
	this->SetInvalidate(true);
	this->_relPos = relPos;
	this->_CalculRelativePosition(&(this->_x), &(this->_y));
	this->_RefreshOffset();
	this->SetInvalidate(true);
}

inline int		SetBackground(ID::Surface* surface)
{
	this->_bgSurface = surface;
	this->SetInvalidate(true);
	return 0;
}

inline int		SetBackground(ID::Color* struct_c)
{
	this->_bgColor = *struct_c;
	this->_bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

inline int		SetBackground(uint32_t c)
{
	this->_bgColor = c;
	this->_bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

inline void		SetVisibleRect(Rect* rect)
{
	if (this->_visibleRect != NULL)
		delete this->_visibleRect;
	this->_visibleRect = new ID::Rect(*rect);
	this->SetInvalidate(true);
}

inline void		SetBgRect(Rect* rect)
{
	if (this->_bgRect != NULL)
		delete this->_bgRect;
	this->_bgRect = new ID::Rect(*rect);
	this->SetInvalidate(true);
}

inline int		SetBorderColor(ID::Color* struct_c)
{
	this->_borderColor = *struct_c;
	this->SetInvalidate(true);
	return 0;
}

inline int		SetBorderColor(uint32_t c)
{
	this->_borderColor = c;
	this->SetInvalidate(true);
	return 0;
}

inline void		SetBorder(Border* b)
{
	this->_border = *b;
	this->SetInvalidate(true);
}

inline void		SetBorder(uint16_t all)
{
	this->_border.top = all;
	this->_border.bot = all;
	this->_border.left = all;
	this->_border.right = all;
	this->SetInvalidate(true);
}

inline void		SetBorder(uint16_t top, uint16_t bot,
				  uint16_t left, uint16_t right)
{
	this->_border.top = top;
	this->_border.bot = bot;
	this->_border.left = left;
	this->_border.right = right;
	this->SetInvalidate(true);
}

inline bool		GetOnScreen(void) const
{
	return this->_onScreen;
}

inline bool		GetEnable(void) const
{
	return this->_isEnable;
}

inline bool		GetInvalidate(void) const
{
	return this->_isInvalidate;

}

inline bool		GetAbstractParent(void) const
{
	return this->_abstractParent;
}

inline bool		GetEnableBg(void) const
{
	return this->_enableBg;
}

inline ID::Surface*	GetSurface(void) const
{
	return this->_surface;
}

inline void	GetPos(int16_t* x, int16_t* y) const
{
	if (x != NULL)
		*x = this->_x;
	if (y != NULL)
		*y = this->_y;
}

inline ID::REL_POS_TYPE	GetRelPos(void) const
{
	return this->_relPos;
}

inline void	GetOffset(int* offset_x, int* offset_y) const
{
	if (offset_x != NULL)
		*offset_x = this->_offset_x;
	if (offset_y != NULL)
		*offset_y = this->_offset_y;
}

inline ID::Color	GetBorderColor(void) const
{
	return this->_borderColor;
}

inline ID::Border	GetBorder(void) const
{
	return this->_border;
}

inline void		GetBorder(uint16_t* top, uint16_t* bot,
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

inline uint16_t		GetWidth(void) const
{
//	return this->_w;
	return (this->_surface != 0) ? this->_surface->w : this->_w;
}

inline uint16_t		GetHeight(void) const
{
//	return this->_h;
	return (this->_surface != 0) ? this->_surface->h : this->_h;
}

inline ID::Rect*	GetVisibleRect(void) const
{
	return this->_visibleRect;
}

inline ID::Rect*	GetBgRect(void) const
{
	return this->_bgRect;
}

inline ID::Window*	GetRealWindow(void)
{
	ID::Drawable*	draw;

	draw = this;
	while (draw->GetParent() != NULL)
		draw = draw->GetParent();
	return draw->GetWindow();
}

inline int	BlitSurface(ID::Rect* rect, ID::Surface* target, int x, int y)
{
	return this->_surface->BlitSurface(rect, target, x, y);
}

inline virtual int	RefreshToSurface(ID::Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false ||
	    (this->_surface == NULL && this->GetAbstractParent() == false))
		return 0;
	std::list<Drawable*>::iterator	it;
	std::list<Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	if (this->GetAbstractParent() == true)
	{
		while (it != end)
		{
			if ((*it)->RefreshToSurface(s, x + this->_x, y + this->_y) == -1)
				return -1;
			++it;
		}
	}
	else
	{
		if (this->GetInvalidate() == true)
		{
			if (this->GetEnableBg() == true)
				this->_RefreshBackground();
			while (it != end)
			{
				if ((*it)->RefreshToSurface(this->GetSurface(), 0, 0) == -1)
					return -1;
				++it;
			}
		}
		if (this->_surface->BlitSurface(this->_visibleRect,
						s,
						x + this->_x,
						y + this->_y) == -1)
			return -1;
	}
	if (this->_cbUpdate != NULL)
		this->_cbUpdate(this, this->__cbUpdateData);
	this->SetInvalidate(false);
	return 0;
}

inline virtual int	Resize(uint16_t w, uint16_t h,
			       uint32_t f = SDL_SWSURFACE | SDL_SRCALPHA,
			       uint32_t r = 0, uint32_t g = 0,
			       uint32_t b = 0, uint32_t a = 0)
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
	this->_w = w;
	this->_h = h;
	return 0;
}

protected:
inline void	_RefreshBackground(void)
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

inline virtual void	_SetInvalidate(bool invalidate)
{
	if (invalidate == true)
	{
		if (this->_parent != NULL &&
		    this->_parent->GetInvalidate() == false)
			this->_parent->_SetInvalidate(true);
	}
	this->_isInvalidate = invalidate;
}

inline void	_AddUpdateRect()
{
	ID::Window*	w;

	w = this->GetRealWindow();
	if (w != NULL)
	{
		ID::Rect rect(this->_offset_x + this->_x,
			      this->_offset_y + this->_y,
			      this->GetWidth(), this->GetHeight());
		w->AddUpdate(&rect);
	}
}

inline void	_RefreshOffset()
{
	ID::Drawable*			dad;
	std::list<Drawable*>::iterator	it;
	std::list<Drawable*>::iterator	end;

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
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		(*it)->_RefreshOffset();
		++it;
	}
}

inline void	_CalculRelativePosition(int16_t* x, int16_t* y)
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

void	_PushClickEvent(Event* e)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1 ||
	    Wrapper_Event::GetInstance()->CheckIntervalClick(&(this->_lastClickDown), &tv) == false)
		return ;
	Event	clickEvent;

	clickEvent.type = EVENT_CLICK;
	clickEvent.click.button = e->clickUp.button;
	clickEvent.click.x = e->clickUp.x;
	clickEvent.click.y = e->clickUp.y;
	Wrapper_Event::GetInstance()->PushEvent(&clickEvent);
}

void	_PushDblClickEvent(Event* e)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1 ||
	    Wrapper_Event::GetInstance()->CheckIntervalClick(&(this->_lastClick), &tv) == false)
		return ;
	Event	clickEvent;

	clickEvent.type = EVENT_DOUBLE_CLICK;
	clickEvent.doubleClick.button = e->click.button;
	clickEvent.doubleClick.x = e->click.x;
	clickEvent.doubleClick.y = e->click.y;
	Wrapper_Event::GetInstance()->PushEvent(&clickEvent);
}

#endif
