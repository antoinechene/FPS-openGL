#ifndef Display_h
#define Display_h
#include <iostream>
#include <vector>
#include "../uilibgp2015/OGL/ID_glibrary.h"

class Object;
class Game;
class Menu;
class HUD;
class Display : public ID::Singleton<Display>
{

	friend class ID::Singleton<Display>;
	public:
				Display();
				~Display();
		int		Init(int argc, char** argv);
		static void	ReshapeFunc(int w, int h);
		static void	RenderScene(void);
	//	static void	clean(void);
		void		ApllyMat(Object* obj);
		static void	MouseFunc(int button, int state, int, int);
		static void	PassiveMotionFunc(int x, int y);
		static void	KeyboardUpFunc(unsigned char key, int, int);
		static void	KeyboardFunc(unsigned char key, int, int);
		static void	TimerFunc(int);
		static void	MoveWorld(GLfloat dt);
		void		Disable3D(void);
		void		Enable3D(void);
		void		InitMenu(void);

		static void	Exit(void);
	public:
		Game*			game;
		std::vector<Menu*>	menu;
		bool			InGame;
		HUD*			hud;
		int			width;
		int			height;
	private:
};

#endif
