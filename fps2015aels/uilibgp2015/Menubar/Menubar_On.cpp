#include "Menubar.h"
#include <iostream>

bool	ID::Menubar::_OnClick(ID::Event* e)
{
	if (this->GetOnScreen() == false)
		return false;
	if (this->_surface != NULL &&
	    this->GetEnable() == true &&
	    (int16_t)e->click.x >= this->_x &&
	    (int16_t)e->click.y >= this->_y &&
	    e->click.x < this->_x + this->_surface->w &&
	    e->click.y < this->_y + this->_surface->h)
		return true;
	std::list<Menu*>::reverse_iterator	it;
	std::list<Menu*>::reverse_iterator	end;

	it = this->__childrenMenu.rbegin();
	end = this->__childrenMenu.rend();
	while (it != end)
	{
		if ((*it)->_OnClick(e) == true)
			return true;
		++it;
	}
	return false;
}

bool	ID::Menubar::_OnDoubleClick(ID::Event* e)
{
	if (this->GetOnScreen() == false)
		return false;
	if (this->_surface != NULL &&
	    this->GetEnable() == true &&
	    (int16_t)e->doubleClick.x >= this->_x &&
	    (int16_t)e->doubleClick.y >= this->_y &&
	    e->doubleClick.x < this->_x + this->_surface->w &&
	    e->doubleClick.y < this->_y + this->_surface->h)
		return true;
	std::list<Menu*>::reverse_iterator	it;
	std::list<Menu*>::reverse_iterator	end;

	it = this->__childrenMenu.rbegin();
	end = this->__childrenMenu.rend();
	while (it != end)
	{
		if ((*it)->_OnDoubleClick(e) == true)
			return true;
		++it;
	}
	return false;
}

bool	ID::Menubar::_OnClickDown(ID::Event* e)
{
	if (this->GetOnScreen() == false)
		return false;
	if (this->_surface != NULL &&
	    this->GetEnable() == true &&
	    (int16_t)e->clickDown.x >= this->_x &&
	    (int16_t)e->clickDown.y >= this->_y &&
	    e->clickDown.x < this->_x + this->_surface->w &&
	    e->clickDown.y < this->_y + this->_surface->h)
		return true;
	std::list<Menu*>::reverse_iterator	it;
	std::list<Menu*>::reverse_iterator	end;

	it = this->__childrenMenu.rbegin();
	end = this->__childrenMenu.rend();
	while (it != end)
	{
		if ((*it)->_OnClickDown(e) == true)
			return true;
		++it;
	}
	return false;
}

bool	ID::Menubar::_OnClickUp(ID::Event* e)
{
	if (this->GetOnScreen() == false)
		return false;
	if (this->_surface != NULL &&
	    this->GetEnable() == true &&
	    (int16_t)e->clickUp.x >= this->_x &&
	    (int16_t)e->clickUp.y >= this->_y &&
	    e->clickUp.x < this->_x + this->_surface->w &&
	    e->clickUp.y < this->_y + this->_surface->h)
		return true;
	std::list<Menu*>::reverse_iterator	it;
	std::list<Menu*>::reverse_iterator	end;

	it = this->__childrenMenu.rbegin();
	end = this->__childrenMenu.rend();
	while (it != end)
	{
		if ((*it)->_OnClickUp(e) == true)
			return true;
		++it;
	}
	return false;
}

bool	ID::Menubar::_OnEnter(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Menubar::_OnLeave(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Menubar::_OnMotion(ID::Event* e)
{
	if (this->GetOnScreen() == false)
		return false;
	if (this->_surface != NULL &&
	    this->GetEnable() == true &&
	    (int16_t)e->motion.x >= this->_x &&
	    (int16_t)e->motion.y >= this->_y &&
	    e->motion.x < this->_x + this->_surface->w &&
	    e->motion.y < this->_y + this->_surface->h)
		return true;
	std::list<Menu*>::reverse_iterator	it;
	std::list<Menu*>::reverse_iterator	end;

	it = this->__childrenMenu.rbegin();
	end = this->__childrenMenu.rend();
	while (it != end)
	{
		if ((*it)->_OnMotion(e) == true)
			return true;
		++it;
	}
	return false;
}

