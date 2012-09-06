#include "Control.h"

#ifdef	__SDL
#include "../Wrapper/Wrapper_Event_SDL.h"
#endif

#ifdef	__OGL
#include "../Wrapper/Wrapper_Event_OGL.h"
#endif


void	ID::Control::SetCbClick(ID::cbEvent cb, void* d)
{
	this->_cbClick = cb;
	this->__cbClickData = d;
}

void	ID::Control::SetCbDoubleClick(ID::cbEvent cb, void* d)
{
	this->_cbDoubleClick = cb;
	this->__cbDoubleClickData = d;
}

void	ID::Control::SetCbClickDown(ID::cbEvent cb, void* d)
{
	this->_cbClickDown = cb;
	this->__cbClickDownData = d;
}

void	ID::Control::SetCbClickUp(ID::cbEvent cb, void* d)
{
	this->_cbClickUp = cb;
	this->__cbClickUpData = d;
}

void	ID::Control::SetCbEnter(ID::cbEvent cb, void* d)
{
	this->_cbEnter = cb;
	this->__cbEnterData = d;
}

void	ID::Control::SetCbLeave(ID::cbEvent cb, void* d)
{
	this->_cbLeave = cb;
	this->__cbLeaveData = d;
}

void	ID::Control::SetCbMotion(ID::cbEvent cb, void* d)
{
	this->_cbMotion = cb;
	this->__cbMotionData = d;
}

void	ID::Control::SetCbKeyUp(ID::cbEvent cb, void* d, bool)
{
	this->_cbKeyUp = cb;
	this->__cbKeyUpData = d;
/*	if (global == true)
	{
		if (cb != NULL)
			ID::Wrapper_Event::GetInstance()->AddKeyUpControl(this);
		else
			ID::Wrapper_Event::GetInstance()->DelKeyUpControl(this);
	}*/
}

void	ID::Control::SetCbKeyDown(ID::cbEvent cb, void* d, bool)
{
	this->_cbKeyDown = cb;
	this->__cbKeyDownData = d;
/*	if (global == true)
	{
		if (cb != NULL)
			ID::Wrapper_Event::GetInstance()->AddKeyDownControl(this);
		else
			ID::Wrapper_Event::GetInstance()->DelKeyDownControl(this);
	}*/
}

void	ID::Control::SetCbScreenChange(ID::cbEvent cb, void* d)
{
	this->_cbScreenChange = cb;
	this->__cbScreenChangeData = d;
}

void	ID::Control::SetCbFocusEnter(ID::cbEvent cb, void* d)
{
	this->_cbFocusEnter = cb;
	this->__cbFocusEnterData = d;
}

void	ID::Control::SetCbFocusLeave(ID::cbEvent cb, void* d)
{
	this->_cbFocusLeave = cb;
	this->__cbFocusLeaveData = d;
}

void	ID::Control::SetCbEnableChange(ID::cbEvent cb, void* d)
{
	this->_cbEnableChange = cb;
	this->__cbEnableChangeData = d;
}

void	ID::Control::SetCbResize(ID::cbEvent cb, void* d)
{
	this->_cbResize = cb;
	this->__cbResizeData = d;
}

void	ID::Control::SetCbQuit(ID::cbEvent cb, void* d)
{
	this->_cbQuit = cb;
	this->__cbQuitData = d;
}

void	ID::Control::SetCbUserEvent(ID::cbEvent cb, void* d)
{
	this->_cbUserEvent = cb;
	this->__cbUserEventData = d;
}

void	ID::Control::SetCbUpdate(ID::cb cb, void* d)
{
	this->_cbUpdate = cb;
	this->__cbUpdateData = d;
}
