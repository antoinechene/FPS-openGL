NAME = ./../Resources/lib/Database.a

SRC =	Ammo_Model.cpp\
	Tools.cpp\
	Database.cpp\
	Fire_Model.cpp\
	Player.cpp\
	Weapon.cpp\
	Weapon_Model.cpp\
	Charger.cpp\
	Charger_Model.cpp\
	Sound_Model.cpp

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -Wall -W  -I/usr/include/GLTools/ -g3
LDFLAGS =  -lglut -lGL -lGLTools -lGLEW -lGLU -lSDL -lSDL_ttf  -D__SDL -DSHOW_DBG -lfbxsdk-2012.2




$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	ranlib ./../Resources/lib/Database.a

clean:
	rm -rf $(OBJ)

distclean: clean
	rm -rf $(NAME)

rebuild: distclean $(NAME)
