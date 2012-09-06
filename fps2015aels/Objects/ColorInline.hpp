#ifndef Color_hpp
#define Color_hpp

inline GLuint	GetR(void)
{
	return (this->R);
}
inline GLuint	GetG(void)
{
	return (this->G);
}
inline GLuint	GetB(void)
{
	return (this->B);
}

inline void	SetR(int r)
{
	this->R = r;
}
inline void	SetG(int g)
{
	this->G = g;
}
inline void	SetB(int b)
{
	this->B = b;
}



#endif
