#ifndef __TABLE_H__
#define __TABLE_H__

#include "../Drawable/Drawable.h"

#ifndef	__MAKE_H
#include <vector>
#endif

namespace ID
{
	class	TRow;

	class	Table : public Drawable
	{
	public:
				Table();
		virtual		~Table(void);
		virtual int	ClickDown(Event*);
		virtual int	RefreshSurface(int x, int y);
		virtual void	AddChild(Drawable* o);
		virtual void	AddChild(Control* o);
		virtual int	DelChild(Control* o);
		void		SetChange(bool);
		void		CalculColOffsets(void);
		std::vector<unsigned int>*	GetColOffsets(void);

	protected:
		std::vector<unsigned int>	_colOffset;

	private:
		void	__ResetColOffset(void);

	private:
		bool	__changed;
	};
}

#endif

