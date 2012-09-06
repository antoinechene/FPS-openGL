#ifndef __OPTION_H__
#define __OPTION_H__

#include "../Drawable/Drawable.h"
#include "../Label/Label.h"

namespace ID
{
	class	Option : public Drawable
	{
	public:
				Option(int value,
				       void* font, char* text,
				       Color* fg = (Color*)&COLOR_BLACK);
				Option(const Option& button);
		virtual		~Option(void);
		virtual int	RefreshSurface(int x, int y);
		void		SetLabel(Label* label);
		Label*		GetLabel(void) const;
		void		SetLabelPos(int16_t x, int16_t y);
		void		SetLabelPos(REL_POS_TYPE);
		void		GetLabelPos(int16_t* x, int16_t* y) const;
		REL_POS_TYPE	GetLabelRelPos(void) const;
		int		GetValue(void) const;
		void		SetValue(int);

	private:
		int	__value;
		Label*	__label;
	};
}

#endif

