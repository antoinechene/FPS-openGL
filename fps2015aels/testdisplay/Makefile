NAME	=	test
SRC	=	main.cpp\
		DrawScene.cpp\
		GetPosition.cpp\
		GlFunctions.cpp\
		InitScene.cpp\
		SetCamera.cpp\
		Texture.cpp\
		Common.cpp
OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	=  -Wall -W -I/usr/include/GLTools/
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU -lGLTools -lfbxsdk-2012.2 -lm -lSDL_mixer 

$(NAME): $(OBJ)
	g++  -o $(NAME) $(CPPFLAGS) $(OBJ)  $(LDFLAGS)  ../Objects/Object.a ../Database/Database.a ../Sound/Sound.a
clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
