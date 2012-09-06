#include "Texture.h"

Texture::Texture()
{
	this->id = -1;
}

Texture::~Texture()
{
	delete [] this->Name;
	delete [] this->FileName;
}
