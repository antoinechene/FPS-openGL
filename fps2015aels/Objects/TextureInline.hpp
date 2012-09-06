#ifndef TextureInline_hpp
#define TextureInline_hpp

inline	char*	GetName(void)
{
	return (this->Name);
}

inline	void	SetName(char* Name)
{
	this->Name = new char[strlen (Name) + 1];
	strcpy(this->Name, Name);
}
inline char*	GetFileName(void)
{
	return (this->FileName);
}

inline void	SetFilename(char* filename)
{
	this->FileName = new char[strlen (filename) + 1];
	strcpy(this->FileName, filename);
}
inline	GLuint	GetID(void)
{
	return (this->id);
}

inline	void	SetID(GLint id)
{
	this->id = id;
}

inline	GLuint	GetTXTChan(void)
{
	return (this->txtchanel);
}

inline	void	SetTXTChanel(GLint Chan)
{
	this->txtchanel = Chan;
}

inline	GLuint	GetTXTUse(void)
{
	return (this->txtuse);
}

inline	void	SetTXTUse(GLint Use)
{
	this->txtuse = Use;
}

#endif
