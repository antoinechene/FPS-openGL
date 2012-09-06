#ifndef __AMMO_MODEL_H__
#define __AMMO_MODEL_H__
#include <GL/glut.h>

class Ammo_Model
{
	public:
		Ammo_Model(char** data);
		~Ammo_Model();
		int	Get_Id();
		void	Set_Id(int id);
//		Object*	Get_Object();
//		void	Set_Object(Object*);
		GLfloat	Get_Speed_Ammo();
		void	Set_Speed_Ammo(GLfloat);
		GLfloat	Get_Area_Effect();
		void	Set_Area_Effect(GLfloat);
		GLfloat	Get_Speard();
		void	Set_Speard(GLfloat);
		GLfloat	Get_Fire_Rate();
		void	Set_Fire_Rate(GLfloat);
	private:
		int	__id;
//		Object*	__ammo;
		GLfloat	__speed_ammo;
		GLfloat	__area_effect;
		GLfloat	__speard;
		GLfloat	__fire_rate;
};

#endif
