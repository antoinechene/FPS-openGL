#ifndef TGAReader_h
#define TGAReader_h

#include <GLTools.h>
#include <GL/glut.h>
#include <GL/glew.h>
#include <GL/gl.h>

//#include <GL/glut.h>
class TGAReader
{
	public:
		TGAReader();
		~TGAReader();
		bool	ReadFile(const char* filename, GLenum MinFilter, GLenum magFilter, GLenum wrapMode);

	private:

};

#endif
