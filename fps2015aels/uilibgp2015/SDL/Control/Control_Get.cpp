#include "Control.h"

ID::cbEvent	ID::Control::GetCbClick(void) const
{
	return this->_cbClick;
}

ID::cbEvent	ID::Control::GetCbDoubleClick(void) const
{
	return this->_cbDoubleClick;
}

ID::cbEvent	ID::Control::GetCbClickDown(void) const
{
	return this->_cbClickDown;
}

ID::cbEvent	ID::Control::GetCbClickUp(void) const
{
	return this->_cbClickUp;
}

ID::cbEvent	ID::Control::GetCbEnter(void) const
{
	return this->_cbEnter;
}

ID::cbEvent	ID::Control::GetCbLeave(void) const
{
	return this->_cbLeave;
}

ID::cbEvent	ID::Control::GetCbMotion(void) const
{
	return this->_cbMotion;
}

ID::cbEvent	ID::Control::GetCbKeyUp(void) const
{
	return this->_cbKeyUp;
}

ID::cbEvent	ID::Control::GetCbKeyDown(void) const
{
	return this->_cbKeyDown;
}


ID::cbEvent	ID::Control::GetCbFocusEnter(void) const
{
	return this->_cbFocusEnter;
}

ID::cbEvent	ID::Control::GetCbFocusLeave(void) const
{
	return this->_cbFocusLeave;
}

ID::cbEvent	ID::Control::GetCbEnableChange(void) const
{
	return this->_cbEnableChange;
}

ID::cbEvent	ID::Control::GetCbScreenChange(void) const
{
	return this->_cbScreenChange;
}

ID::cbEvent	ID::Control::GetCbResize(void) const
{
	return this->_cbResize;
}

ID::cbEvent	ID::Control::GetCbQuit(void) const
{
	return this->_cbQuit;
}


ID::cbEvent	ID::Control::GetCbUserEvent(void) const
{
	return this->_cbUserEvent;
}

ID::cb		ID::Control::GetCbUpdate(void) const
{
	return this->_cbUpdate;
}
