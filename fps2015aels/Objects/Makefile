NAME	=	./../Resources/lib/Object.a
SRC	=	Object.cpp\
		SolidObj.cpp\
		PhysObj.cpp\
		NewtonObj.cpp\
		Ball.cpp\
		Vec3f.cpp\
		HitBox.cpp\
		EventObj.cpp\
		StaticObj.cpp\
		GhostObj.cpp\
		Light.cpp\
		Sun.cpp\
		Camera.cpp\
		FBXLoader.cpp\
		Mesh.cpp\
		Shader/Tools.cpp\
		Point.cpp\
		Vec2f.cpp\
		Texture.cpp\
		Material.cpp\
		Color.cpp\
		Polygon.cpp\
		Plane.cpp\
		GetPosition.cpp\
		Scene.cpp
OBJ	=	$(SRC:.cpp=.o)
CPPFLAGS	= -Wall -W -I/usr/include/GLTools/ -O3
LDFLAGS 	= -lglut -lGL -lGLEW -lGLU -lGLTools -lfbxsdk-2012.2 

$(NAME): $(OBJ)
	ar r $(NAME) $(OBJ)
	ranlib ./../Resources/lib/Object.a

clean:
	rm -rf $(OBJ)
distclean: clean
	rm -rf $(NAME)
rebuild: distclean $(NAME)
debug: CPPFLAGS += -g3
debug: rebuild
only: rebuild
	rm -rf $(OBJ)
