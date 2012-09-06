#include "Menubar.h"
#include "../Window/Window.h"

int	ID::Menubar::Click(ID::Event* e)
{
	if (!this->_OnClick(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->Click(e))
			return 1;
		++d_rit;
	}
	if (this->_cbClick != NULL)
		this->_cbClick(this, e, this->__cbClickData);
	return 1;
}

int	ID::Menubar::DoubleClick(ID::Event* e)
{
	if (!this->_OnDoubleClick(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->DoubleClick(e))
			return 1;
		++d_rit;
	}
	if (this->_cbDoubleClick != NULL)
		this->_cbDoubleClick(this, e, this->__cbDoubleClickData);
	return 1;
}

int	ID::Menubar::ClickDown(ID::Event* e)
{
	if (!this->_OnClickDown(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->ClickDown(e))
			return 1;
		++d_rit;
	}
	if (this->_cbClickDown != NULL)
		this->_cbClickDown(this, e, this->__cbClickDownData);
	return 1;
}

int	ID::Menubar::ClickUp(ID::Event* e)
{
	if (!this->_OnClickUp(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->ClickUp(e))
			return 1;
		++d_rit;
	}
	if (this->_cbClickUp != NULL)
		this->_cbClickUp(this, e, this->__cbClickUpData);
	return 1;
}

int	ID::Menubar::Enter(ID::Event* e)
{
	if (!this->_OnEnter(e))
		return 0;
	if (this->_cbEnter != NULL)
		this->_cbEnter(this, e, this->__cbEnterData);
	return 1;
}

int	ID::Menubar::Leave(ID::Event* e)
{
	if (!this->_OnLeave(e))
		return 0;
	if (this->_cbLeave != NULL)
		this->_cbLeave(this, e, this->__cbLeaveData);
	return 1;
}

int	ID::Menubar::Motion(ID::Event* e)
{
	if (!this->_OnMotion(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
	while (d_rit != d_end)
	{
		if ((*d_rit)->Motion(e))
			return 1;
		++d_rit;
	}
	this->GetRealWindow()->SetDrawableEnter(this);
	if (this->_cbMotion != NULL)
		this->_cbMotion(this, e, this->__cbMotionData);
	return 1;
}

int	ID::Menubar::KeyUp(ID::Event* e)
{
	if (!this->_OnKeyUp(e))
		return 0;
	if (this->_cbKeyUp != NULL)
		this->_cbKeyUp(this, e, this->__cbKeyUpData);
	return 1;
}

int	ID::Menubar::KeyDown(ID::Event* e)
{
	if (!this->_OnKeyDown(e))
		return 0;
	if (this->_cbKeyDown != NULL)
		this->_cbKeyDown(this, e, this->__cbKeyDownData);
	return 1;
}

int	ID::Menubar::FocusEnter(ID::Event* e)
{
	if (!this->_OnFocusEnter(e))
		return 0;
	if (this->_cbFocusEnter != NULL)
		this->_cbFocusEnter(this, e, this->__cbFocusEnterData);
	return 1;
}

int	ID::Menubar::FocusLeave(ID::Event* e)
{
	if (!this->_OnFocusLeave(e))
		return 0;
	if (this->_cbFocusLeave != NULL)
		this->_cbFocusLeave(this, e, this->__cbFocusLeaveData);
	return 1;
}

int	ID::Menubar::EnableChange(ID::Event* e)
{
	if (!this->_OnEnableChange(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
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

int	ID::Menubar::ScreenChange(ID::Event* e)
{
	if (!this->_OnScreenChange(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
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

int	ID::Menubar::Resize(ID::Event* e)
{
	if (!this->_OnResize(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
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

int	ID::Menubar::Quit(ID::Event* e)
{
	if (!this->_OnQuit(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
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

int	ID::Menubar::UserEvent(ID::Event* e)
{
	if (!this->_OnUserEvent(e))
		return 0;
	std::list<ID::Menu*>::reverse_iterator	d_rit;
	std::list<ID::Menu*>::reverse_iterator	d_end;

	d_rit = this->__childrenMenu.rbegin();
	d_end = this->__childrenMenu.rend();
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

