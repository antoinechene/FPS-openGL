#include "TCol.h"
#include "TRow.h"
#include "../Env.h"

#include <iostream>

ID::TCol::TCol(uint16_t w, uint16_t h,
	       unsigned short int r, unsigned short int c) : Drawable(w, h), __rowspan(r), __colspan(c)
{
}

ID::TCol::~TCol(void)
{
}

int	ID::TCol::ClickDown(ID::Event* e)
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

void	ID::TCol::AddChild(ID::Drawable* d)
{
	this->Control::AddChild(d);
	if (this->GetParent() != NULL)
		((ID::TRow*)this->GetParent())->SetChange(true);
}

int	ID::TCol::DelChild(ID::Drawable* o)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if (*it == o)
		{
			(*it)->SetParent(NULL);
			this->_childrenDrawable.erase(it);
			if (this->GetParent() != NULL)
				((ID::TRow*)this->GetParent())->SetChange(true);
			return 0;
		}
		++it;
	}
	return -1;
}

unsigned short int	ID::TCol::GetRowspan(void) const
{
	return this->__rowspan;
}

unsigned short int	ID::TCol::GetColspan(void) const
{
	return this->__colspan;
}

