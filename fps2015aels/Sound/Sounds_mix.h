#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_mixer.h>
#include <vector>
//#include <list>
//#include <pthread.h>
#include "../uilibgp2015/OGL/ID_glibrary.h"

class	Sounds : public ID::Singleton<Sounds>
{
	friend class ID::Singleton<Sounds>;
public:
	bool		init(void);
	bool		LoadWAV(const char*);
	bool		LoadMUS(const char*);
	void		set_theme(int);
	void		stop_audio_player(void);
	bool		pause_audio_player(void);
	bool		unpause_audio_player(void);
	void		play_sound(int);
	void		play_distant_sound(int, int, int);
//	void		Set_Volume(int);
	void		Volume_Music_Up();
	void		Volume_Music_Down();
	void		Mute_Music();
	void		Volume_Sounds_Up();
	void		Volume_Sounds_Down();
	void		Mute_Sounds();
//private:
	Sounds(void);
	~Sounds(void);
	void		set_vol_dist_sound(int, int);
	void		set_vol_song(int);

public:
	const int&			theme;
	const bool&			alive;
private:
	std::vector<Mix_Chunk*>		sounds;
	std::vector<Mix_Music*>		songs;
	int				volume;
	int				volume_sound;
	bool				new_theme;
	int				_theme;
	bool				_alive;
};


#endif

