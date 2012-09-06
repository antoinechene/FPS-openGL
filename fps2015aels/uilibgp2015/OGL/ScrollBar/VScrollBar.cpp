#include "VScrollBar.h"
#include "../Env.h"

#ifndef	__MAKE_H
#include <GL/glut.h>
#include <iostream>
#endif

ID::VScrollBar::VScrollBar(unsigned int w,
			   unsigned int h,
			   unsigned int bW) : Drawable(w + bW, h),
					      __slider(bW, h),
					      __scaleRateX(0.0f),
					      __scaleRateY(0.0f),
					      __barWidth(bW),
					      __barSide(BARSIDE_RIGHT)
{
	this->Control::AddChild(&(this->__slider));
	if (this->__barSide == BARSIDE_RIGHT)
		this->__slider.SetPos(w + bW - this->__barWidth, 0);
	else
		this->__slider.SetPos(0, 0);
}

ID::VScrollBar::~VScrollBar(void)
{
}

int	ID::VScrollBar::ClickDown(ID::Event* e)
{
	if (!this->_OnClickDown(e) ||
	    this->_childrenDrawable.size() == 1)
		return 0;

	if (this->__slider.ClickDown(e))
		return 1;

	e->clickDown.y += this->__slider.GetValue();
	if (this->_childrenDrawable.back()->ClickDown(e))
	{
		std::cout << "Drawable\n";
		return 1;
	}
	ID::Env::GetInstance()->SetDrawableFocused(this);
	gettimeofday(&(this->_lastClickDown), NULL); // Dont care if failed
	return 1;
}

int	ID::VScrollBar::Motion(ID::Event* e)
{
	if (!this->_OnMotion(e) ||
	    this->_childrenDrawable.size() == 1)
		return 0;

	if (this->__slider.Motion(e))
		return 1;

	e->motion.y += this->__slider.GetValue();
	if (this->_childrenDrawable.back()->Motion(e))
		return 1;
	ID::Env::GetInstance()->SetDrawableEntered(this);
	return 1;
}

int	ID::VScrollBar::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false ||
	    this->_childrenDrawable.size() == 1)
		return 0;
	float	offset;

	glViewport(x + this->_x,
		   glutGet(GLUT_WINDOW_HEIGHT) - (y + this->_y + this->GetSurface()->h),
		   this->GetSurface()->w,
		   this->GetSurface()->h);
	glPushMatrix();
	glScalef(this->__scaleRateX, this->__scaleRateY, 0.0f);

	offset = (float)this->__slider.GetValue() / 100.0f *
		  (float)(this->_childrenDrawable.back()->GetSurface()->h -
		  this->GetSurface()->h);
	if (this->_childrenDrawable.
		  back()->
		  RefreshSurface(x + this->_x,
				 -offset + y + this->_y) == -1)
	{
		glPopMatrix();
		glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
		return -1;
	}
	glPopMatrix();
	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	if (this->__slider.RefreshSurface(x + this->_x, y + this->_y) == -1)
		return -1;
	return 0;
}

void	ID::VScrollBar::AddChild(ID::Drawable* r)
{
	if (this->_childrenDrawable.size() > 1)
		return ;
	this->Control::AddChild(r);
	this->__scaleRateX = glutGet(GLUT_WINDOW_WIDTH) / this->GetSurface()->w;
	this->__scaleRateY = glutGet(GLUT_WINDOW_HEIGHT) / this->GetSurface()->h;
	this->__slider.SetHeightLink(r->GetSurface()->h);
}

void	ID::VScrollBar::AddChild(ID::Control*)
{
	throw 987;
}

int	ID::VScrollBar::DelChild(ID::Control*)
{
	return -1;
}

bool	ID::VScrollBar::_OnClickDown(Event* e)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    this->_surface != NULL &&
	    e->clickDown.x >= this->_x + this->_offset_x &&
	    e->clickDown.y >= this->_y + this->_offset_y &&
	    e->clickDown.x < this->_x + this->_offset_x + this->_surface->w &&
	    e->clickDown.y < this->_y + this->_offset_y + this->_surface->h)
		return true;
	return false;
}

bool	ID::VScrollBar::_OnMotion(Event* e)
{
	if (this->GetOnScreen() == true && this->GetEnable() == true &&
	    this->_surface != NULL &&
	    e->motion.x >= this->_x + this->_offset_x &&
	    e->motion.y >= this->_y + this->_offset_y &&
	    e->motion.x < this->_x + this->_offset_x + this->_surface->w &&
	    e->motion.y < this->_y + this->_offset_y + this->_surface->h)
		return true;
	return false;
}

