#ifndef __BUTTON_LABEL_H__
#define __BUTTON_LABEL_H__

#include "Button.h"
#include "../Label/Label.h"
#include "../Common.h"
#include "../Colors.h"

namespace ID
{
	class	Button_Label : public Button
	{
		public:
				Button_Label(uint16_t width, uint16_t height);
				Button_Label(uint16_t width, uint16_t height,
					     void* font, char* label,
					     Color* fg = (Color*)&COLOR_BLACK);
				Button_Label(const Button_Label& button);
		virtual		~Button_Label(void);
		void		SetLabel(Label* label);
		Label*		GetLabel(void) const;
		void		SetLabelPos(int16_t x, int16_t y);
		void		SetLabelPos(REL_POS_TYPE rel_pos);
		void		GetLabelPos(int16_t* x, int16_t* y)const;
		REL_POS_TYPE	GetLabelRelPos(void)const;
		virtual int	RefreshSurface(int x, int y);

		private:
			ID::Label*	__label;
	};
}

#endif

