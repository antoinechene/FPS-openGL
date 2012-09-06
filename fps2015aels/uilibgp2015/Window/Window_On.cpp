#include "Window.h"

bool	ID::Window::_OnClick(ID::Event* event)
{
	if (event->click.x < this->__window.w &&
	    event->click.y < this->__window.h)
		return true;
	return false;
}

bool	ID::Window::_OnDoubleClick(ID::Event* event)
{
	if (event->doubleClick.x < this->__window.w &&
	    event->doubleClick.y < this->__window.h)
		return true;
	return false;
}

bool	ID::Window::_OnClickDown(ID::Event* event)
{
	if (event->clickDown.x < this->__window.w &&
	    event->clickDown.y < this->__window.h)
		return true;
	return false;
}

bool	ID::Window::_OnClickUp(ID::Event* event)
{
	if (event->clickUp.x < this->__window.w &&
	    event->clickUp.y < this->__window.h)
		return true;
	return false;
}

bool	ID::Window::_OnEnter(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnLeave(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnMotion(ID::Event* event)
{
	if (event->motion.x < this->__window.w &&
	    event->motion.y < this->__window.h)
		return true;
	return false;
}

bool	ID::Window::_OnKeyUp(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnKeyDown(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnFocusEnter(ID::Event*)
{
	return true;
}


bool	ID::Window::_OnFocusLeave(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnEnableChange(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnScreenChange(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnResize(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnQuit(ID::Event*)
{
	return true;
}

bool	ID::Window::_OnUserEvent(ID::Event*)
{
	return true;
}

