#ifndef __HUD_H__
#define __HUD_H__

#include "../uilibgp2015/OGL/ID_glibrary.h"
class HUD
{
	public:
		HUD();
		~HUD();
		void	Init(Player*);
		void	Init_All(Player*, Game*);
		void	Init_Ammo1();
		void	Init_Ammo2();
		void	Init_Charger1();
		void	Init_Charger2();
		void	Init_Life();
		void	Init_Frag();
		void	Init_Time(Game*);
		void	Set_Ammo1(int);
		void	Set_Ammo2(int);
		void	Set_Charger1(int);
		void	Set_Charger2(int);
		void	Set_Life(int);
		void	Set_Frag(int);
		void	Set_Time(int);
	private:
		ID::Drawable*	hud;
		ID::Drawable*	avatar;
		ID::Drawable*	ammo1[3];
		ID::Drawable*	ammo2[3];
		ID::Drawable*	charger1[2];
		ID::Drawable*	charger2[2];
		ID::Drawable*	life[3];
		ID::Drawable*	frag[2];
		ID::Drawable*	time[3];
		Player*		player;
};

#endif
