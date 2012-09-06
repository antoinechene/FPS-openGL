#include "Control.h"

bool	ID::Control::_OnClick(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnDoubleClick(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnClickDown(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnClickUp(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnEnter(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnLeave(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnMotion(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnKeyUp(ID::Event*)
{
	return true;
}

bool	ID::Control::_OnKeyDown(ID::Event*)
{
	return true;
}

bool	ID::Control::_OnFocusEnter(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnFocusLeave(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnEnableChange(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnScreenChange(ID::Event* event)
{
	(void)event;
	return true;
}

bool	ID::Control::_OnResize(ID::Event* event)
{
	(void)event;
	return false;
}

bool	ID::Control::_OnQuit(ID::Event* event)
{
	(void)event;
	return true;
}

bool	ID::Control::_OnUserEvent(ID::Event* event)
{
	(void)event;
	return true;
}
