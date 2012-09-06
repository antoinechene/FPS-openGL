#ifndef	__MENU_H__
#define	__MENU_H__

#include "../Drawable/Drawable.h"
#include "../Button/Button_Label.h"
#include "../Font.h"
#include "../Event.h"
#include "../Colors.h"

namespace	ID
{
	enum	MENU_TYPE
	{
		MENU_VERTICAL = 1,
		MENU_HORIZONTAL = 2
	};

	enum	ALIGNMENT_TYPE
	{
		ALIGNMENT_TOP = 1,
		ALIGNMENT_LEFT = 1,
		ALIGNMENT_BOT = 2,
		ALIGNMENT_RIGHT = 2,
		ALIGNMENT_CENTER = 3
	};

	enum	SIDE_POSITION_TYPE
	{
		SIDE_POSITION_TOP = 1,
		SIDE_POSITION_BOT,
		SIDE_POSITION_LEFT,
		SIDE_POSITION_RIGHT
	};

	class	Menu : public Drawable
	{
		friend class	Menubar;
		public:
					Menu(uint16_t w, uint16_t h, uint32_t flags,
					     uint32_t rmask, uint32_t gmask,
					     uint32_t bmask, uint32_t amask,
					     const char* font_path, int font_size,
					     char* text, Color* color = (Color*)&COLOR_BLACK);
			virtual		~Menu(void);

			void		SetMenuType(MENU_TYPE menu_type);
			void		SetChildrenSidePosition(SIDE_POSITION_TYPE side_position_type);
			void		SetChildrenAlignment(ALIGNMENT_TYPE alignment_type);
			void		SetMustBeOnScreen(bool mustBeOnScreen);
			void		SetLabel(Label* label);

			MENU_TYPE		GetMenuType(void) const;
			std::list<Menu*>	GetChildrenMenu(void) const;
			SIDE_POSITION_TYPE	GetChildrenSidePosition(void) const;
			ALIGNMENT_TYPE		GetChildrenAlignment(void) const;
			bool			GetMustBeOnScreen(void) const;
			Label*			GetLabel(void) const;

			void		ShowAll();
			void		HideAll();

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

			int		ActionEvent(void);
			void		SetCbActionEvent(cbEvent, void* data);
			cbEvent		GetCbActionEvent(void);

			virtual void	AddChild(Menu* menu);
			virtual int	DelChild(Menu* menu);
			virtual	int	RefreshToSurface(Surface* surface, int x, int y);

		protected:
			void		_SetToReorganize(bool toReorganize);
			bool		_GetToReorganize(void);

			void		_Reorganize(void);
			int		_BlitToWindow(void);

			virtual bool	_OnClick(Event* event);
			virtual bool	_OnDoubleClick(Event* event);
			virtual bool	_OnClickDown(Event* event);
			virtual bool	_OnClickUp(Event* event);
			virtual bool	_OnEnter(Event* event);
			virtual bool	_OnLeave(Event* event);
			virtual bool	_OnMotion(Event* event);
			cbEvent		_cbActionEvent;

		protected:
			Label*		_label;

		private:
			void		__ReorganizeVertical(void);
			void		__ReorganizeHorizontal(void);
			int		__GetChildrenMaxWidth(void);
			int		__GetChildrenTotalWidth(void);
			int		__GetChildrenMaxHeight(void);
			int		__GetChildrenTotalHeight(void);
			void		__CalculChildrenSidePosition(int* x, int* y);
			void		__CalculChildrenAlignment(int* x, int* y,
								  int minX, int minY);

		private:
			MENU_TYPE		__menuType;
			std::list<Menu*>	__childrenMenu;
			SIDE_POSITION_TYPE	__childrenSidePosition;
			ALIGNMENT_TYPE		__childrenAlignment;
			bool			__mustBeOnScreen;
			bool			__toReorganize;
			void*			__cbActionEventData;
	};
};

#endif
