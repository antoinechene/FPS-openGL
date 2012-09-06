#ifndef Color_h
#define Color_h
#include <fbxsdk.h>
#include <GL/glut.h>
class Color
{
	public:
		Color();
		Color(KFbxPropertyDouble3 col);
		Color(int r, int g, int b);
		~Color();
		#include "ColorInline.hpp"
	private:
		GLuint	R;
		GLuint	G;
		GLuint	B;

};

#endif
