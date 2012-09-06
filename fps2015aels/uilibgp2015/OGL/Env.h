#ifndef	__ENV_H__
#define	__ENV_H__

#include "Singleton.hpp"
#include "Event.h"

#ifndef	__MAKE_H
#include <list>
#endif

namespace	ID
{
	class	Drawable;

	class	Env : public ID::Singleton<Env>
	{
		friend class	ID::Singleton<Env>;
	public:
		void		SetDrawableFocused(Drawable*);
		void		SetDrawableEntered(Drawable*);
		Drawable*	GetDrawableFocused(void);
		Drawable*	GetDrawableEntered(void);
		int		RefreshScreen(void);
		void		ClickDown(ID::Event*);
		void		ClickUp(ID::Event*);
		void		Motion(ID::Event*);
		void		KeyDown(ID::Event*);
		void		KeyUp(ID::Event*);
		void		Resize(ID::Event*);
		void		Quit(ID::Event*);

	public:
		std::list<Drawable*>	root;

	private:
		Env();
		~Env();

	private:
		Drawable*	__focused;
		Drawable*	__entered;
	};
};

#endif
