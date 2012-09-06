#include "Select.h"
#include "Option.h"
#include "../Env.h"

#include <iostream>

ID::Select::Select(uint16_t w, uint16_t h) : Drawable(w, h),
					     _cbChange(NULL),
					     __focusOption(NULL), __open(false)
{
}

ID::Select::~Select(void)
{
}

int	ID::Select::ClickDown(ID::Event* e)
{
	if (this->GetOpen() == false)
		this->GetFocusOption()->ClickDown(e);
	else
	{
		std::list<ID::Drawable*>::iterator	it;
		std::list<ID::Drawable*>::iterator	end;
		int					y;

		y = e->clickDown.y - this->_y - this->_offset_y;
		y /= this->GetSurface()->h;
		if (y > (int)this->_childrenDrawable.size())
			return 0;
		if (y == 0)
			this->GetFocusOption()->ClickDown(e);
		--y;

		it = this->_childrenDrawable.begin();
		end = this->_childrenDrawable.end();
		while (it != end && y > 0)
		{
			++it;
			--y;
		}
		if (y == 0)
		{
			e->clickDown.y = this->_y + this->_offset_y;
			(*it)->ClickDown(e);
		}
	}
	ID::Env::GetInstance()->SetDrawableFocused(this);
	gettimeofday(&(this->_lastClickDown), NULL); // Dont care if failed
	return 1;
}

int	ID::Select::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;
	int					yOffset;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	if (it == end)
	{
		if (this->GetSurface()->BlitSurface(x + this->_x, y + this->_y) == -1)
			return -1;
		return 0;
	}
	if (this->GetFocusOption()->RefreshSurface(x + this->_x, y + this->_y) == -1)
		return -1;
	if (this->__open == false)
		return 0;
	yOffset = this->GetSurface()->h;
	y += yOffset;
	while (it != end)
	{
		if ((*it)->RefreshSurface(x + this->_x, y + this->_y) == -1)
			return -1;
		y += yOffset;
		++it;
	}
	return 0;
}

void	ID::Select::AddChild(ID::Drawable* _o)
{
	ID::Option*		o;

	o = dynamic_cast<ID::Option*>(_o);
	if (o == NULL)
		throw 1;
	if (o->GetParent() != NULL)
	{
		ID::Select* s = dynamic_cast<ID::Select*>(o->GetParent());
		s->DelChild(o);
	}
	if (this->_childrenDrawable.size() == 0)
		this->SetFocusOption(o);
	o->GetSurface()->Resize(this->GetSurface()->w, this->GetSurface()->h);
	this->Control::AddChild(o);
}

void	ID::Select::AddChild(ID::Control*)
{
}

int	ID::Select::DelChild(ID::Drawable* o)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == o)
		{
			if (this->__focusOption == o)
				this->__focusOption = (ID::Option*)this->_childrenDrawable.front();
			(*it)->SetParent(NULL);
			this->_childrenDrawable.erase(it);
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::Select::DelChild(ID::Control*)
{
	return -1;
}

void	ID::Select::SetFocusOption(ID::Option* o)
{
	this->__focusOption = o;
	this->Change();
}

ID::Option*	ID::Select::GetFocusOption(void) const
{
	return this->__focusOption;
}

int	ID::Select::GetValue(void) const
{
	return this->GetFocusOption()->GetValue();
}

void	ID::Select::SetOpen(bool b)
{
	this->__open = b;
}

bool	ID::Select::GetOpen(void) const
{
	return this->__open;
}

int	ID::Select::Change(void)
{
	if (this->_cbChange != NULL)
	{
		this->_cbChange(this, NULL, this->__cbChangeData);
		return 1;
	}
	return 0;
}

void	ID::Select::SetCbChange(ID::cbEvent cb, void* data)
{
	this->_cbChange = cb;
	this->__cbChangeData = data;
}

ID::cbEvent	ID::Select::GetCbChange(void) const
{
	return this->_cbChange;
}

