#ifndef __TROW_H__
#define __TROW_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	TRow : public Drawable
	{
	public:
				TRow();
		virtual		~TRow(void);
		virtual int	ClickDown(Event*);
		virtual int	RefreshSurface(int x, int y);
		virtual void	AddChild(Drawable* o);
		virtual void	AddChild(Control* o);
		virtual int	DelChild(Drawable* o);
		virtual int	DelChild(Control* o);
		void		SetChange(bool);

	private:
		void	__AutoResize(void);
	};
}

#endif

