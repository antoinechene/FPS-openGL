#ifndef MaterialInline_hpp
#define MaterialInline_hpp

inline char*	GetName(void)
{
	return (this->Name);
}

inline	void	SetName(char* name)
{
	this->Name = new char[strlen(name)+ 1];
	strcpy(this->Name, name);
}

inline Color	GetAmbiamt(void)
{
	return (this->Ambient);
}

inline	void	SetAmbient(Color Amb)
{
	this->Ambient = Amb;
}

inline Color	GetDiffuse(void)
{
	return (this->Diffuse);
}

inline	void	SetDiffuse(Color Diff)
{
	this->Diffuse = Diff;
}

inline Color	GetSpecular(void)
{
	return (this->Specular);
}

inline	void	SetSpecular(Color Spec)
{
	this->Specular = Spec;
}

inline Color	GetEmissive(void)
{
	return (this->Emissive);
}

inline	void	SetEmissive(Color Em)
{
	this->Emissive = Em;
}

inline	float	GetOpacity(void)
{
	return (this->Opacity);
}

inline	void	SetOpacity(float Op)
{
	this->Opacity = Op;
}

inline	float	GetReflection(void)
{
	return (this->Reflection);
}

inline	void	SetReflection(float Ref)
{
	this->Reflection = Ref;
}

inline	float	GetShininess(void)
{
	return (this->Shininess);
}

inline	void	SetShininess(float Shi)
{
	this->Shininess = Shi;
}
inline	int	GetShadingModel(void)
{
	return (this->ShadingModel);
}

inline	void	SetShadingModel(int Shad)
{
	this->ShadingModel = Shad;
}

inline	std::vector<Texture*>*	GetTexture(void)
{
	return (&this->TextureL);
}

inline	void	AddTexture(Texture* tex)
{
	this->TextureL.push_back(tex);
}



#endif
