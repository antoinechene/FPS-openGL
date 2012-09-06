NAME	=	HUD/id_fps
SRC	=	HUD/main.cpp\
		HUD/Game.cpp\
		HUD/Hud.cpp\
		Objects/Display.cpp\
		Objects/TGALoader.cpp\
		map/Map.cpp\
		EventHandler/EventHandler.cpp\
		PhysicEngine/Physic.cpp\
		menu/Menu.cpp\
		menu/FirstMenu.cpp\
		menu/ServeurMenu.cpp\
		menu/Option_Menu.cpp\
		PhysicEngine/Octree.cpp
OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	=  -Wall -W -I/usr/include/GLTools/
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU -lGLTools -lfbxsdk-2012.2 -lm -lSDL_mixer -lSDL -lSDL_ttf -D__SDL


$(NAME): $(OBJ)
	g++  -o $(NAME) $(CPPFLAGS) $(OBJ)  $(LDFLAGS)  Resources/lib/Object.a  Resources/lib/ID_glibrary.a NetworkHandler/libnetworkhandler.a Resources/lib/Database.a  Resources/lib/Sound.a 
clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
