#ifndef	__DRAWABLE_H__
#define	__DRAWABLE_H__

#include "../Wrapper/Wrapper_Event_SDL.h"
#include "../Control/Control.h"
#include "../Window/Window.h"
#include "../Surface.h"
#include "../Event.h"
#include "../Common.h"
#ifndef	__MAKE_H
#include <sys/time.h>
#endif

namespace ID
{
	enum	REL_POS_TYPE
	{
		REL_POS_NONE = 1,
		REL_POS_TOP = 2,
		REL_POS_BOT = 4,
		REL_POS_LEFT = 8,
		REL_POS_RIGHT = 16,
		REL_POS_CENTER = REL_POS_TOP | REL_POS_BOT | REL_POS_LEFT | REL_POS_RIGHT
	};

	class Drawable : public Control
	{
		public:
				Drawable(void);
				Drawable(uint16_t width, uint16_t height, uint32_t flags,
					 uint32_t rmask, uint32_t gmask,
					 uint32_t bmask, uint32_t amask);
				Drawable(const Drawable&);
		virtual		~Drawable(void);
		Drawable&	operator=(const Drawable&);

		virtual int	Click(Event* event);
		virtual	int	DoubleClick(Event* event);
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
#include "Drawable_inline.hpp"
/*
		void		SetOnScreen(bool visible);
		void		SetEnable(bool enable);
		void		SetInvalidate(bool invalidate);
		void		SetSurface(Surface* new_surface);
		void		SetPos(int16_t new_x, int16_t new_y);
		void		SetPos(REL_POS_TYPE relative_position);
		int		SetBackground(Surface* surface);
		int		SetBackground(Color* color);
		int		SetBackground(uint32_t color);
		void		SetVisibleRect(Rect* rect);
		void		SetBgRect(Rect* rect);
		int		SetBorderColor(Color* color);
		int		SetBorderColor(uint32_t color);
		void		SetBorder(Border* border);
		void		SetBorder(uint16_t all);
		void		SetBorder(uint16_t top, uint16_t bot,
					  uint16_t left, uint16_t right);

		bool		GetOnScreen(void) const;
		bool		GetEnable(void) const;
		bool		GetInvalidate(void) const;
		Surface*	GetSurface(void) const;
		void		GetPos(int16_t* x, int16_t* y) const;
		REL_POS_TYPE	GetRelPos(void) const;
		void		GetOffset(int* offset_x, int* offset_y) const;
		Color		GetBorderColor(void) const;
		Border		GetBorder(void) const;
		void		GetBorder(uint16_t* top, uint16_t* bot,
					  uint16_t* left, uint16_t* right);
		uint16_t	GetWidth(void) const;
		uint16_t	GetHeight(void) const;
		Rect*		GetVisibleRect(void) const;
		Rect*		GetBgRect(void) const;
		Window*		GetRealWindow(void);

		int		BlitSurface(Rect* rect, Surface* surface, int x, int y);
		virtual int	RefreshToSurface(Surface* surface, int x, int y);
		virtual int	Resize(uint16_t width, uint16_t height,
				       uint32_t flags = SDL_SWSURFACE | SDL_SRCALPHA,
				       uint32_t rmask = 0, uint32_t gmask = 0,
				       uint32_t bmask = 0, uint32_t amask = 0);

	protected:
		void		_RefreshBackground(void);
		virtual void	_SetInvalidate(bool invalidate);
		void		_AddUpdateRect(void);
		void		_RefreshOffset(void);
		void		_CalculRelativePosition(int16_t* x, int16_t* y);
		void		_PushClickEvent(Event* event);
		void		_PushDblClickEvent(Event* event);
		*/
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


	protected:
		Surface*	_surface;
		Surface*	_bgSurface;
		Color		_bgColor;
		bool		_onScreen;
		bool		_isEnable;
		bool		_isInvalidate;
		bool		_abstractParent;
		bool		_enableBg;
		REL_POS_TYPE	_relPos;
		int16_t		_x;
		int16_t		_y;
		Rect*		_visibleRect;
		Rect*		_bgRect;
		int16_t		_offset_x;
		int16_t		_offset_y;
		Color		_borderColor;
		Border		_border;

		uint16_t	_w;
		uint16_t	_h;
		struct timeval	_lastClickDown;
		struct timeval	_lastClick;
	};
}

#endif
