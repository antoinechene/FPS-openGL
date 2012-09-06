#include "Material.h"

Material::Material()
{
}

Material::~Material()
{
	size_t	i;
	size_t	size;

	delete [] this->Name;
	i = 0;
	size = this->TextureL.size();
	while (i < size)
	{
		delete this->TextureL[i];
		++i;
	}
}
