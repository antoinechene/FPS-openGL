#include "Menubar.h"
#include "../Drawable/Drawable.h"
#include "../Font.h"
#include <iostream>

ID::Menubar::Menubar(uint16_t w, uint16_t h, uint32_t f,
		     uint32_t r, uint32_t g,
		     uint32_t b, uint32_t a,
		     ID::REL_POS_TYPE relPos) : Drawable(w, h, f, r, g, b, a)
{
	this->_relPos = relPos;
}

ID::Menubar::~Menubar()
{
}

void	ID::Menubar::SetOnScreen(bool visible)
{
/*	if (this->GetWindow() != NULL)
	{
		std::cout << "ToReorg" << std::endl;
		this->GetWindow()->SetToReorganize(true);
	}
*/	this->Drawable::SetOnScreen(visible);
}

void	ID::Menubar::AddChild(Menu* menu)
{
	this->__childrenMenu.push_back(menu);
	menu->SetParent(this);
	this->_Reorganize();
}

int	ID::Menubar::RefreshToSurface(ID::Surface* s, int x, int y)
{
	PRINT_DBG("Menubar RefToSur\n");
	if (this->GetOnScreen() == false)
		return 0;
//	if (this->GetInvalidate() == true)
		this->_RefreshBackground();
	if (s != NULL &&
	    this->_surface->BlitSurface(this->_visibleRect, s,
					x + this->_x,
					y + this->_y) == -1)
		return -1;
	if (this->_cbUpdate != NULL)
		this->_cbUpdate(this, this->__cbUpdateData);
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;

	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		if ((*it)->RefreshToSurface(s, 0, 0) == -1)
			return -1;
		++it;
	}
	return 0;
}

void	ID::Menubar::_Reorganize(void)
{
	std::list<Menu*>::iterator	it;
	std::list<Menu*>::iterator	end;
	int				minX;
	int				w;
	ID::Font*			font;

	font = ID::Font::GetInstance();
	w = 0;
	minX = 0;
	it = this->__childrenMenu.begin();
	end = this->__childrenMenu.end();
	while (it != end)
	{
		(*it)->SetPos(minX, 0);
		w = (*it)->GetWidth();
		minX = minX + w;
		if (minX > this->GetWidth())
			break ;
		++it;
	}
}

