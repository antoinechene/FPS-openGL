#ifndef __VSLIDER_H__
#define __VSLIDER_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	VSlider : public Drawable
	{
	public:
				VSlider(unsigned int width,
				       unsigned int height,
				       unsigned int forceHeightBar = -1);
		virtual		~VSlider(void);
		virtual int	ClickDown(Event*);
		virtual int	Motion(Event*);
		virtual int	RefreshSurface(int x, int y);
		virtual void	AddChild(Drawable* o);
		virtual void	AddChild(Control* o);
		ID::Drawable*	GetBarSurface(void);
		void		SetHeightLink(unsigned int);
		unsigned int	GetValue(void) const;

	protected:
		virtual bool	_OnClickDown(Event*);
		virtual bool	_OnMotion(Event*);

	private:
		Drawable	__bar;
		unsigned int	__forceHeightBar;
		unsigned int	__heightLink;
		unsigned int	__offsetY;
		float		__threshold;
		unsigned int	__realBarSpace;
	};
}

#endif

