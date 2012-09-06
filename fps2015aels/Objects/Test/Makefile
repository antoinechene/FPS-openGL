NAME	=	test
SRC	=	test.cpp\

OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	+=	 -Wall -W 
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) libfbxsdk-2012.2-static.a
clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
