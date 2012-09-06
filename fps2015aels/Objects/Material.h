#ifndef Material_h
#define Material_h
#include "Color.h"
#include "Texture.h"
#include <iostream>
#include <vector>

class Material
{
	public:
		Material();
		~Material();
		#include "MaterialInline.hpp"
	private:
		char*			Name;
		Color			Ambient;
		Color			Diffuse;
		Color			Specular;
		Color			Emissive;
		float			Opacity;
		float			Reflection;
		float			Shininess;
		int			ShadingModel;
		std::vector<Texture*>	TextureL;

};
#endif
