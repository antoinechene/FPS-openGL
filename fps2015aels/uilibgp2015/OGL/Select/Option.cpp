#include "Option.h"
#include "Select.h"
#include <string.h>

void	__id_optionClickDown(ID::Control* _o, ID::Event*, void*)
{
	ID::Option*	o;
	ID::Select*	s;

	o = (ID::Option*)_o;
	s = dynamic_cast<ID::Select*>(o->GetParent());
	if (s->GetOpen() == true)
	{
		s->SetFocusOption(o);
		s->SetOpen(false);
	}
	else
	{
		s->SetOpen(true);
	}
}

ID::Option::Option(int v, void* f, char* t, ID::Color* fg) : Drawable(strlen(t) * 9, 15), __value(v)
{
	this->__label = new ID::Label(f, t, fg);
	this->__label->SetParent(this);
	this->__label->SetPos(ID::REL_POS_CENTER);
	this->__label->SetCbClickDown(__id_optionClickDown, NULL);
	this->SetCbClickDown(__id_optionClickDown, NULL);
}

ID::Option::Option(const ID::Option& b) : Drawable(b)
{
}

ID::Option::~Option(void)
{
	delete[] this->__label;
}

int	ID::Option::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false ||
	    dynamic_cast<ID::Select*>(this->GetParent()) == NULL)
		return 0;
//	if (this->GetInvalidate() == true)
	{
//		this->_RefreshBackground();
		if (this->_surface->BlitSurface(x + this->_x,
						y + this->_y) == -1)
			return -1;
		if (this->__label != NULL)
		{
			if (this->__label->RefreshSurface(x + this->_x, y + this->_y) == -1)
				return -1;
		}
	}
	return 0;
}

void	ID::Option::SetLabel(ID::Label* label)
{
	if (this->__label != NULL)
		this->__label->SetParent(NULL);
	this->__label = label;
	this->__label->SetParent(this);
	this->__label->SetPos(ID::REL_POS_CENTER);
}

ID::Label*	ID::Option::GetLabel(void) const
{
	return this->__label;
}

void		ID::Option::SetLabelPos(int16_t x, int16_t y)
{
	this->__label->SetPos(x, y);
}

void		ID::Option::SetLabelPos(ID::REL_POS_TYPE rel_pos)
{
	this->__label->SetPos(rel_pos);
}

void		ID::Option::GetLabelPos(int16_t* x, int16_t* y) const
{
	this->__label->GetPos(x, y);
}

ID::REL_POS_TYPE	ID::Option::GetLabelRelPos(void) const
{
	return this->__label->GetRelPos();
}

int	ID::Option::GetValue(void) const
{
	return this->__value;
}

void	ID::Option::SetValue(int v)
{
	this->__value = v;
}

