#ifndef	__WINDOW_H__
#define	__WINDOW_H__

#include "../Control/Control.h"
#include "../Surface.h"
#ifndef	__MAKE_H
#include <vector>
#include <iostream>
#endif

namespace ID
{
	class	Menubar;
	class	Menu;
	class	Main_Control;
	class	Drawable;
	class	Window : public Control
	{
		public:
					Window(uint16_t width, uint16_t height, uint32_t flags);
					Window(const Window& window);
			virtual		~Window(void);
			Window&		operator=(const Window& window);

			virtual int	Click(Event* event);
			virtual int	DoubleClick(Event* event);
			virtual int	ClickDown(Event* event);
			virtual int	ClickUp(Event* event);
			virtual int	Enter(Event* event);
			virtual int	Leave(Event* event);
			virtual int	Motion(Event* event);
			virtual int	KeyUp(Event* event);
			virtual int	KeyDown(Event* event);
			virtual int	FocusEnter(Event* event);
			virtual int	FocusLeave(Event* event);
			virtual int	EnableChange(Event* event);
			virtual int	ScreenChange(Event* event);
			virtual int	Resize(Event* event);
			virtual int	Quit(Event* event);
			virtual int	UserEvent(Event* event);

#include "Window_inline.hpp"
/*
			void		SetInvalidate(bool invalidate);
			int		SetBackground(Surface* surface);
			int		SetBackground(Color* color);
			int		SetBackground(uint32_t color);
*/
		public:
			void		SetDrawableFocused(Drawable* focused);
			void		SetDrawableEnter(Drawable* enter);
/*			void		SetToReorganize(bool toReorganize);

			Drawable*	GetMainControl(void) const;
			bool		GetInvalidate(void) const;
			uint16_t	GetWidth(void) const;
			uint16_t	GetHeight(void) const;
			Drawable*	GetDrawableFocused(void) const;
			Drawable*	GetDrawableEnter(void) const;
			Surface*	GetSurface(void);
			std::vector<Menu*>*	GetDeveloppedMenus(void);
			bool		GetToReorganize(void) const;
*/
			int		RefreshSurface(void);
/*			void		AddUpdate(Rect* rect);
			int		Update(void);
			int		Update(Rect* rect);
			int		Resize(uint16_t width, uint16_t height);
*/
			void		AddMenubar(Menubar* menubar);
			int		DelMenubar(Menubar* menubar);
			virtual void	AddChild(Control* control);
			virtual void	AddChild(Drawable* drawable);

		protected:

			int		_Reorganize(void);
/*			void		_RefreshBackground(void);
*/
		protected:
			virtual bool	_OnClick(Event* event);
			virtual bool	_OnDoubleClick(Event* event);
			virtual bool	_OnClickDown(Event* event);
			virtual bool	_OnClickUp(Event* event);
			virtual bool	_OnEnter(Event* event);
			virtual bool	_OnLeave(Event* event);
			virtual bool	_OnMotion(Event* event);
			virtual bool	_OnKeyUp(Event* event);
			virtual bool	_OnKeyDown(Event* event);
			virtual bool	_OnFocusEnter(Event* event);
			virtual bool	_OnFocusLeave(Event* event);
			virtual bool	_OnEnableChange(Event* event);
			virtual bool	_OnScreenChange(Event* event);
			virtual bool	_OnResize(Event* event);
			virtual bool	_OnQuit(Event* event);
			virtual bool	_OnUserEvent(Event* event);

		private:
			Surface			__window;
			Main_Control*		__mainControl;
			bool			__isInvalidate;
			bool			__enableBg;
			Surface*		__bgSurface;
			Color			__bgColor;
			Drawable*		__drawableFocused;
			Drawable*		__drawableEnter;
			std::vector<Rect>	__updateRects;
			bool			__fullscreenUpdate;
			bool			__toReorganize;
			std::vector<Menu*>	__developpedMenus;
	};
}

#endif

