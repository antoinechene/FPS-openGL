#ifndef __CONTROL_H__
#define __CONTROL_H__

#ifndef	__MAKE_H
#include <list>
#endif
#include "../Event.h"

#ifdef	__SDL
#include "../Wrapper/Wrapper_Event_SDL.h"
#endif

namespace ID
{
	class	Drawable;
	class	Control;
	class	Wrapper_Event;
	typedef void (*cbEvent)(Control* sender, Event* event, void* data);
	typedef void (*cb)(Control* sender, void* data);
	class	Control
	{
	public:
				Control(void);
				Control(const Control&);
		virtual		~Control(void);
		Control&	operator=(const Control&);

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

		void		SetCbClick(cbEvent, void* data);
		void		SetCbDoubleClick(cbEvent, void* data);
		void		SetCbClickDown(cbEvent, void* data);
		void		SetCbClickUp(cbEvent, void* data);
		void		SetCbEnter(cbEvent, void* data);
		void		SetCbLeave(cbEvent, void* data);
		void		SetCbMotion(cbEvent, void* data);
		void		SetCbKeyUp(cbEvent, void* data, bool global = false);
		void		SetCbKeyDown(cbEvent, void* data, bool global = false);
		void		SetCbFocusEnter(cbEvent, void* data);
		void		SetCbFocusLeave(cbEvent, void* data);
		void		SetCbEnableChange(cbEvent, void* data);
		void		SetCbScreenChange(cbEvent, void* data);
		void		SetCbResize(cbEvent, void* data);
		void		SetCbQuit(cbEvent, void* data);
		void		SetCbUserEvent(cbEvent, void* data);
		void		SetCbUpdate(cb, void* data);

		cbEvent	GetCbClick(void) const;
		cbEvent	GetCbDoubleClick(void) const;
		cbEvent	GetCbClickDown(void) const;
		cbEvent	GetCbClickUp(void) const;
		cbEvent	GetCbEnter(void) const;
		cbEvent	GetCbLeave(void) const;
		cbEvent	GetCbMotion(void) const;
		cbEvent	GetCbKeyUp(void) const;
		cbEvent	GetCbKeyDown(void) const;
		cbEvent	GetCbFocusEnter(void) const;
		cbEvent	GetCbFocusLeave(void) const;
		cbEvent	GetCbEnableChange(void) const;
		cbEvent	GetCbScreenChange(void) const;
		cbEvent	GetCbResize(void) const;
		cbEvent	GetCbQuit(void) const;
		cbEvent	GetCbUserEvent(void) const;
		cb	GetCbUpdate(void) const;

		virtual void		AddChild(Control* control);
		virtual void		AddChild(Drawable* drawable);
		virtual int		DelChild(Control* control);
		virtual int		DelChild(Drawable* drawable);
		int			MoveChildFront(Drawable* drawable);
		int			MoveChildBack(Drawable* drawable);
		void			ClearChildren(void);
		void			SetParent(Drawable* drawable);
		Drawable*		GetParent(void) const;
		std::list<Control*>*	GetChildrenControl(void);
		std::list<Drawable*>*	GetChildrenDrawable(void);

		inline void		SetName(const char* name)
		{
			this->__name = name;
		}
		inline const char*	GetName(void) const
		{
			return this->__name;
		}

	protected:
		virtual bool		_OnClick(Event* event);
		virtual bool		_OnDoubleClick(Event* event);
		virtual bool		_OnClickDown(Event* event);
		virtual bool		_OnClickUp(Event* event);
		virtual bool		_OnEnter(Event* event);
		virtual bool		_OnLeave(Event* event);
		virtual bool		_OnMotion(Event* event);
		virtual bool		_OnKeyUp(Event* event);
		virtual bool		_OnKeyDown(Event* event);
		virtual bool		_OnFocusEnter(Event* event);
		virtual bool		_OnFocusLeave(Event* event);
		virtual bool		_OnEnableChange(Event* event);
		virtual bool		_OnScreenChange(Event* event);
		virtual bool		_OnResize(Event* event);
		virtual bool		_OnQuit(Event* event);
		virtual bool		_OnUserEvent(Event* event);

	protected:
		Drawable*		_parent;
		std::list<Control*>	_childrenControl;
		std::list<Drawable*>	_childrenDrawable;
		cbEvent			_cbClick;
		cbEvent			_cbDoubleClick;
		cbEvent			_cbClickDown;
		cbEvent			_cbClickUp;
		cbEvent			_cbEnter;
		cbEvent			_cbLeave;
		cbEvent			_cbMotion;
		cbEvent			_cbKeyUp;
		cbEvent			_cbKeyDown;
		cbEvent			_cbFocusEnter;
		cbEvent			_cbFocusLeave;
		cbEvent			_cbEnableChange;
		cbEvent			_cbScreenChange;
		cbEvent			_cbResize;
		cbEvent			_cbQuit;
		cbEvent			_cbUserEvent;
		cb			_cbUpdate;

	protected:
		void*		__cbClickData;
		void*		__cbDoubleClickData;
		void*		__cbClickDownData;
		void*		__cbClickUpData;
		void*		__cbEnterData;
		void*		__cbLeaveData;
		void*		__cbMotionData;
		void*		__cbKeyUpData;
		void*		__cbKeyDownData;
		void*		__cbFocusEnterData;
		void*		__cbFocusLeaveData;
		void*		__cbEnableChangeData;
		void*		__cbScreenChangeData;
		void*		__cbResizeData;
		void*		__cbQuitData;
		void*		__cbUserEventData;
		void*		__cbUpdateData;
		const char*	__name;
	};
};

#endif
