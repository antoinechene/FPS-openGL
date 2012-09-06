#ifndef PointInline_hpp
#define PointInline_hpp

inline Vec3f	GetPoint(void)
{
	return (this->P);
}

inline Vec3f	GetNormal(void)
{
	return (this->N);
}

inline Vec2f	GetUV(void)
{
	return (this->UV);
}

inline void	SetPoint(Vec3f P)
{
	this->P = P;
}

inline void	SetNormal(Vec3f N)
{
	this->N = N;
}
inline void	SetUV(Vec2f UV)
{
	this->UV = UV;
}

inline void	SetPoint(float x, float y, float z)
{
	this->P[0] = x;
	this->P[1] = y;
	this->P[2] = z;

}

inline void	SetNormal(float n1, float n2, float n3)
{
	this->N[0] = n1;
	this->N[1] = n2;
	this->N[2] = n3;
}

inline void	SetUV(float uv1, float uv2)
{
	this->UV[0] = uv1;
	this->UV[1] = uv2;
}



#endif
