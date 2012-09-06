#ifndef MeshInline_hpp
#define MeshInline_hpp

inline Polygon**	GetPoly(void)
{
	return (this->pol);
}

inline GLfloat*	GetMatrice(void)
{
	return (this->Matrice);
}

inline void	SetMat(GLfloat*	mat)
{
	this->Matrice = mat;
}

inline Point**	GetControlPoint(void)
{
	return(this->ControlPoint);
}

inline GLint	GetTextureDiffIndex(void)
{
	return (this->TextureDiffIndex);
}

inline GLint	GetTextureAmbIndex(void)
{
	return (this->TextureAmbIndex);
}

inline GLint	GetTextureEmndex(void)
{
	return (this->TextureEmIndex);
}

inline GLint	GetTextureSpecularIndex(void)
{
	return (this->TextureSpecularIndex);
}

inline GLint	GetMatIndex(void)
{
	return (this->MatIndex);
}

inline std::vector<Material*>*	GetMat(void)
{
	return (&this->Mat);
}

#endif
