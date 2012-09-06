//#include <string.h>
//#include <stdio.h>
//#include <iostream>
#include <GL/glut.h>
#include "Sounds_mix.h"
#include "../Database/Database.h"
#include "../Database/Sound_Model.h"



Sounds::Sounds(void): theme(_theme), alive(_alive), volume(128), volume_sound(218), _alive(true)
{

}

Sounds::~Sounds(void)
{
}

bool	Sounds::init(void)
{
	Database*	database;
	unsigned int	i = 0;

	database = Database::GetInstance();
	SDL_Init(SDL_INIT_EVERYTHING);
//	MIX_EFFECTSMAXSPEED = "MIX_EFFECTSMAXSPEED";
	if (Mix_OpenAudio(44200, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
	{
		std::cout << "Fatal Audio Error: " << SDL_GetError() << std::endl;
		return true;
	}
	Mix_AllocateChannels(2);
	while (i < database->__sound_db.size())
	{
		if (database->__sound_db[i]->Get_Type() == 1)
			this->LoadWAV(database->__sound_db[i]->Get_File());
		if (database->__sound_db[i]->Get_Type() == 0)
			this->LoadMUS(database->__sound_db[i]->Get_File());
		++i;
	}

//	if (this->LoadWAV("test.wav"))
//		throw 801;
//	if (this->LoadWAV("pause.wav"))
//		throw 805;
//	if (this->LoadMUS("SHA.mp3"))
//		throw 802;
//	if (this->LoadMUS("WDY.mp3"))
//		throw 803;
//	if (this->LoadMUS("DRS.mp3"))
//		throw 804;
	return false;
}

bool	Sounds::LoadWAV(const char* path)
{
	Mix_Chunk*	sound;

	sound = Mix_LoadWAV(path);
	if (sound == NULL)
	{
		std::cout << "Error LoadWAV: " << path << std::endl;
	}
	this->sounds.push_back(sound);
	return false;
}

bool	Sounds::LoadMUS(const char* path)
{
	Mix_Music*	song;

	song = Mix_LoadMUS(path);
	if (song == NULL)
	{
		std::cout << "Error LoadMUS: " << path << std::endl;
	}
	this->songs.push_back(song);
	return false;
}

void	Sounds::play_sound(int key)
{
//	if (key >= SOUND_OFF || key < SOUND_THEME_MENU)
//		return;
	if (Mix_Paused(1) == 0)
	{
		if (Mix_PlayChannel(1, this->sounds[key], 0) == -1)
		{
			std::cout << "faileuh" << this->sounds[key] << std::endl;
			return;
		}
	}
//	Mix_SetPosition(MIX_DEFAULT_CHANNELS, 0, 0);
}

void	Sounds::set_theme(int key)
{
//	if (key >= SONG_OFF || key < SONG_SHA)
//		return;
	this->_theme = key;
	if (Mix_PausedMusic() != 1)
	{
		if (Mix_PlayMusic(this->songs[key], -1) == -1)
		{
			std::cout << "Faileuh pour la musiqueuh" << std::endl;
		}
	}
}

void	Sounds::stop_audio_player(void)
{
	std::vector<Mix_Chunk*>::iterator	itC;
	std::vector<Mix_Chunk*>::iterator	endC;
	std::vector<Mix_Music*>::iterator	itM;
	std::vector<Mix_Music*>::iterator	endM;

	itC = this->sounds.begin();
	endC = this->sounds.end();
	itM = this->songs.begin();
	endM = this->songs.end();

	while (itC != endC)
	{
		Mix_FreeChunk(*itC);
		++itC;
	}
	while (itM != endM)
	{
		Mix_FreeMusic(*itM);
		++itM;
	}
	this->_alive = false;
	Mix_CloseAudio();
}

bool	Sounds::pause_audio_player(void)
{
	if (Mix_PausedMusic() != 1)
	{
		Mix_PauseMusic();
		Mix_Pause(1);
		return (true);
	}
	return (false);
}

bool	Sounds::unpause_audio_player(void)
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_ResumeMusic();
		Mix_Resume(1);
		return (true);
	}
	return (false);
}

void	Sounds::play_distant_sound(int key, int angle, int dist)
{
	if (!Mix_SetPosition(1, angle, dist))
	{
		std::cout << "Error MIX_SetPosition" << std::endl;
	}
	this->play_sound(key);
}

void	Sounds::Volume_Music_Up()
{
	this->volume = this->volume + 8;
	Mix_VolumeMusic(this->volume);
}

void	Sounds::Volume_Music_Down()
{
	this->volume = this->volume - 8;
	Mix_VolumeMusic(this->volume);
}

void	Sounds::Mute_Music()
{
	Mix_VolumeMusic(0);
}

void	Sounds::Volume_Sounds_Up()
{
	unsigned int	i;

	i = 0;
	while (i != this->sounds.size())
	{
		Mix_VolumeChunk(this->sounds[i], this->volume_sound - 8);
	}
}

void	Sounds::Volume_Sounds_Down()
{
	unsigned int	i;

	i = 0;
	while (i != this->sounds.size())
	{
		Mix_VolumeChunk(this->sounds[i], this->volume_sound - 8);
	}
}

void	Sounds::Mute_Sounds()
{
	unsigned int	i;

	i = 0;
	while (i != this->sounds.size())
	{
		Mix_VolumeChunk(this->sounds[i], 0);
	}
}

