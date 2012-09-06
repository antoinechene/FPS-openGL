#ifndef __BUTTON_IMAGE_H__
#define __BUTTON_IMAGE_H__

#include "Button.h"
#include "../Surface.h"

namespace ID
{
	class	Button_Image : public Button
	{
	public:
				Button_Image(uint16_t w, uint16_t h, uint16_t f,
					     uint32_t rmask, uint32_t gmask,
					     uint32_t bmask, uint32_t amask);
				Button_Image(const char* image_path);
				Button_Image(const Button_Image& button_image);
		virtual		~Button_Image(void);
		void		SetImage(Surface* surface);
		Surface*	GetImage(void) const;
		void		SetImagePosition(int x, int y);
		int		SetImageVisible(Rect* rect);
		void		GetImageVisible(Rect* rect) const;
		virtual int	RefreshToSurface(Surface* surface, int x, int y);
	private:
		Surface*	__image;
		int		__imgX;
		int		__imgY;
		Rect*		__imgRect;
	};
}

#endif

