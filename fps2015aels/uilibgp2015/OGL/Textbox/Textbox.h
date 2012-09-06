#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "../Drawable/Drawable.h"
#include "../Colors.h"
#include "../Font.h"

void	__id_textboxClickDown(ID::Control* _tb, ID::Event*, void*);
void	__id_textboxKeyDown(ID::Control* _tb, ID::Event*, void*);

namespace ID
{
	class	Textbox : public Drawable
	{
		friend void	::__id_textboxKeyDown(ID::Control*, ID::Event*, void*);
		public:
					Textbox(void);
					Textbox(uint16_t w, uint16_t h,	void* font,
						Color* fg = (Color*)&COLOR_BLACK);
					Textbox(const Textbox& button);
			virtual		~Textbox(void);
			void		SetText(char* text);
			char*		GetText(void);
			void		SetColor(Color fg);
			void		SetColor(uint32_t fg);
			Color		GetColor(void) const;
			void		SetFont(void* font);
			void*		GetFont(void) const;
			int		SetMaxLength(unsigned int maxLength);
			unsigned int	GetMaxLength(void) const;
			virtual int	RefreshSurface(int x, int y);

			virtual int	Action(Event*);
			void		SetCbAction(cbEvent, void* data);
			cbEvent		GetCbAction(void) const;

		protected:
			cbEvent	_cbAction;
			void*	_cbActionData;

		private:
			unsigned int	__maxLength;
			char*		__text;
			Color		__color;
			void*		__font;

	};
};

#endif
