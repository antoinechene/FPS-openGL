#ifndef __EVENT_H__
#define __EVENT_H__

#ifndef	__MAKE_H
#include <stdint.h>
#endif
#include "Keymap.h"

namespace	ID
{
	typedef enum
	{
		EVENT_CLICK = 25,
		EVENT_DOUBLE_CLICK = 26,
		EVENT_CLICK_DOWN = 1,
		EVENT_CLICK_UP,
		EVENT_ENTER,
		EVENT_LEAVE,
		EVENT_MOTION,
		EVENT_KEY_UP,
		EVENT_KEY_DOWN,
		EVENT_FOCUS_ENTER,
		EVENT_FOCUS_LEAVE,
		EVENT_ENABLE_CHANGE,
		EVENT_SCREEN_CHANGE,
		EVENT_RESIZE,
		EVENT_QUIT,
		EVENT_USER_EVENT
	}	EVENT_TYPE;

	typedef struct
	{
		uint8_t		scancode;
		Key		sym;
		Mod		mod;
	}	Keysym;

	typedef struct
	{
		uint8_t		type;
		Mouse_Button	button;
		uint16_t	x;
		uint16_t	y;
	}		t_Click, t_DoubleClick, t_ClickDown, t_ClickUp;

	typedef struct
	{
		uint8_t		type;
	}		t_Enter, t_Leave;

	typedef struct
	{
		uint8_t		type;
		uint8_t		state;
		uint16_t	x;
		uint16_t	y;
		int16_t		x_rel;
		int16_t		y_rel;
	}		t_Motion;

	typedef struct
	{
		uint8_t		type;
		Keysym		keysym;
	}		t_KeyUp, t_KeyDown;

	typedef struct
	{
		uint8_t		type;
	}		t_FocusEnter, t_FocusLeave;

	typedef struct
	{
		uint8_t		type;
		bool		isEnable;
	}		t_EnableChange;

	typedef struct
	{
		uint8_t		type;
		bool		isOnScreen;
	}		t_ScreenChange;

	typedef struct
	{
		uint8_t		type;
		int		w;
		int		h;
	}		t_Resize;

	typedef struct
	{
		uint8_t		type;
	}		t_Quit;

	typedef union
	{
		uint8_t			type;
		t_Click			click;
		t_DoubleClick		doubleClick;
		t_ClickDown		clickDown;
		t_ClickUp		clickUp;
		t_Enter			enter;
		t_Leave			leave;
		t_Motion		motion;
		t_KeyUp			keyUp;
		t_KeyDown		keyDown;
		t_FocusEnter		focusEnter;
		t_FocusLeave		focusLeave;
		t_EnableChange		enableChange;
		t_ScreenChange		screenChange;
		t_Resize		resize;
		t_Quit			quit;
	}	Event;
};

#endif
