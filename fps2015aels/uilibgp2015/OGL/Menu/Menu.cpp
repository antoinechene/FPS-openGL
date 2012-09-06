#include "Menu.h"
#include "../Common.h"
#include "../Drawable/Drawable.h"
#include <iostream>

void	__id_menuClickDown(ID::Control* _m, ID::Event*, void*)
{
	ID::Menu*				m;
/*	std::list<ID::Menu*>			childrenMenu;
	std::vector<ID::Menu*>*			developpedMenus;
	std::vector<ID::Menu*>::iterator	it;
	std::vector<ID::Menu*>::iterator	end;
*/
	m = (ID::Menu*)_m;
/*	PRINT_DBG("ClickDown ")
	if (m->GetName() != NULL)
		PRINT_DBG(m->GetName())
	PRINT_DBG("\n")

	win = m->GetRealWindow();
	developpedMenus = win->GetDeveloppedMenus();
	it = developpedMenus->begin();
	end = developpedMenus->end();
	while (it != end)
	{
		PRINT_DBG("-----developpedMenus ")
		if ((*it)->GetName() != NULL)
			PRINT_DBG((*it)->GetName())
		PRINT_DBG("\n")
		if ((*it)->GetParent() == m->GetParent())
		{
			if (*it != m)
			{
				(*it)->HideAll();
				developpedMenus->erase(it, developpedMenus->end());
			}
			break ;
		}
		++it;
	}
	developpedMenus->push_back(m);
	childrenMenu = m->GetChildrenMenu();
	if (m->Action() == 1)
	{
		PRINT_DBG("front() Hideall()");
		developpedMenus->front()->HideAll();
		developpedMenus->clear();
	}
	else if (childrenMenu.empty() == false)
	{
		if (childrenMenu.front()->GetOnScreen() == true)
			m->HideAll();
		else
			m->ShowAll();
	}
*/
}

ID::Menu::Menu(uint16_t w, uint16_t h, uint32_t f,
	       uint32_t r, uint32_t g,
	       uint32_t b, uint32_t a,
	       const char* font_path, int font_size,
	       char* text, ID::Color* color) : Drawable(w, h, f, r, g, b, a),
					       _cbAction(NULL),
					       __menuType(ID::MENU_VERTICAL),
					       __childrenSidePosition(ID::SIDE_POSITION_BOT),
					       __childrenAlignment(ID::ALIGNMENT_TOP),
					       __mustBeOnScreen(true),
					       __toReorganize(true),
					       __cbActionData(NULL)
{
	this->_label = new ID::Label(font_path, font_size, text, color);
	if (this->_label == NULL)
		throw 150;
	this->_label->SetParent(this);
	this->_label->SetPos(ID::REL_POS_CENTER);
	this->SetCbClickDown(__id_menuClickDown, 0);
//	this->SetCbFocusEnter(__id_menuFocusEnter, 0);
//	this->SetCbFocusLeave(__id_menuFocusLeave, 0);
}

ID::Menu::~Menu()
{
	delete this->_label;
}

void	ID::Menu::SetMenuType(ID::MENU_TYPE menu_type)
{
	this->__menuType = menu_type;
	this->_SetToReorganize(true);
}

void	ID::Menu::SetChildrenSidePosition(ID::SIDE_POSITION_TYPE side_position_type)
{
	this->__childrenSidePosition = side_position_type;
	this->_SetToReorganize(true);
}

void	ID::Menu::SetChildrenAlignment(ID::ALIGNMENT_TYPE alignment_type)
{
	this->__childrenAlignment = alignment_type;
	this->_SetToReorganize(true);
}

void	ID::Menu::SetMustBeOnScreen(bool mustBeOnScreen)
{
	this->__mustBeOnScreen = mustBeOnScreen;
	this->_SetToReorganize(true);
}

void	ID::Menu::SetLabel(ID::Label* lb)
{
	this->_label = lb;
}

ID::MENU_TYPE		ID::Menu::GetMenuType(void) const
{
	return this->__menuType;
}

std::list<ID::Menu*>	ID::Menu::GetChildrenMenu(void) const
{
	return this->__childrenMenu;
}

ID::SIDE_POSITION_TYPE	ID::Menu::GetChildrenSidePosition(void) const
{
	return this->__childrenSidePosition;
}

ID::ALIGNMENT_TYPE	ID::Menu::GetChildrenAlignment(void) const
{
	return this->__childrenAlignment;
}

bool			ID::Menu::GetMustBeOnScreen(void) const
{
	return this->__mustBeOnScreen;
}


ID::Label*		ID::Menu::GetLabel(void) const
{
	return this->_label;
}

void			ID::Menu::ShowAll()
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;

	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		PRINT_DBG("Menu is showing\n")
		(*it)->SetOnScreen(true);
		(*it)->HideAll();
		++it;
	}
}

void			ID::Menu::HideAll()
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;

	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		PRINT_DBG("Menu is hiding\n")
		(*it)->HideAll();
		(*it)->SetOnScreen(false);
		++it;
	}
}

int		ID::Menu::Action(void)
{
	if (this->_cbAction!= NULL)
	{
		this->_cbAction(this, NULL, this->__cbActionData);
		return 1;
	}
	return 0;
}

void		ID::Menu::SetCbAction(ID::cbEvent cb, void* data)
{
	this->_cbAction = cb;
	this->__cbActionData = data;
}

ID::cbEvent	ID::Menu::GetCbAction(void)
{
	return this->_cbAction;
}

void	ID::Menu::AddChild(Menu* menu)
{
	this->__childrenMenu.push_back(menu);
	menu->SetParent(this);
	this->_SetToReorganize(true);
}

int	ID::Menu::DelChild(Menu* menu)
{
	std::list<ID::Menu*>::iterator	it;
	std::list<ID::Menu*>::iterator	end;

	this->_SetToReorganize(true);
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		if (*it == menu)
		{
			this->__childrenMenu.erase(it);
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::Menu::RefreshToSurface(ID::Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->_GetToReorganize() == true)
		this->_Reorganize();
//	if (this->GetInvalidate() == true)
	{
		PRINT_DBG("Menu RefSur Invalid\n");
		this->_RefreshBackground();
		if (this->_label->RefreshToSurface(this->GetSurface(), 0, 0) == -1)
			return -1;
	}
	if (s != NULL &&
	    this->GetSurface()->BlitSurface(this->_visibleRect, s,
					    x + this->_x,
					    y + this->_y) == -1)
		return -1;
	if (this->_cbUpdate != NULL)
		this->_cbUpdate(this, this->__cbUpdateData);
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;

	PRINT_DBG("Menu RefSur X=" << this->_x << "	Y=" << this->_y << "\n");
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		PRINT_DBG("Menu RefSur while\n");
		if ((*it)->RefreshToSurface(s, this->_x, this->_y) == -1)
		{
			PRINT_DBG("Menu RefSur while RefSurf() error\n");
			return -1;
		}
		++it;
	}
	return 0;
}

void	ID::Menu::_SetToReorganize(bool toReorganize)
{
	this->__toReorganize = toReorganize;
}

bool	ID::Menu::_GetToReorganize(void)
{
	return this->__toReorganize;
}

void	ID::Menu::_Reorganize(void)
{
	if (this->__menuType == ID::MENU_VERTICAL)
		this->__ReorganizeVertical();
	else
		this->__ReorganizeHorizontal();
	this->_SetToReorganize(false);
}

void	ID::Menu::__ReorganizeVertical(void)
{
	std::list<ID::Menu*>::iterator	it;
	std::list<ID::Menu*>::iterator	end;
	int				x;
	int				y;

	this->__CalculChildrenSidePosition(&x, &y);
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
//		this->__CalculChildrenAlignment(&x, &y, minX, minY);
		PRINT_DBG("Menu __ReorganizeV X=" << x << "	Y=" << y << "\n")
		(*it)->SetPos(x, y);
		y = y + (*it)->GetHeight();
		++it;
	}
}

void	ID::Menu::__ReorganizeHorizontal(void)
{
	std::list<ID::Menu*>::iterator	it;
	std::list<ID::Menu*>::iterator	end;
	int				x;
	int				y;

	this->__CalculChildrenSidePosition(&x, &y);
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		PRINT_DBG("Menu __ReorganizeH X=" << x << "	Y=" << y << "\n")
		(*it)->SetPos(x, y);
		x = x + (*it)->GetWidth();
		++it;
	}
}

int	ID::Menu::__GetChildrenMaxWidth(void)
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;
	int				w;

	w = 0;
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		if ((*it)->GetWidth() > w)
			w = (*it)->GetWidth();
		++it;
	}
	return w;
}

int	ID::Menu::__GetChildrenMaxHeight(void)
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;
	int				h;

	h = 0;
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		if ((*it)->GetHeight() > h)
			h = (*it)->GetHeight();
		++it;
	}
	return h;
}

int	ID::Menu::__GetChildrenTotalWidth(void)
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;
	int				w;

	w = 0;
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		w = w + (*it)->GetLabel()->GetWidth();
		++it;
	}
	return w;
}

int	ID::Menu::__GetChildrenTotalHeight(void)
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;
	int				h;

	h = 0;
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		h = h + (*it)->GetLabel()->GetHeight();
		++it;
	}
	return h;
}
/*
void	ID::Menu::__CalculChildrenSidePosition(int* x, int* y)
{
	int		maxW;
	int		maxH;
	ID::Window*	win;

	if (this->__childrenSidePosition == ID::SIDE_POSITION_TOP)
	{
		*y = this->_y - this->__GetChildrenTotalHeight();
		this->__CalculChildrenAlignment(x, y, this->_x, *y);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_BOT)
	{
		*y = this->_y + this->GetHeight();
		this->__CalculChildrenAlignment(x, y, this->_x, *y);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_LEFT)
	{
		*x = this->_x - this->__GetChildrenMaxWidth();
		this->__CalculChildrenAlignment(x, y, *x, this->_y);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_RIGHT)
	{
		*x = this->_x + this->GetWidth();
		this->__CalculChildrenAlignment(x, y, *x, this->_y);
	}
	if (this->__mustBeOnScreen == true)
	{
		win = this->GetRealWindow();
		maxW = this->__GetChildrenMaxWidth();
		if (*x < 0)
			*x = 0;
		else if (*x + maxW > win->GetWidth())
			*x = win->GetWidth() - maxW;
		maxH = this->__GetChildrenTotalHeight();
		if (*y < 0)
			*y = 0;
		else if (*y + maxH > win->GetHeight())
		{
			*y = win->GetHeight() - maxH;
		}
	}
}
*/

void	ID::Menu::__CalculChildrenSidePosition(int* x, int* y)
{
//	int		maxW;
//	int		maxH;

	if (this->__childrenSidePosition == ID::SIDE_POSITION_TOP)
	{
		*y = -this->__GetChildrenTotalHeight();
		this->__CalculChildrenAlignment(x, y, 0, *y);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_BOT)
	{
		*y = this->GetHeight();
		this->__CalculChildrenAlignment(x, y, 0, *y);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_LEFT)
	{
		*x = -this->__GetChildrenMaxWidth();
		this->__CalculChildrenAlignment(x, y, *x, 0);
	}
	else if (this->__childrenSidePosition == ID::SIDE_POSITION_RIGHT)
	{
		*x = this->GetWidth();
		this->__CalculChildrenAlignment(x, y, *x, 0);
	}
	if (this->__mustBeOnScreen == true)
	{
/*		win = this->GetRealWindow();
		maxW = this->__GetChildrenMaxWidth();
		if (*x < 0)
			*x = 0;
		else if (*x + maxW > win->GetWidth())
			*x = win->GetWidth() - maxW;
		maxH = this->__GetChildrenTotalHeight();
		if (*y < 0)
			*y = 0;
		else if (*y + maxH > win->GetHeight())
		{
			*y = win->GetHeight() - maxH;
		}
*/	}
}

void	ID::Menu::__CalculChildrenAlignment(int* x, int* y, int minX, int minY)
{
	if (this->__childrenSidePosition == ID::SIDE_POSITION_LEFT ||
	    this->__childrenSidePosition == ID::SIDE_POSITION_RIGHT)
	{
		*x = minX;
		if (this->__childrenAlignment == ID::ALIGNMENT_TOP)
			*y = minY;
		else if (this->__childrenAlignment == ID::ALIGNMENT_BOT)
			*y = minY + this->GetHeight() - this->__GetChildrenTotalHeight();
		else if (this->__childrenAlignment == ID::ALIGNMENT_CENTER)
			*y = minY + (this->GetHeight() >> 1) -
			     (this->__GetChildrenTotalHeight() >> 1);
	}
	if (this->__childrenSidePosition == ID::SIDE_POSITION_TOP ||
	    this->__childrenSidePosition == ID::SIDE_POSITION_BOT)
	{
		*y = minY;
		if (this->__childrenAlignment == ID::ALIGNMENT_LEFT)
			*x = minX;
		else if (this->__childrenAlignment == ID::ALIGNMENT_RIGHT)
			*x = minX + this->GetWidth() - this->__GetChildrenMaxWidth();
		else if (this->__childrenAlignment == ID::ALIGNMENT_CENTER)
			*x = minX + (this->GetWidth() >> 1) -
			     (this->__GetChildrenMaxWidth() >> 1);
	}
}
