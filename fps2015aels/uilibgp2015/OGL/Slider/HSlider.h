#ifndef __HSLIDER_H__
#define __HSLIDER_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	HSlider : public Drawable
	{
	public:
				HSlider(unsigned int width,
				       unsigned int height,
				       unsigned int forceHeightBar = -1);
		virtual		~HSlider(void);
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

