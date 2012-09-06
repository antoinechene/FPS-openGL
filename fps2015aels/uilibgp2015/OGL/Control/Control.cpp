#include "Control.h"
#include "../Drawable/Drawable.h"
#include "../Env.h"
#include <iostream>

ID::Control::Control() : _parent(NULL),
			 _cbClick(NULL),
			 _cbDoubleClick(NULL),
			 _cbClickDown(NULL),
			 _cbClickUp(NULL),
			 _cbEnter(NULL),
			 _cbLeave(NULL),
			 _cbMotion(NULL),
			 _cbKeyUp(NULL),
			 _cbKeyDown(NULL),
			 _cbFocusEnter(NULL),
			 _cbFocusLeave(NULL),
			 _cbEnableChange(NULL),
			 _cbScreenChange(NULL),
			 _cbResize(NULL),
			 _cbQuit(NULL),
			 _cbUserEvent(NULL),
			 _cbUpdate(NULL),
			 __cbClickData(NULL),
			 __cbDoubleClickData(NULL),
			 __cbClickDownData(NULL),
			 __cbClickUpData(NULL),
			 __cbEnterData(NULL),
			 __cbLeaveData(NULL),
			 __cbMotionData(NULL),
			 __cbKeyUpData(NULL),
			 __cbKeyDownData(NULL),
			 __cbFocusEnterData(NULL),
			 __cbFocusLeaveData(NULL),
			 __cbEnableChangeData(NULL),
			 __cbScreenChangeData(NULL),
			 __cbResizeData(NULL),
			 __cbQuitData(NULL),
			 __cbUserEventData(NULL),
			 __cbUpdateData(NULL),
			 __name(NULL)
{
}

ID::Control::Control(const ID::Control& c)
{
	this->_parent = c._parent;
	this->_childrenControl = c._childrenControl;
	this->_childrenDrawable = c._childrenDrawable;
	this->_cbClick = c._cbClick;
	this->_cbDoubleClick = c._cbDoubleClick;
	this->_cbClickDown = c._cbClickDown;
	this->_cbClickUp = c._cbClickUp;
	this->_cbEnter = c._cbEnter;
	this->_cbLeave = c._cbLeave;
	this->_cbMotion = c._cbMotion;
	this->_cbKeyUp = c._cbKeyUp;
	this->_cbKeyDown = c._cbKeyDown;
	this->_cbFocusEnter = c._cbFocusEnter;
	this->_cbFocusLeave = c._cbFocusLeave;
	this->_cbEnableChange = c._cbEnableChange;
	this->_cbScreenChange = c._cbScreenChange;
	this->_cbResize = c._cbResize;
	this->_cbQuit = c._cbQuit;
	this->_cbUserEvent = c._cbUserEvent;
	this->_cbUpdate = c._cbUpdate;
	this->__cbClickData = c.__cbClickData;
	this->__cbDoubleClickData = c.__cbDoubleClickData;
	this->__cbClickDownData = c.__cbClickDownData;
	this->__cbClickUpData = c.__cbClickUpData;
	this->__cbEnterData = c.__cbEnterData;
	this->__cbLeaveData = c.__cbLeaveData;
	this->__cbMotionData = c.__cbMotionData;
	this->__cbKeyUpData = c.__cbKeyUpData;
	this->__cbKeyDownData = c.__cbKeyDownData;
	this->__cbFocusEnterData = c.__cbFocusEnterData;
	this->__cbFocusLeaveData = c.__cbFocusLeaveData;
	this->__cbEnableChangeData = c.__cbEnableChangeData;
	this->__cbScreenChangeData = c.__cbScreenChangeData;
	this->__cbResizeData = c.__cbResizeData;
	this->__cbQuitData = c.__cbQuitData;
	this->__cbUserEventData = c.__cbUserEventData;
	this->__cbUpdateData = c.__cbUpdateData;
	this->__name = c.__name;
}

ID::Control::~Control(void)
{
	this->_childrenControl.clear();
	this->_childrenDrawable.clear();
}

ID::Control&	ID::Control::operator=(const ID::Control& c)
{
	this->_parent = c._parent;
	this->_childrenControl = c._childrenControl;
	this->_childrenDrawable = c._childrenDrawable;
	this->_cbClick = c._cbClick;
	this->_cbDoubleClick = c._cbDoubleClick;
	this->_cbClickDown = c._cbClickDown;
	this->_cbClickUp = c._cbClickUp;
	this->_cbEnter = c._cbEnter;
	this->_cbLeave = c._cbLeave;
	this->_cbMotion = c._cbMotion;
	this->_cbKeyUp = c._cbKeyUp;
	this->_cbKeyDown = c._cbKeyDown;
	this->_cbFocusEnter = c._cbFocusEnter;
	this->_cbFocusLeave = c._cbFocusLeave;
	this->_cbEnableChange = c._cbEnableChange;
	this->_cbScreenChange = c._cbScreenChange;
	this->_cbResize = c._cbResize;
	this->_cbQuit = c._cbQuit;
	this->_cbUserEvent = c._cbUserEvent;
	this->_cbUpdate = c._cbUpdate;
	this->__cbClickData = c.__cbClickData;
	this->__cbDoubleClickData = c.__cbDoubleClickData;
	this->__cbClickDownData = c.__cbClickDownData;
	this->__cbClickUpData = c.__cbClickUpData;
	this->__cbEnterData = c.__cbEnterData;
	this->__cbLeaveData = c.__cbLeaveData;
	this->__cbMotionData = c.__cbMotionData;
	this->__cbKeyUpData = c.__cbKeyUpData;
	this->__cbKeyDownData = c.__cbKeyDownData;
	this->__cbFocusEnterData = c.__cbFocusEnterData;
	this->__cbFocusLeaveData = c.__cbFocusLeaveData;
	this->__cbEnableChangeData = c.__cbEnableChangeData;
	this->__cbScreenChangeData = c.__cbScreenChangeData;
	this->__cbResizeData = c.__cbResizeData;
	this->__cbQuitData = c.__cbQuitData;
	this->__cbUserEventData = c.__cbUserEventData;
	this->__cbUpdateData = c.__cbUpdateData;
	this->__name = c.__name;
	return *this;
}

void	ID::Control::AddChild(ID::Drawable* d)
{
	ID::REL_POS_TYPE	relPos;
	ID::Drawable*		parent;

	parent = d->GetParent();
	if (parent != NULL)
	{
		parent->DelChild(d);
	}
	this->_childrenDrawable.push_back(d);
	d->SetParent((Drawable*)this);
	relPos = d->GetRelPos();
	if (relPos != ID::REL_POS_NONE)
		d->SetPos(relPos);
	else
	{
		int16_t	x;
		int16_t	y;

		d->GetPos(&x, &y);
		d->SetPos(x, y);
	}
}

void	ID::Control::AddChild(ID::Control* c)
{
	this->_childrenControl.push_back(c);
	c->SetParent((Drawable*)this);
}

int	ID::Control::DelChild(ID::Control* control)
{
	std::list<ID::Control*>::iterator	it;
	std::list<ID::Control*>::iterator	end;

	it = this->_childrenControl.begin();
	end = this->_childrenControl.end();
	while (it != end)
	{
		if (*it == control)
		{
			this->_childrenControl.erase(it);
			control->SetParent(NULL);
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::Control::DelChild(ID::Drawable* drawable)
{
	ID::Env*				e;
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	e = Env::GetInstance();
	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == drawable)
		{
			if (e->GetDrawableFocused() == drawable)
				e->SetDrawableFocused(NULL);
			if (e->GetDrawableEntered() == drawable)
				e->SetDrawableEntered(NULL);
			this->_childrenDrawable.erase(it);
			drawable->SetParent(NULL);
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::Control::MoveChildFront(ID::Drawable* drawable)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == drawable)
		{
			this->_childrenDrawable.push_front(*it);
			this->_childrenDrawable.erase(it);
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::Control::MoveChildBack(ID::Drawable* drawable)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == drawable)
		{
			this->_childrenDrawable.push_back(*it);
			this->_childrenDrawable.erase(it);
			return 0;
		}
		++it;
	}
	return -1;
}

void	ID::Control::ClearChildren()
{
	this->_childrenControl.clear();
	this->_childrenDrawable.clear();
}

void	ID::Control::SetParent(ID::Drawable* p)
{
	Env*	e;

	e = Env::GetInstance();
	if (e->GetDrawableFocused() == this)
		e->SetDrawableFocused(NULL);
	if (e->GetDrawableEntered() == this)
		e->SetDrawableEntered(NULL);
	this->_parent = p;
}

ID::Drawable*	ID::Control::GetParent(void) const
{
	return this->_parent;
}

std::list<ID::Control*>*	ID::Control::GetChildrenControl(void)
{
	return &(this->_childrenControl);
}

std::list<ID::Drawable*>*	ID::Control::GetChildrenDrawable(void)
{
	return &(this->_childrenDrawable);
}

