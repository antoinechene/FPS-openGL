NAME	=	test
SRC	=	main.cpp\
		Menu.cpp

OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	=  -Wall -W -I/usr/include/GLTools/
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU -lGLTools -lfbxsdk-2012.2 -lm -lSDL_mixer -lSDL -lSDL_ttf -D__SDL

$(NAME): $(OBJ)
	g++  -o $(NAME) $(CPPFLAGS) $(OBJ)  $(LDFLAGS)   ../uilibgp2015/OGL/ID_glibrary.a
clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
