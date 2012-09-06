#include "TRow.h"
#include "TCol.h"
#include "Table.h"
#include "../Env.h"

#include <iostream>

ID::TRow::TRow() : Drawable(0, 0)
{
}

ID::TRow::~TRow(void)
{
}

int	ID::TRow::ClickDown(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;
	int	y;

	y = e->clickDown.y - this->_y - this->_offset_y;
	y /= this->GetSurface()->h;
	if (y > (int)this->_childrenDrawable.size())
		return 0;
	--y;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
		while (it != end && y >= 0)
		{
			if (y == 0)
			{
				e->clickDown.y = this->_y + this->_offset_y;
				(*it)->ClickDown(e);
				break ;
			}
			++it;
			--y;
		}
	ID::Env::GetInstance()->SetDrawableFocused(this);
	gettimeofday(&(this->_lastClickDown), NULL); // Dont care if failed
	return 1;
}

int	ID::TRow::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;
	std::vector<unsigned int>::iterator	itO;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	itO = ((ID::Table*)this->GetParent())->GetColOffsets()->begin();
	while (it != end)
	{
		if ((*it)->RefreshSurface(x + this->_x, y + this->_y) == -1)
			return -1;
		x += *itO;
		++itO;
		++it;
	}
	return 0;
}

void	ID::TRow::AddChild(ID::Drawable* _c)
{
	ID::TCol*		c;

	c = dynamic_cast<ID::TCol*>(_c);
	if (c == NULL)
		throw 1;
	if (c->GetParent() != NULL)
	{
		ID::TRow* r = dynamic_cast<ID::TRow*>(c->GetParent());
		r->DelChild(c);
	}
	this->Control::AddChild(c);
	this->__AutoResize();
	this->SetChange(true);
}

void	ID::TRow::AddChild(ID::Control*)
{
}

int	ID::TRow::DelChild(ID::Drawable* c)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == c)
		{
			(*it)->SetParent(NULL);
			this->_childrenDrawable.erase(it);
			this->SetChange(true);
			this->__AutoResize();
			return 0;
		}
		++it;
	}
	return -1;
}

int	ID::TRow::DelChild(ID::Control*)
{
	return -1;
}

void	ID::TRow::SetChange(bool b)
{
	if (this->GetParent() != NULL)
	{
		((ID::Table*)this->GetParent())->SetChange(b);
	}
}

void	ID::TRow::__AutoResize(void)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;
	int					w;
	int					h;

	w = 0;
	h = 0;
	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		w += (*it)->GetSurface()->w;
		if ((*it)->GetSurface()->h > h)
			h = (*it)->GetSurface()->h;
		++it;
	}
	this->GetSurface()->Resize(w, h);
}

