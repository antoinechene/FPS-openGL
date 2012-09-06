#ifndef __BUTTON_IMAGE_H__
#define __BUTTON_IMAGE_H__

#include "Button.h"
#include "../Surface.h"

namespace ID
{
	class	Button_Image : public Button
	{
	public:
				Button_Image(uint16_t w, uint16_t h);
				Button_Image(const char* image_path);
				Button_Image(const Button_Image& button_image);
		virtual		~Button_Image(void);
		void		SetImage(Surface* surface);
		Surface*	GetImage(void) const;
		void		SetImagePosition(int x, int y);
		int		SetImageVisible(Rect* rect);
		void		GetImageVisible(Rect* rect) const;
		virtual int	RefreshSurface(int x, int y);
	private:
		int		__imgX;
		int		__imgY;
	};
}

#endif

