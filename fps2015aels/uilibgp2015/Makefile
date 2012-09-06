LIBRARY_NAME =	ID_glibrary.a
LIBRARY_HNAME=	ID_glibrary.h
LIBRARY_SRC = \
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
		Window/Window.cpp\
		Window/Window_Event.cpp\
		Window/Window_On.cpp\
		Main_Control/Main_Control.cpp\
\
		Button/Button.cpp\
		Button/Button_Image.cpp\
		Button/Button_Label.cpp\
\
		Textbox/Textbox.cpp\
		Label/Label.cpp\
		Container/Container.cpp\
\
		Menubar/Menubar.cpp\
		Menubar/Menubar_Event.cpp\
		Menubar/Menubar_On.cpp\
		Menu/Menu.cpp\
		Menu/Menu_On.cpp\
		Menu/Menu_Event.cpp\
\
		Draw_Geometry/Draw_Geometry_Line.cpp\
		Draw_Geometry/Draw_Geometry_Circle.cpp\
		Draw_Geometry/Draw_Geometry_Rect.cpp\
		Draw_Geometry/Draw_Geometry_Polygon.cpp\
		GLine/GLine.cpp\
		GCircle/GCircle.cpp\
		GRect/GRect.cpp\
		GPolygon/GPolygon.cpp\
\
	       	ID_Master_FCT.cpp\
	  	Wrapper/Wrapper_Event_SDL.cpp\
	  	Wrapper/Wrapper_Interface_SDL.cpp\
		Keyboard_Manager.cpp\
		Font.cpp\
		Surface.cpp

LDFLAGS	+= -lpthread -lSDL -lSDL_ttf -lefence
CXXFLAGS+= -Wall -W -Werror -D__SDL -g3
OBJ	= $(LIBRARY_SRC:.cpp=.o)
COMP_OBJ= $(COMPILE_SRC:.cpp=.o)
.cpp.o:
	g++ ${CXXFLAGS} -c $*.cpp -o $*.o

$(LIBRARY_NAME): $(OBJ)
	ar -q $(LIBRARY_NAME) $(OBJ)
	ranlib $(LIBRARY_NAME)

ID_h:
	cp -f stdlib_require.make_h $(LIBRARY_HNAME) && cpp -D__SDL -D__MAKE_H ./glib_require.make_h | sed '/^#/d' >> $(LIBRARY_HNAME) && echo "\n#endif" >> ${LIBRARY_HNAME}

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

