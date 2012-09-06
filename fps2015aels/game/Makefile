NAME	=	fps
SRC	=	main.cpp\
		Game.cpp\
		../Objects/Display.cpp\
		../Objects/TGALoader.cpp\
		../map/Map.cpp\
		../EventHandler/EventHandler.cpp\
		../menu/Menu.cpp\
		../menu/FirstMenu.cpp\
		../HUD/Hud.cpp
OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	=  -Wall -W -I/usr/include/GLTools/ -g3 -O3 
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU -lGLTools -lfbxsdk-2012.2 -lm -lSDL_mixer -lSDL -lSDL_ttf -D__SDL


$(NAME): $(OBJ)
	g++  -o $(NAME) $(CPPFLAGS) $(OBJ)  $(LDFLAGS)  ../Resources/lib/Object.a ../Resources/lib/Database.a ../Resources/lib/Sound.a ../Resources/lib/ID_glibrary.a ../Resources/lib/HUD.a

clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
nosound: CPPFLAGS += -D_NO_SOUND
nosound: rebuild
pg: CPPFLAGS += -pg
pg: rebuild
