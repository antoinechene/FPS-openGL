#ifndef Map_h
#define Map_h
#include <iostream>
#include <vector>
#include <string.h>
class Object;
class Map
{
	public:
		Map(int id, const char* name, const char* filename);
		~Map();
		bool	Load();
		#include "MapInline.hpp"
	private:
		int 			id;
		char*			Name;
		char*			Filename;
		std::vector<Object*>	Obj;
};

#endif

