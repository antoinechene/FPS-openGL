#ifndef Texture_h
#define Texture_h
#include <GL/glut.h>
#include <string.h>
class Texture
{
	public:
		Texture();
		~Texture();
		#include "TextureInline.hpp"
	private:
		char*	Name;
		char*	FileName;
		GLuint	id;
		GLint	txtchanel;
		GLint	txtuse;

};

#endif
