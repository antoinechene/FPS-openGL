NAME = ../Resources/lib/Sound.a

SRC =	Sounds_mix.cpp

OBJ = $(SRC:.cpp=.o)

CPPFLAGS = -Wall -W  -I/usr/include/GLTools/ -g3 -O3
LDFLAGS =  -lglut -lGL -lGLTools -lGLEW -lGLU -lSDL -lSDL_ttf  -D__SDL -DSHOW_DBG -lm -lSDL_mixer


$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	ranlib ./../Resources/lib/Sound.a

clean:
	rm -rf $(OBJ)

distclean: clean
	rm -rf $(NAME)

rebuild: distclean $(NAME)
