#ifndef __TCOL_H__
#define __TCOL_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	TCol : public Drawable
	{
	public:
				TCol(uint16_t width, uint16_t height,
				     unsigned short int rowspan = 1,
				     unsigned short int colspan = 1);
		virtual		~TCol(void);
		virtual int	ClickDown(Event*);
		virtual void	AddChild(Drawable* o);
		virtual int	DelChild(Drawable* o);
		unsigned short int	GetRowspan(void) const;
		unsigned short int	GetColspan(void) const;

	private:
		unsigned short int	__rowspan;
		unsigned short int	__colspan;
	};
}

#endif

