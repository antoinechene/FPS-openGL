#include "Button_Label.h"

ID::Button_Label::Button_Label(uint16_t w, uint16_t h, uint32_t f,
			       uint32_t rmask, uint32_t gmask,
			       uint32_t bmask, uint32_t amask) : Button(w, h, f, rmask, gmask,
									bmask, amask),
								 __label(NULL)
{
}

ID::Button_Label::Button_Label(uint16_t w, uint16_t h, uint32_t f,
			       uint32_t rmask, uint32_t gmask,
			       uint32_t bmask, uint32_t amask,
			       const char* font_path, int font_size, char* label,
			       ID::Color* fg)  : Button(w, h, f, rmask, gmask,
						       bmask, amask)
{
	this->__label = new ID::Label(font_path, font_size, label, fg);
	if (this->__label == NULL)
		throw 250;
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
	this->SetInvalidate(true);
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

int	ID::Button_Label::RefreshToSurface(Surface* s, int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;
	if (this->GetInvalidate() == true)
	{
		this->_RefreshBackground();
		if (this->__label != NULL)
		{
			if (this->__label->RefreshToSurface(this->GetSurface(), 0, 0) == -1)
				return -1;
		}
	}
	if (s != NULL &&
	    this->_surface->BlitSurface(this->_visibleRect, s,
					x + this->_x,
					y + this->_y) == -1)
		        return -1;
	this->SetInvalidate(false);
	return 0;
}

