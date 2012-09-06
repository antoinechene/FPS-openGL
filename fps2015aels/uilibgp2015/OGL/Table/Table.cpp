#include "Table.h"
#include "TRow.h"
#include "../Env.h"

#include <iostream>

ID::Table::Table() : Drawable(), __changed(false)
{
	this->_colOffset.resize(5, 0);
}

ID::Table::~Table(void)
{
}

int	ID::Table::ClickDown(ID::Event* e)
{
	return 0;
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;
	int					y;

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

int	ID::Table::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->__changed == true)
		this->CalculColOffsets();
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->_childrenDrawable.begin();
	end = this->_childrenDrawable.end();
	while (it != end)
	{
		if ((*it)->RefreshSurface(x + this->_x, y + this->_y) == -1)
			return -1;
		y += (*it)->GetSurface()->h;
		++it;
	}
	return 0;
}

void	ID::Table::AddChild(ID::Drawable* _r)
{
	ID::TRow*		r;

	r = dynamic_cast<ID::TRow*>(_r);
	if (r == NULL)
		throw 1;
	this->Control::AddChild(r);
	this->__changed = true;
}

void	ID::Table::AddChild(ID::Control*)
{
}

int	ID::Table::DelChild(ID::Control*)
{
	return -1;
}

void	ID::Table::SetChange(bool b)
{
	this->__changed = b;
}

void	ID::Table::CalculColOffsets(void)
{
	std::vector<unsigned int>::iterator	itO;

	std::list<ID::Drawable*>::iterator	itR;
	std::list<ID::Drawable*>::iterator	endR;
	std::list<ID::Drawable*>::iterator	itC;
	std::list<ID::Drawable*>::iterator	endC;
	int					xOffset;

	this->__ResetColOffset();
	itR = this->GetChildrenDrawable()->begin();
	endR = this->GetChildrenDrawable()->end();
	xOffset = 0;
	while (itR != endR)
	{
		itO = this->_colOffset.begin();
		itC = (*itR)->GetChildrenDrawable()->begin();
		endC = (*itR)->GetChildrenDrawable()->end();
		while (itC != endC)
		{
			if ((*itC)->GetSurface()->w > *itO)
				*itO = (*itC)->GetSurface()->w;
			++itC;
			++itO;
		}
		++itR;
	}
	this->__changed = false;
}

std::vector<unsigned int>*	ID::Table::GetColOffsets(void)
{
	return &(this->_colOffset);
}

void	ID::Table::__ResetColOffset(void)
{
	std::vector<unsigned int>::iterator	it;
	std::vector<unsigned int>::iterator	end;

	it = this->_colOffset.begin();
	end = this->_colOffset.end();
	while (it != end)
	{
		(*it) = 0;
		++it;
	}
}

