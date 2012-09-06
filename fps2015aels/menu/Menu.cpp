#include "Menu.h"


Menu::Menu()
{
}

Menu::~Menu()
{
	size_t	i;
	size_t	size;

	i = 0;
	size = this->list.size();
	while (i < size)
	{
		delete this->list[i];
		i ++;
	}
	i = 0;
	size = this->surface.size();
	while (i < size)
	{
		delete this->surface[i];
		i ++;
	}

}

void	Menu::Add_Win()
{
	int		size;
	int		i;
	ID::Env*	env;

	env = ID::Env::GetInstance();
	i = 0;
	size = this->list.size();
	while (i < size)
	{
		env->root.push_back(this->list[i]);
		i = i + 1;
	}
}

void	Menu::Rem_Win()
{
	int	size;
	int	i;
	ID::Env*	env;

	env = ID::Env::GetInstance();
	i = 0;
	size = this->list.size();
	while (i < size)
	{
		this->list[i]->SetOnScreen(false);
//		env->root.remove(this->list[i]);
		i = i + 1;
	}
//	env->root.clear();
}

void	Menu::AddWin()
{
	int	size;
	int	i;
	ID::Env*	env;

	env = ID::Env::GetInstance();
	i = 0;
	size = this->list.size();
	while (i < size)
	{
		this->list[i]->SetOnScreen(true);
//		env->root.remove(this->list[i]);
		i = i + 1;
	}
//	env->root.clear();
}



void	Menu::Add_Draw(ID::Drawable* d)
{
	this->list.push_back(d);
}

std::vector<ID::Drawable*>*	Menu::Get_List()
{
	return (&this->list);
}

void	Menu::Construct()
{
}

void	Menu::Animate(int sens)
{
	(void)sens;

}
