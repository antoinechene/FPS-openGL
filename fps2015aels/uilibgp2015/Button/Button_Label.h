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
				Button_Label(uint16_t width, uint16_t height, uint32_t flags,
					     uint32_t rmask, uint32_t gmask,
					     uint32_t bmask, uint32_t amask);
				Button_Label(uint16_t width, uint16_t height, uint32_t flags,
					     uint32_t rmask, uint32_t gmask,
					     uint32_t bmask, uint32_t amask,
					     const char* font_path, int font_size, char* label,
					     Color* fg = (Color*)&COLOR_BLACK);
				Button_Label(const Button_Label& button);
		virtual		~Button_Label(void);
		void		SetLabel(Label* label);
		Label*		GetLabel(void) const;
		void		SetLabelPos(int16_t x, int16_t y);
		void		SetLabelPos(REL_POS_TYPE rel_pos);
		void		GetLabelPos(int16_t* x, int16_t* y)const;
		REL_POS_TYPE	GetLabelRelPos(void)const;
		virtual int	RefreshToSurface(Surface* surface, int x, int y);

		private:
			ID::Label*	__label;
	};
}

#endif

