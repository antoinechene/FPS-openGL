#include "TGALoader.h"
#include <stdlib.h>
#include <iostream>

TGAReader::TGAReader()
{
}
TGAReader::~TGAReader()
{

}
bool	TGAReader::ReadFile(const char* filename, GLenum MinFilter, GLenum magFilter, GLenum wrapMode)
{
	GLbyte*		Bits;
	int		w;
	int		h;
	int		compo;
	GLenum		Format;


	Bits = NULL;
	Bits = gltReadTGABits(filename, &w, &h, &compo, &Format);
	if (Bits == NULL)
	{
		return (false);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, MinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, compo, w, h, 0, Format, GL_UNSIGNED_BYTE, Bits);

	free (Bits);
	if (MinFilter == GL_LINEAR_MIPMAP_LINEAR ||
	    MinFilter == GL_LINEAR_MIPMAP_NEAREST ||
	    MinFilter == GL_NEAREST_MIPMAP_LINEAR ||
	    MinFilter == GL_NEAREST_MIPMAP_NEAREST) 
		glGenerateMipmap(GL_TEXTURE_2D);

	return (true);



}

