#ifndef __VSCROLLBAR_H__
#define __VSCROLLBAR_H__

#include "../Drawable/Drawable.h"
#include "../Slider/VSlider.h"

namespace ID
{
	enum	BARSIDE_TYPE
	{
		BARSIDE_LEFT = 0,
		BARSIDE_TOP = 0,
		BARSIDE_RIGHT = 1,
		BARSIDE_BOTTOM = 1,
	};

	class	VScrollBar : public Drawable
	{
	public:
				VScrollBar(unsigned int width,
					   unsigned int height,
					   unsigned int barWidth);
		virtual		~VScrollBar(void);
		virtual int	ClickDown(Event*);
		virtual int	Motion(Event*);
		virtual int	RefreshSurface(int x, int y);
		virtual void	AddChild(Drawable* o);
		virtual void	AddChild(Control* o);
		virtual int	DelChild(Control* o);

	protected:
		virtual bool	_OnClickDown(Event*);
		virtual bool	_OnMotion(Event*);

	private:
		VSlider		__slider;
		float		__scaleRateX;
		float		__scaleRateY;
		unsigned int	__barWidth;
		BARSIDE_TYPE	__barSide;
	};
}

#endif

