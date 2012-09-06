#include "Env.h"
#include "Event.h"
#include "Drawable/Drawable.h"

#ifndef	NULL
#define	NULL	0
#endif

ID::Env::Env() : __focused(NULL), __entered(NULL)
{
}

ID::Env::~Env()
{
}

void		ID::Env::SetDrawableFocused(Drawable* d)
{
	ID::Event	e;

	if (this->__focused == d)
		return ;
	if (this->__focused != NULL)
	{
		e.type = ID::EVENT_FOCUS_LEAVE;
		this->__focused->FocusLeave(&e);
	}
	this->__focused = d;
	if (this->__focused != NULL)
	{
		e.type = ID::EVENT_FOCUS_ENTER;
		this->__focused->FocusEnter(&e);
	}
}

void		ID::Env::SetDrawableEntered(Drawable* d)
{
	ID::Event	e;

	if (this->__entered == d)
		return ;
	if (this->__entered != NULL)
	{
		e.type = ID::EVENT_LEAVE;
		this->__entered->Leave(&e);
	}
	this->__entered = d;
	if (this->__entered != NULL)
	{
		e.type = ID::EVENT_ENTER;
		this->__entered->Enter(&e);
	}
}

ID::Drawable*	ID::Env::GetDrawableFocused(void)
{
	return this->__focused;
}

ID::Drawable*	ID::Env::GetDrawableEntered(void)
{
	return this->__entered;
}

int		ID::Env::RefreshScreen(void)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		if ((*it)->RefreshSurface(0, 0) == -1)
			return -1;
		++it;
	}
	return 0;
}

void	ID::Env::ClickDown(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

//	if (this->__focused != NULL)
//		this->__focused->ClickDown(e);
	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->ClickDown(e);
		++it;
	}
}

void	ID::Env::ClickUp(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

//	if (this->__focused != NULL)
//		this->__focused->ClickUp(e);
	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->ClickUp(e);
		++it;
	}
}

void	ID::Env::Motion(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	if (this->__focused != NULL)
		this->__focused->Motion(e);
	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->Motion(e);
		++it;
	}
}

void	ID::Env::KeyDown(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	if (this->__focused != NULL)
		this->__focused->KeyDown(e);
/*	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->KeyDown(e);
		++it;
	}*/
}

void	ID::Env::KeyUp(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	if (this->__focused != NULL)
		this->__focused->KeyUp(e);
/*	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->KeyUp(e);
		++it;
	}*/
}

void	ID::Env::Resize(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->Resize(e);
		++it;
	}
}

void	ID::Env::Quit(ID::Event* e)
{
	std::list<ID::Drawable*>::iterator	it;
	std::list<ID::Drawable*>::iterator	end;

	it = this->root.begin();
	end = this->root.end();
	while (it != end)
	{
		(*it)->Quit(e);
		++it;
	}
}

