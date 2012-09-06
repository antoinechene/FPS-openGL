#include "Control.h"
#include "../Drawable/Drawable.h"

int	ID::Control::Click(ID::Event*)
{
	return 0;
}

int	ID::Control::DoubleClick(ID::Event*)
{
	return 0;
}

int	ID::Control::ClickDown(ID::Event*)
{
	return 0;
}

int	ID::Control::ClickUp(ID::Event*)
{
	return 0;
}

int	ID::Control::Enter(ID::Event*)
{
	return 0;
}

int	ID::Control::Leave(ID::Event*)
{
	return 0;
}

int	ID::Control::Motion(ID::Event*)
{
	return 0;
}

int	ID::Control::KeyUp(ID::Event* e)
{
	if (!this->_OnKeyUp(e))
		return 0;
	if (this->_cbKeyUp != NULL)
		this->_cbKeyUp(this, e, this->__cbKeyUpData);
	return 1;
}

int	ID::Control::KeyDown(ID::Event* e)
{
	if (!this->_OnKeyDown(e))
		return 0;
	if (this->_cbKeyDown != NULL)
		this->_cbKeyDown(this, e, this->__cbKeyDownData);
	return 1;
}

int	ID::Control::FocusEnter(ID::Event*)
{
	return 0;
}

int	ID::Control::FocusLeave(ID::Event*)
{
	return 0;
}

int	ID::Control::EnableChange(ID::Event* e)
{
	if (!this->_OnEnableChange(e))
		return 0;
	std::list<ID::Drawable*>::reverse_iterator	d_rit;
	std::list<ID::Control*>::reverse_iterator	c_rit;
	std::list<ID::Drawable*>::reverse_iterator	d_end;
	std::list<ID::Control*>::reverse_iterator	c_end;

	c_rit = this->_childrenControl.rbegin();
	c_end = this->_childrenControl.rend();
	while (c_rit != c_end)
	{
		if ((*c_rit)->EnableChange(e))
			return 1;
		++c_rit;
	}

	d_rit = this->_childrenDrawable.rbegin();
	d_end = this->_childrenDrawable.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->EnableChange(e))
			return 1;
		++d_rit;
	}
	if (this->_cbEnableChange != NULL)
		this->_cbEnableChange(this, e, this->__cbEnableChangeData);
	return 1;
}

int	ID::Control::ScreenChange(ID::Event* e)
{
	if (!this->_OnScreenChange(e))
		return 0;
	std::list<ID::Drawable*>::reverse_iterator	d_rit;
	std::list<ID::Drawable*>::reverse_iterator	d_end;

	d_rit = this->_childrenDrawable.rbegin();
	d_end = this->_childrenDrawable.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->ScreenChange(e))
			return 1;
		++d_rit;
	}
	if (this->_cbScreenChange != NULL)
		this->_cbScreenChange(this, e, this->__cbScreenChangeData);
	return 1;
}

int	ID::Control::Resize(ID::Event* e)
{
	if (!this->_OnResize(e))
		return 0;
	std::list<ID::Drawable*>::reverse_iterator	d_rit;
	std::list<ID::Drawable*>::reverse_iterator	d_end;

	d_rit = this->_childrenDrawable.rbegin();
	d_end = this->_childrenDrawable.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->Resize(e))
			return 1;
		++d_rit;
	}
	if (this->_cbResize != NULL)
		this->_cbResize(this, e, this->__cbResizeData);
	return 1;
}

int	ID::Control::Quit(ID::Event* e)
{
	if (!this->_OnQuit(e))
		return 0;
	std::list<ID::Drawable*>::reverse_iterator	d_rit;
	std::list<ID::Control*>::reverse_iterator	c_rit;
	std::list<ID::Drawable*>::reverse_iterator	d_end;
	std::list<ID::Control*>::reverse_iterator	c_end;

	c_rit = this->_childrenControl.rbegin();
	c_end = this->_childrenControl.rend();
	while (c_rit != c_end)
	{
		if ((*c_rit)->Quit(e))
			return 1;
		++c_rit;
	}

	d_rit = this->_childrenDrawable.rbegin();
	d_end = this->_childrenDrawable.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->Quit(e))
			return 1;
		++d_rit;
	}
	if (this->_cbQuit != NULL)
		this->_cbQuit(this, e, this->__cbQuitData);
	return 1;
}

int	ID::Control::UserEvent(ID::Event* e)
{
	if (!this->_OnUserEvent(e))
		return 0;
	std::list<ID::Drawable*>::reverse_iterator	d_rit;
	std::list<ID::Control*>::reverse_iterator	c_rit;
	std::list<ID::Drawable*>::reverse_iterator	d_end;
	std::list<ID::Control*>::reverse_iterator	c_end;

	c_rit = this->_childrenControl.rbegin();
	c_end = this->_childrenControl.rend();
	while (c_rit != c_end)
	{
		if ((*c_rit)->UserEvent(e))
			return 1;
		++c_rit;
	}

	d_rit = this->_childrenDrawable.rbegin();
	d_end = this->_childrenDrawable.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->UserEvent(e))
			return 1;
		++d_rit;
	}
	if (this->_cbUserEvent != NULL)
		this->_cbUserEvent(this, e, this->__cbUserEventData);
	return 1;
}

