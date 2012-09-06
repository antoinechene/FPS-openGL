LIBRARY_NAME =	ID_glibrary.a
LIBRARY_HNAME=	ID_glibrary.h
LIBRARY_SRC = \
	       	ID_Master_FCT.cpp\
	  	Wrapper/Wrapper_Interface_OGL.cpp\
		Env.cpp\
		Keyboard_Manager.cpp\
		Texture_Manager.cpp\
		targa.cpp\
		Font.cpp\
		Surface.cpp\
\
		Select/Select.cpp\
		Select/Option.cpp\
		Table/Table.cpp\
		Table/TRow.cpp\
		Table/TCol.cpp\
		ScrollBar/VScrollBar.cpp\
		Slider/HSlider.cpp\
		Slider/VSlider.cpp\
	      	Button/Button_Label.cpp\
		Label/Label.cpp\
		Textbox/Textbox.cpp\
	  	Control/Control.cpp\
	  	Control/Control_Get.cpp\
	  	Control/Control_Set.cpp\
	  	Control/Control_Event.cpp\
	 	Control/Control_On.cpp\
\
		Drawable/Drawable.cpp\
		Drawable/Drawable_Event.cpp\
		Drawable/Drawable_On.cpp\
\
		Button/Button.cpp\


CXX	= clang++
LDFLAGS	+= -lpthread -lSDL -lSDL_ttf -lefence -lglut -lGLU -lGLTools -lGLEW -lGL
CXXFLAGS+= -Wall -W -Werror -D__OGL -g3
OBJ	= $(LIBRARY_SRC:.cpp=.o)
COMP_OBJ= $(COMPILE_SRC:.cpp=.o)
.cpp.o:
	$(CXX) ${CXXFLAGS} -c $*.cpp -o $*.o

$(LIBRARY_NAME): $(OBJ)
	ar -q $(LIBRARY_NAME) $(OBJ)
	ranlib $(LIBRARY_NAME)

ID_h:
	cp -f stdlib_require.make_h $(LIBRARY_HNAME) && cpp -D__OGL -D__MAKE_H ./glib_require.make_h | sed '/^#/d' >> $(LIBRARY_HNAME) && echo "\n#endif" >> ${LIBRARY_HNAME}

clean:
	rm -f ${OBJ}

distclean: clean
	rm -f $(LIBRARY_NAME)
	rm -f ${LIBRARY_HNAME}

rebuild: distclean $(LIBRARY_NAME)

prod:	distclean ID_h $(LIBRARY_NAME)
	make clean

debug:	CXXFLAGS += -DSHOW_DBG
debug:	rebuild

debug1:	CXXFLAGS += -D__DEBUG
debug1:	debug

debug2:	LDFLAGS += -lefence
debug2:	debug1

debug3:	CXXFLAGS += -pg
debug3:	LDFLAGS += -pg
debug3:	debug2

