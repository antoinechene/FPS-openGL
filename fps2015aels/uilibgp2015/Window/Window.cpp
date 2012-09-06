#include "Window.h"
#include "../Main_Control/Main_Control.h"
#include "../Menu/Menu.h"
#include "../Menubar/Menubar.h"
#include "../Drawable/Drawable.h"
#include <iostream>

ID::Window::Window(uint16_t w, uint16_t h, uint32_t f) : __window(w, h, f, 1),
							 __mainControl(NULL),
							 __isInvalidate(true),
							 __enableBg(true),
							 __bgSurface(NULL),
							 __bgColor(),
							 __drawableFocused(NULL),
							 __drawableEnter(NULL),
							 __fullscreenUpdate(false),
							 __toReorganize(false)
{
	this->__mainControl = new ID::Main_Control(w, h, f, 0, 0, 0, 0);
	if (this->__mainControl == NULL)
		throw 50;
	this->_childrenDrawable.push_back(this->__mainControl);
	this->__mainControl->SetName("MainControl");
	this->__mainControl->SetParent(NULL);
	this->__mainControl->SetWindow(this);
	this->__mainControl->SetInvalidate(true);
	this->SetName("Window");
}

ID::Window::~Window(void)
{
	delete this->__mainControl;
	this->__updateRects.clear();
	this->__developpedMenus.clear();
}

ID::Window::Window(const ID::Window& w) : Control()
{
	this->__window = w.__window;
	this->__mainControl = new ID::Main_Control(*(w.__mainControl));
	this->__isInvalidate = w.__isInvalidate;
	this->__enableBg = w.__enableBg;
	if (w.__bgSurface != NULL)
		this->__bgSurface = new ID::Surface(*(w.__bgSurface));
	else
		this->__bgSurface = NULL;
	this->__bgColor = w.__bgColor;
	this->__drawableFocused = w.__drawableFocused;
	this->__drawableEnter = w.__drawableEnter;
	this->__fullscreenUpdate = w.__fullscreenUpdate;
	this->__toReorganize = w.__toReorganize;
}

ID::Window&	ID::Window::operator=(const ID::Window& w)
{
	this->__window = w.__window;
	this->__mainControl = new ID::Main_Control(*(w.__mainControl));
	if (this->__mainControl == NULL)
		throw 51;
	this->__isInvalidate = w.__isInvalidate;
	this->__enableBg = w.__enableBg;
	if (w.__bgSurface != NULL)
	{
		this->__bgSurface = new ID::Surface(*(w.__bgSurface));
		if (this->__bgSurface == NULL)
			throw 52;
	}
	else
		this->__bgSurface = NULL;
	this->__bgColor = w.__bgColor;
	this->__drawableFocused = w.__drawableFocused;
	this->__drawableEnter = w.__drawableEnter;
	this->__fullscreenUpdate = w.__fullscreenUpdate;
	this->__toReorganize = w.__toReorganize;
	return (*this);
}
/*
void	ID::Window::SetInvalidate(bool i)
{
	this->__isInvalidate = i;
//	if (i == true)
//		this->AddUpdate(0);
}

int	ID::Window::SetBackground(ID::Surface* surface)
{
	this->__bgSurface = surface;
	this->SetInvalidate(true);
	return 0;
}

int	ID::Window::SetBackground(ID::Color* struct_c)
{
	this->__bgColor = *struct_c;
	this->__bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}

int	ID::Window::SetBackground(uint32_t c)
{
	this->__bgColor = c;
	this->__bgSurface = NULL;
	this->SetInvalidate(true);
	return 0;
}
*/
void	ID::Window::SetDrawableFocused(ID::Drawable* f)
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

void	ID::Window::SetDrawableEnter(ID::Drawable* en)
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
/*
void	ID::Window::SetToReorganize(bool toReorganize)
{
	this->__toReorganize = toReorganize;
}

ID::Drawable*	ID::Window::GetMainControl(void) const
{
	return this->__mainControl;
}

bool	ID::Window::GetInvalidate(void) const
{
	return this->__isInvalidate;
}

uint16_t	ID::Window::GetWidth(void) const
{
	return this->__window.w;
}

uint16_t	ID::Window::GetHeight(void) const
{
	return this->__window.h;
}

ID::Drawable*	ID::Window::GetDrawableFocused(void) const
{
	return this->__drawableFocused;
}

ID::Drawable*	ID::Window::GetDrawableEnter(void) const
{
	return this->__drawableEnter;
}

ID::Surface*	ID::Window::GetSurface(void)
{
	return &(this->__window);
}

std::vector<ID::Menu*>*	ID::Window::GetDeveloppedMenus(void)
{
	return &(this->__developpedMenus);
}

bool	ID::Window::GetToReorganize(void) const
{
	return this->__toReorganize;
}
*/
int	ID::Window::RefreshSurface(void)
{
	if (this->GetToReorganize() == true)
		if (this->_Reorganize() == -1)
			return -1;
	if (this->GetInvalidate() == true)
	{
		std::list<Drawable*>::iterator	it;
		std::list<Drawable*>::iterator	end;

		if (this->GetEnableBg() == true)
			this->_RefreshBackground();
		it = this->_childrenDrawable.begin();
		end = this->_childrenDrawable.end();
		while (it != end)
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
/*
void	ID::Window::AddUpdate(ID::Rect* r)
{
	if (r == 0 || (r->x == 0 && r->y == 0 && r->w == 0 && r->h == 0))
	{
		this->__fullscreenUpdate = true;
		this->__updateRects.clear();
	}
	else
	{
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

int	ID::Window::Update(void)
{
	if (this->__fullscreenUpdate == true)
	{
		PRINT_DBG("U(full)\n");
		this->__window.Update(0);
		this->__fullscreenUpdate = false;
	}
	else
	{
		std::vector<ID::Rect>::iterator	it;

		it = this->__updateRects.begin();
		while (it != this->__updateRects.end())
		{
			PRINT_DBG("U(" << (*it).x << "," << (*it).y << "," << (*it).w << "," << (*it).h << ")\n");
			if (this->__window.Update(&(*it)) == -1)
				return -1;
			++it;
		}
		this->__updateRects.clear();
	}
	return 0;
}

int	ID::Window::Update(ID::Rect* r)
{
	return this->__window.Update(r);
}

int	ID::Window::Resize(uint16_t w, uint16_t h)
{
	return this->__window.ResizeVideoMode(w, h);
}
*/
void	ID::Window::AddMenubar(ID::Menubar* m)
{
	this->_childrenDrawable.push_back(m);
	m->SetParent(NULL);
	m->SetWindow(this);
	m->SetInvalidate(true);
	this->MoveChildFront(this->__mainControl);
	if (m->GetOnScreen() == true)
		this->SetToReorganize(true);
}

int	ID::Window::DelMenubar(ID::Menubar* m)
{
	this->SetToReorganize(true);
	return  this->Control::DelChild(m);
}

void	ID::Window::AddChild(Control* c)
{
	this->__mainControl->AddChild(c);
	PRINT_DBG("AddChild Control to MainControl\n")
}

void	ID::Window::AddChild(Drawable* c)
{
	this->__mainControl->AddChild(c);
	PRINT_DBG("AddChild Drawable to MainControl\n");
}

int	ID::Window::_Reorganize(void)
{
	std::list<Drawable*>::iterator	it;
	std::list<Drawable*>::iterator	end;
	ID::REL_POS_TYPE		relPos;
	ID::Rect			rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = this->GetWidth();
	rect.h = this->GetHeight();
	it = this->_childrenDrawable.begin();
	++it; // to avoid to control mainControl
	end = this->_childrenDrawable.end();
	while (it != end)
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
/*
void	ID::Window::_RefreshBackground(void)
{
	if (this->__bgSurface != NULL)
		this->__bgSurface->BlitSurface(NULL, &(this->__window), 0, 0);
	else
		this->__window.FillRect(NULL, &(this->__bgColor));
}
*/
