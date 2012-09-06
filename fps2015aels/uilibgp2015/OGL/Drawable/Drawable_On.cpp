#include "Drawable.h"

bool	ID::Drawable::_OnClick(ID::Event* event)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    (this->GetAbstractParent() == true ||
	     (this->_surface != NULL &&
	      event->click.x >= this->_x + this->_offset_x &&
	      event->click.y >= this->_y + this->_offset_y &&
	      event->click.x < this->_x + this->_offset_x + this->_surface->w &&
	      event->click.y < this->_y + this->_offset_y + this->_surface->h)))
		return true;
	return false;
}

bool	ID::Drawable::_OnDoubleClick(ID::Event* event)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    (this->GetAbstractParent() == true ||
	     (this->_surface != NULL &&
	      event->doubleClick.x >= this->_x + this->_offset_x &&
	      event->doubleClick.y >= this->_y + this->_offset_y &&
	      event->doubleClick.x < this->_x + this->_offset_x + this->_surface->w &&
	      event->doubleClick.y < this->_y + this->_offset_y + this->_surface->h)))
		return true;
	return false;
}

bool	ID::Drawable::_OnClickDown(ID::Event* event)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    (this->GetAbstractParent() == true ||
	     (this->_surface != NULL &&
	      event->clickDown.x >= this->_x + this->_offset_x &&
	      event->clickDown.y >= this->_y + this->_offset_y &&
	      event->clickDown.x < this->_x + this->_offset_x + this->_surface->w &&
	      event->clickDown.y < this->_y + this->_offset_y + this->_surface->h)))
		return true;
	return false;
}

bool	ID::Drawable::_OnClickUp(ID::Event* event)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    (this->GetAbstractParent() == true ||
	     (this->_surface != NULL &&
	      event->clickUp.x >= this->_x + this->_offset_x &&
	      event->clickUp.y >= this->_y + this->_offset_y &&
	      event->clickUp.x < this->_x + this->_offset_x + this->_surface->w &&
	      event->clickUp.y < this->_y + this->_offset_y + this->_surface->h)))
		return true;
	return false;
}

bool	ID::Drawable::_OnEnter(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnLeave(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnMotion(ID::Event* event)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    (this->GetAbstractParent() == true ||
	     (this->_surface != NULL &&
	      event->motion.x >= this->_x + this->_offset_x &&
	      event->motion.y >= this->_y + this->_offset_y &&
	      event->motion.x < this->_x + this->_offset_x + this->_surface->w &&
	      event->motion.y < this->_y + this->_offset_y + this->_surface->h)))
		return true;
	return false;
}

bool	ID::Drawable::_OnKeyUp(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnKeyDown(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnFocusEnter(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnFocusLeave(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnEnableChange(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnScreenChange(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnResize(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnQuit(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

bool	ID::Drawable::_OnUserEvent(ID::Event*)
{
	if (this->GetOnScreen() == true &&
	    this->GetEnable() == true)
		return true;
	return false;
}

