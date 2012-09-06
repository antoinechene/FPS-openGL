#ifndef	__MENUBAR_H__
#define	__MENUBAR_H__

#include "../Drawable/Drawable.h"
#include "../Menu/Menu.h"

namespace	ID
{
	class	Menubar : public Drawable
	{
		public:
					Menubar(uint16_t w, uint16_t h, uint32_t flags,
						uint32_t rmask, uint32_t gmask,
						uint32_t bmask, uint32_t amask,
						REL_POS_TYPE relPos = REL_POS_TOP);
			virtual		~Menubar(void);

			void		SetOnScreen(bool visible);
			virtual void	AddChild(Menu* menu);
			virtual	int	RefreshToSurface(Surface* surface, int x, int y);

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

		protected:
			void			_Reorganize(void);
			virtual bool		_OnClick(ID::Event* event);
			virtual bool		_OnDoubleClick(ID::Event* event);
			virtual bool		_OnClickDown(ID::Event* event);
			virtual bool		_OnClickUp(ID::Event* event);
			virtual bool		_OnEnter(ID::Event* event);
			virtual bool		_OnLeave(ID::Event* event);
			virtual bool		_OnMotion(ID::Event* event);

		private:
			std::list<Menu*>	__childrenMenu;
	};
};

#endif
