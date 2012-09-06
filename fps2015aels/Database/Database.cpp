#include "../Tools/Buffer.h"
#include "Tools.h"
//#include <sys/stat.h>
#include <fcntl.h>
#include <GL/glut.h>
#include "Database.h"
//#include <iostream>
//#include <sys/types.h>
#include "Ammo_Model.h"
#include "Weapon_Model.h"
#include "Fire_Model.h"
#include "Charger_Model.h"
#include "Sound_Model.h"

Database::Database()
{
}

Database::~Database()
{
	std::vector<Weapon_Model*>::iterator	it;
	std::vector<Weapon_Model*>::iterator	end;
	std::vector<Ammo_Model*>::iterator	itA;
	std::vector<Ammo_Model*>::iterator	endA;

	it = this->__weapon_db.begin();
	end = this->__weapon_db.end();
	while (it != end)
	{
		delete *it;
		++it;
	}
	itA = this->__ammo_db.begin();
	endA = this->__ammo_db.end();
	while (itA != endA)
	{
		delete *itA;
		++itA;
	}
}

int	Database::Init()
{
	if (Init_Ammo_Db() == -1)
	{
		std::cout << "Ammo DB failed to load." << std::endl;
		return -1;
	}
	if (Init_Charger_Db() == -1)
	{
		std::cout << "Charger DB failed to load." << std::endl;
		return -1;
	}
	if (Init_Fire_Db() == -1)
	{
		std::cout << "fire DB failed to load." << std::endl;
		return -1;
	}
	if (Init_Weapon_Db() == -1)
	{
		std::cout << "Unit DB failed to load." << std::endl;
		return -1;
	}
	if (Init_Sound_Db() == -1)
	{
		std::cout << "Sound DB failed to load." << std::endl;
		return -1;
	}

	return (0);
}

int	Database::Init_Weapon_Db()
{
	Weapon_Model*	wm;
	int		fd;
	int		readed = 1;
	char**		tab;
	char*		line;
	Buffer		buf;

	buf.NewBuffer(512);
	fd = open("../Database/Weapon_DB", O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Weapon_DB cannot be found." << std::endl;
		return -1;
	}
	readed = buf.ReadEntry(fd, 512);
	line = buf.GetLine();
	delete line;
	while (readed != 0 && readed != -1)
	{
		line = buf.GetLine();
		while (line != NULL)
		{
			tab = id_str_to_word_tab_char(line, (char*)"\t");
			wm = new Weapon_Model(tab);
			if (wm == NULL)
				return -1;
			this->__weapon_db.push_back(wm);
			delete line;
			line = buf.GetLine();
		}
		readed = buf.ReadEntry(fd, 512);
	}
	std::cout << "Weapon_DB succesfully loaded" << std::endl;
	if (close(fd) != 0)
		return -1;
	buf.Clear();
	return (0);
}

int	Database::Init_Charger_Db()
{
	Charger_Model*	cm;
	int		fd;
	int		readed = 1;
	char**		tab;
	char*		line;
	Buffer		buf;

	buf.NewBuffer(512);
	fd = open("../Database/Charger_DB", O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Charger_DB cannot be found." << std::endl;
		return -1;
	}
	readed = buf.ReadEntry(fd, 512);
	line = buf.GetLine();
	delete line;
	while (readed != 0 && readed != -1)
	{
		line = buf.GetLine();
		while (line != NULL)
		{
			tab = id_str_to_word_tab_char(line, (char*)"\t");
			cm = new Charger_Model(tab);
			if (cm == NULL)
				return -1;
			this->__charger_db.push_back(cm);
			delete line;
			line = buf.GetLine();
		}
		readed = buf.ReadEntry(fd, 512);
	}
	std::cout << "Charger_DB succesfully loaded" << std::endl;
	if (close(fd) != 0)
		return -1;
	buf.Clear();
	return (0);
}

int	Database::Init_Ammo_Db()
{
	Ammo_Model*	am;
	int		fd;
	int		readed = 1;
	char**		tab;
	char*		line;
	Buffer		buf;

	buf.NewBuffer(512);
	fd = open("../Database/Ammo_DB", O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Ammo_DB cannot be found." << std::endl;
		return -1;
	}
	readed = buf.ReadEntry(fd, 512);
	line = buf.GetLine();
	delete line;
	while (readed != 0 && readed != -1)
	{
		line = buf.GetLine();
		while (line != NULL)
		{
			tab = id_str_to_word_tab_char(line, (char*)"\t");
			am = new Ammo_Model(tab);
			if (am == NULL)
				return -1;
			this->__ammo_db.push_back(am);
			delete line;
			line = buf.GetLine();
		}
		readed = buf.ReadEntry(fd, 512);
	}
	std::cout << "Ammo_DB succesfully loaded" << std::endl;
	if (close(fd) != 0)
		return -1;
	buf.Clear();
	return (0);
}

int	Database::Init_Fire_Db()
{
	Fire_Model*	fm;
	int		fd;
	int		readed = 1;
	char**		tab;
	char*		line;
	Buffer		buf;

	buf.NewBuffer(512);
	fd = open("../Database/Fire_DB", O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Fire_DB cannot be found." << std::endl;
		return -1;
	}
	readed = buf.ReadEntry(fd, 512);
	line = buf.GetLine();
	delete line;
	while (readed != 0 && readed != -1)
	{
		line = buf.GetLine();
		while (line != NULL)
		{
			tab = id_str_to_word_tab_char(line, (char*)"\t");
			fm = new Fire_Model(tab);
			if (fm == NULL)
				return -1;
			this->__fire_db.push_back(fm);
			delete line;
			line = buf.GetLine();
		}
		readed = buf.ReadEntry(fd, 512);
	}
	std::cout << "Fire_DB succesfully loaded" << std::endl;
	if (close(fd) != 0)
		return -1;
	buf.Clear();
	return (0);
}

int	Database::Init_Sound_Db()
{
	Sound_Model*	sm;
	int		fd;
	int		readed = 1;
	char**		tab;
	char*		line;
	Buffer		buf;

	buf.NewBuffer(512);
	fd = open("../Database/Sound_DB", O_RDONLY);
	if (fd == -1)
	{
		std::cout << "Sound_DB cannot be found." << std::endl;
		return -1;
	}
	readed = buf.ReadEntry(fd, 512);
	line = buf.GetLine();
	delete line;
	while (readed != 0 && readed != -1)
	{
		line = buf.GetLine();
		while (line != NULL)
		{
			tab = id_str_to_word_tab_char(line, (char*)"\t");
			sm = new Sound_Model(tab);
			if (sm == NULL)
				return -1;
			this->__sound_db.push_back(sm);
			delete line;
			line = buf.GetLine();
		}
		readed = buf.ReadEntry(fd, 512);
	}
	std::cout << "Sound_DB succesfully loaded" << std::endl;
	if (close(fd) != 0)
		return -1;
	buf.Clear();
	return (0);
}

Weapon_Model*	Database::Get_Weapon_Model(int id)
{
	std::vector<Weapon_Model*>::iterator	it;

	it = this->__weapon_db.begin();
	while (it != this->__weapon_db.end())
	{
		if ((*it)->Get_Id() == id)
			return ((*it));
		++it;
	}
	std::cout << "Cannot find Weapon Model for " << id << std::endl;
	return (0);
}

Charger_Model*	Database::Get_Charger_Model(int id)
{
	std::vector<Charger_Model*>::iterator	it;

	it = this->__charger_db.begin();
	while (it != this->__charger_db.end())
	{
		if ((*it)->Get_Id() == id)
			return ((*it));
		++it;
	}
	std::cout << "Cannot find Charger Model for " << id << std::endl;
	return (0);
}

Ammo_Model*	Database::Get_Ammo_Model(int id)
{
	std::vector<Ammo_Model*>::iterator	it;

	it = this->__ammo_db.begin();
	while (it != this->__ammo_db.end())
	{
		if ((*it)->Get_Id() == id)
			return ((*it));
		++it;
	}
	std::cout << "Cannot find Ammo Model for " << id << std::endl;
	return (0);
}

Fire_Model*	Database::Get_Fire_Model(int id)
{
	std::vector<Fire_Model*>::iterator	it;

	it = this->__fire_db.begin();
	while (it != this->__fire_db.end())
	{
		if ((*it)->Get_Id() == id)
			return ((*it));
		++it;
	}
	std::cout << "Cannot find Fire Model for " << id << std::endl;
	return (0);
}

Sound_Model*	Database::Get_Sound_Model(int id)
{
	std::vector<Sound_Model*>::iterator	it;

	it = this->__sound_db.begin();
	while (it != this->__sound_db.end())
	{
		if ((*it)->Get_Id() == id)
			return ((*it));
		++it;
	}
	std::cout << "Cannot find sound Model for " << id << std::endl;
	return (0);
}

