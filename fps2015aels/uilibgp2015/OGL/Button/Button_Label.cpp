#include "Button_Label.h"

ID::Button_Label::Button_Label(uint16_t w, uint16_t h) : Button(w, h),
							 __label(NULL)
{
}

ID::Button_Label::Button_Label(uint16_t w, uint16_t h,
			       void* font, char* label,
			       ID::Color* fg)  : Button(w, h)
{
	this->__label = new ID::Label(font, label, fg);
	this->__label->SetParent(this);
	this->__label->SetPos(ID::REL_POS_CENTER);
}

ID::Button_Label::Button_Label(const ID::Button_Label& b) : Button(b)
{
	this->__label = new ID::Label(*(b.__label));
	this->__label->SetParent(this);
}

ID::Button_Label::~Button_Label(void)
{
	delete this->__label;
}

void	ID::Button_Label::SetLabel(ID::Label* label)
{
	if (this->__label != NULL)
		this->__label->SetParent(NULL);
	this->__label = label;
	this->__label->SetParent(this);
	this->__label->SetPos(ID::REL_POS_CENTER);
}

ID::Label*	ID::Button_Label::GetLabel(void) const
{
	return this->__label;
}

void		ID::Button_Label::SetLabelPos(int16_t x, int16_t y)
{
	this->__label->SetPos(x, y);
}

void		ID::Button_Label::SetLabelPos(ID::REL_POS_TYPE rel_pos)
{
	this->__label->SetPos(rel_pos);
}

void		ID::Button_Label::GetLabelPos(int16_t* x, int16_t* y) const
{
	this->__label->GetPos(x, y);
}

ID::REL_POS_TYPE	ID::Button_Label::GetLabelRelPos(void) const
{
	return this->__label->GetRelPos();
}

int	ID::Button_Label::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
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

