public:
inline void	SetInvalidate(bool i)
{
	this->__isInvalidate = i;
//	if (i == true)
//		this->AddUpdate(0);
}

inline void	SetEnableBg(bool ebg)
{
	this->__enableBg = ebg;
//	if (i == true)
//		this->AddUpdate(0);
}

inline int	SetBackground(ID::Surface* surface)
{
	this->__bgSurface = surface;
	this->SetInvalidate(true);
	return 0;
}

inline int	SetBackground(ID::Color* struct_c)
{
	this->__bgColor = *struct_c;
	this->__bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

inline int	SetBackground(uint32_t c)
{
	this->__bgColor = c;
	this->__bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}
/*
inline void	SetDrawableFocused(ID::Drawable* f)
{
	ID::Event	e;

	if (this->__drawableFocused == f)
		return ;
	if (this->__drawableFocused != NULL)
	{
		e.type = ID::EVENT_FOCUS_LEAVE;
		e.focusLeave.type = ID::EVENT_FOCUS_LEAVE;
		this->__drawableFocused->FocusLeave(&e);
	}
	this->__drawableFocused = f;
	if (this->__drawableFocused != NULL)
	{
		e.type = ID::EVENT_FOCUS_ENTER;
		e.focusEnter.type = ID::EVENT_FOCUS_ENTER;
		this->__drawableFocused->FocusEnter(&e);
	}
}

inline void	SetDrawableEnter(ID::Drawable* en)
{
	ID::Event	e;

	if (this->__drawableEnter == en)
		return ;
	if (this->__drawableEnter != NULL)
	{
		e.type = ID::EVENT_LEAVE;
		e.leave.type = ID::EVENT_LEAVE;
		this->__drawableEnter->Leave(&e);
	}
	this->__drawableEnter = en;
	if (this->__drawableEnter != NULL)
	{
		e.type = ID::EVENT_ENTER;
		e.focusEnter.type = ID::EVENT_ENTER;
		this->__drawableEnter->Enter(&e);
	}
}
*/
inline void	SetToReorganize(bool toReorganize)
{
	this->__toReorganize = toReorganize;
}

inline Main_Control*	GetMainControl(void) const
{
	return this->__mainControl;
}

inline bool	GetInvalidate(void) const
{
	return this->__isInvalidate;
}

inline bool	GetEnableBg(void) const
{
	return this->__enableBg;
}

inline uint16_t	GetWidth(void) const
{
	return this->__window.w;
}

inline uint16_t	GetHeight(void) const
{
	return this->__window.h;
}

inline ID::Drawable*	GetDrawableFocused(void) const
{
	return this->__drawableFocused;
}

inline ID::Drawable*	GetDrawableEnter(void) const
{
	return this->__drawableEnter;
}

inline ID::Surface*	GetSurface(void)
{
	return &(this->__window);
}

inline std::vector<ID::Menu*>*	GetDeveloppedMenus(void)
{
	return &(this->__developpedMenus);
}

inline bool	GetToReorganize(void) const
{
	return this->__toReorganize;
}
/*
inline int	RefreshSurface(void)
{
	std::list<Drawable*>::iterator	it;

	if (this->GetToReorganize() == true)
		if (this->_Reorganize() == -1)
			return -1;
	if (this->GetInvalidate() == true)
	{
		this->_RefreshBackground();
		it = this->_childrenDrawable.begin();
		while (it != this->_childrenDrawable.end())
		{
			PRINT_DBG("Window RefSurf *it\n")
			if ((*it)->RefreshToSurface(this->GetSurface(), 0, 0) == -1)
				return -1;
			++it;
		}
	}
	this->SetInvalidate(false);
	return 0;
}
*/
inline void	AddUpdate(ID::Rect* r)
{
	if (r == 0 || (r->x == 0 && r->y == 0 && r->w == 0 && r->h == 0))
	{
		this->__fullscreenUpdate = true;
		this->__updateRects.clear();
	}
	else
	{
		if (r->w == 0 || r->h == 0)
			return ;
		if (r->x < 0)
		{
			r->w = r->w + r->x;
			r->x = 0;
		}
		if (r->y < 0)
		{
			r->h = r->h + r->y;
			r->y = 0;
		}
		if (r->w + r->x >= this->GetWidth())
		{
			r->w = this->GetWidth() - r->x;
		}
		if (r->h + r->y >= this->GetHeight())
		{
			r->h = this->GetHeight() - r->y;
		}
		this->__updateRects.push_back(*r);
	}
}

inline int	Update(void)
{
	if (this->__fullscreenUpdate == true)
	{
		std::cout << "U(full)\n";
		this->__updateRects.clear();
		this->__window.Update(0);
		this->__fullscreenUpdate = false;
	}
	else
	{
		std::vector<ID::Rect>::iterator	it;
		std::vector<ID::Rect>::iterator	end;

		it = this->__updateRects.begin();
		end = this->__updateRects.end();
		while (it != end)
		{
//			std::cout << "U(" << (*it).x << "," << (*it).y << "," << (*it).w << "," << (*it).h << ")\n";
			if (this->__window.Update(&(*it)) == -1)
				return -1;
			++it;
		}
		this->__updateRects.clear();
	}
	return 0;
}

inline int	Update(ID::Rect* r)
{
	return this->__window.Update(r);
}

inline int	Resize(uint16_t w, uint16_t h)
{
	return this->__window.ResizeVideoMode(w, h);
}
/*
inline void	AddMenubar(ID::Menubar* m)
{
	this->_childrenDrawable.push_back(m);
	m->SetParent(NULL);
	m->SetWindow(this);
	m->SetInvalidate(true);
	this->MoveChildFront(this->__mainControl);
	if (m->GetOnScreen() == true)
		this->SetToReorganize(true);
}

inline int	DelMenubar(ID::Menubar* m)
{
	this->SetToReorganize(true);
	return this->Control::DelChild(m);
}

inline void	AddChild(Control* c)
{
	this->__mainControl->AddChild(c);
	PRINT_DBG("AddChild Control to MainControl\n")
}

inline void	AddChild(Drawable* c)
{
	this->__mainControl->AddChild(c);
	PRINT_DBG("AddChild Drawable to MainControl\n");
}
*/
protected:
/*
inline int	_Reorganize(void)
{
	std::list<Drawable*>::iterator	it;
	REL_POS_TYPE		relPos;
	Rect			rect;

	it = this->_childrenDrawable.begin();
	++it; // to avoid to control mainControl
	rect.x = 0;
	rect.y = 0;
	rect.w = this->GetWidth();
	rect.h = this->GetHeight();
	while (it != this->_childrenDrawable.end())
	{
		if ((*it)->GetOnScreen() == true)
		{
			relPos = (*it)->GetRelPos();
			if (relPos & ID::REL_POS_TOP)
			{
				rect.y = rect.y + (*it)->GetHeight();
				rect.h = rect.h - (*it)->GetHeight();
			}
			else if (relPos & ID::REL_POS_BOT)
				rect.h = rect.h - (*it)->GetHeight();
			else if (relPos & ID::REL_POS_LEFT)
			{
				rect.x = rect.x + (*it)->GetWidth();
				rect.w = rect.w - (*it)->GetWidth();
			}
			else if (relPos & ID::REL_POS_RIGHT)
				rect.w = rect.w - (*it)->GetWidth();
		}
		++it;
	}
	this->__mainControl->SetPos(rect.x, rect.y);
	if (this->__mainControl->Resize(rect.w, rect.h) == -1)
		return -1;
	this->SetToReorganize(false);
	return 0;
}
*/
inline void	_RefreshBackground(void)
{
	if (this->__bgSurface != NULL)
		this->__bgSurface->BlitSurface(NULL, &(this->__window), 0, 0);
	else
		this->__window.FillRect(NULL, &(this->__bgColor));
}

