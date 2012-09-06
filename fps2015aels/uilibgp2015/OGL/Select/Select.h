#ifndef __SELECT_H__
#define __SELECT_H__

#include "../Drawable/Drawable.h"

namespace ID
{
	class	Option;

	class	Select : public Drawable
	{
	public:
				Select(uint16_t width, uint16_t height);
		virtual		~Select(void);
		virtual int	ClickDown(Event*);
		virtual int	RefreshSurface(int x, int y);
		virtual void	AddChild(Drawable* o);
		virtual void	AddChild(Control* o);
		virtual int	DelChild(Drawable* o);
		virtual int	DelChild(Control* o);
		int		GetValue(void) const;
		void		SetFocusOption(Option* o);
		Option*		GetFocusOption(void) const;
		void		SetOpen(bool);
		bool		GetOpen(void) const;

		int	Change(void);
		void	SetCbChange(cbEvent, void* data);
		cbEvent	GetCbChange(void) const;

	protected:
		cbEvent	_cbChange;

	private:
		Option*	__focusOption;
		bool	__open;
		void*	__cbChangeData;
	};
}

#endif

