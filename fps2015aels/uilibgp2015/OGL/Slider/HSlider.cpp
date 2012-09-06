#include "HSlider.h"
#include "../Env.h"

#ifndef	__MAKE_H
#include <GL/glut.h>
#include <iostream>
#endif

ID::HSlider::HSlider(unsigned int w,
		     unsigned int h,
		     unsigned int fHB) : Drawable(w, h),
					 __bar(w, (((int)fHB != -1) ? fHB : 0)),
					 __forceHeightBar(fHB),
					 __offsetY(0),
					 __threshold(0.0f),
					 __realBarSpace(0)
{
	this->GetSurface()->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	this->__bar.GetSurface()->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	this->Control::AddChild(&(this->__bar));
}

ID::HSlider::~HSlider(void)
{
}

int	ID::HSlider::ClickDown(ID::Event* e)
{
	if (!this->_OnClickDown(e))
		return 0;

	float	offsetY = (float)(e->clickDown.y - this->_y - this->_offset_y) /
				 (float)this->__realBarSpace - this->__threshold;

	if (offsetY < 0.0f)
		offsetY = 0.0f;
	else if (offsetY > 1.0f)
		offsetY = 1.0;

	this->__bar.SetPos(0, offsetY * (float)this->__realBarSpace);
	this->__offsetY = offsetY * (float)(this->__heightLink -
					    this->GetSurface()->h);
	glutPostRedisplay();
	ID::Env::GetInstance()->SetDrawableFocused(this);
	gettimeofday(&(this->_lastClickDown), NULL); // Dont care if failed
	return 1;
}

int	ID::HSlider::Motion(ID::Event* e)
{
	if (!this->_OnMotion(e))
		return 0;

	float	offsetY = (float)(e->motion.y - this->_y - this->_offset_y) /
				 (float)this->__realBarSpace - this->__threshold;

	if (offsetY < 0.0f)
		offsetY = 0.0f;
	else if (offsetY > 1.0f)
		offsetY = 1.0;

	this->__bar.SetPos(0, offsetY * (float)this->__realBarSpace);
	this->__offsetY = offsetY * (float)(this->__heightLink -
					    this->GetSurface()->h);
	glutPostRedisplay();
	ID::Env::GetInstance()->SetDrawableEntered(this);
	return 1;
}

int	ID::HSlider::RefreshSurface(int x, int y)
{
	if (this->GetOnScreen() == false)
		return 0;

	if (this->BlitSurface(x + this->_x, y + this->_y) == -1)
		return -1;
	if (this->__bar.RefreshSurface(x + this->_x, y + this->_y) == -1)
		return -1;
	return 0;
}

void	ID::HSlider::AddChild(ID::Drawable*)
{
	throw 988;
}

void	ID::HSlider::AddChild(ID::Control*)
{
	throw 987;
}

bool	ID::HSlider::_OnClickDown(Event* e)
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

bool	ID::HSlider::_OnMotion(Event* e)
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

ID::Drawable*	ID::HSlider::GetBarSurface(void)
{
	return &(this->__bar);
}

void		ID::HSlider::SetHeightLink(unsigned int hL)
{
	if ((int)this->__forceHeightBar != -1)
		return ;
	this->__threshold = (float)this->GetSurface()->h /
			    (float)hL;
	this->__realBarSpace = this->GetSurface()->h -
			       this->__threshold * (float)this->GetSurface()->h;
	this->__heightLink = hL;
	this->__threshold /= 2.0f;
	this->__bar.GetSurface()->Resize(this->GetSurface()->w,
					 this->__threshold * 100.0f + 1);
	this->__bar.SetPos(0, 0);
	this->__offsetY = 0;
}

unsigned int	ID::HSlider::GetValue(void) const
{
	return this->__offsetY;
}

