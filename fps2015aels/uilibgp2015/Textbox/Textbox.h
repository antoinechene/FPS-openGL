#ifndef __TEXTBOX_H__
#define __TEXTBOX_H__

#include "../Drawable/Drawable.h"
#include "../Colors.h"
#include "../Font.h"

void	__id_textboxClickDown(ID::Control* _tb, ID::Event*, void*);
void	__id_textboxKeyDown(ID::Control* _tb, ID::Event* e, void*);

namespace ID
{
	class	Textbox : public Drawable
	{
		friend void	::__id_textboxKeyDown(ID::Control*, ID::Event*, void*);
		public:
					Textbox(void);
					Textbox(uint16_t w, uint16_t h, uint32_t f,
						uint32_t rmask, uint32_t gmask,
						uint32_t bmask, uint32_t amask,
						const char* font_path, int font_size,
						Color* fg = (Color*)&COLOR_BLACK);
					Textbox(const ID::Textbox& button);
			virtual		~Textbox(void);
			void		SetText(char* text);
			char*		GetText(void);
			void		SetColor(Color fg);
			void		SetColor(uint32_t fg);
			Color		GetColor(void) const;
			void		SetPolice(Font::Police* police);
			Font::Police*	GetPolice(void) const;
			int		SetMaxLength(unsigned int maxLength);
			unsigned int	GetMaxLength(void) const;
			virtual int	RefreshToSurface(Surface* surface, int x, int y);

			virtual int	Action(Event*);
			void		SetCbAction(ID::cbEvent, void* data);
			ID::cbEvent	GetCbAction(void) const;

		protected:
			ID::cbEvent	_cbAction;
			void*		_cbActionData;

		private:
			unsigned int		__maxLength;
			char*			__text;
			Color			__color;
			Font::Police*		__police;

	};
};

#endif
