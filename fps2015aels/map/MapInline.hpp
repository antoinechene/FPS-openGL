#ifndef MapInline_hpp
#define MapInline_hpp

inline int	GetID(void)
{
	return (this->id);
}

inline void	SetID(int id)
{
	this->id = id;
}

inline char*	GetName(void)
{
	return (this->Name);
}

inline void	SetName(char* name)
{
	this->Name = new char[strlen(name)+ 1];
	strcpy(this->Name, name);
	this->Name[strlen(name)] = '\0';
}

inline char*	GetFilename(void)
{
	return (this->Filename);
}

inline void	SetFileName(char* filename)
{
	this->Filename = new char[strlen(filename)+ 1];
	strcpy(this->Filename, filename);
	this->Filename[strlen(filename)] = '\0';
}

inline void	AddObject(Object* obj)
{
	this->Obj.push_back(obj);
}

inline std::vector<Object*>*	GetObjectList(void)
{
	return (&this->Obj);
}

#endif
