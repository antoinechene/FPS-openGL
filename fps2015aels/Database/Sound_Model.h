#ifndef __SOUND_MODEL_H__
#define __SOUND_MODEL_H__

class	Sound_Model
{
	public:
		Sound_Model(char** tab);
		~Sound_Model();
		int	Get_Id();
		void	Set_Id(int id);
		int	Get_Type();
		void	Set_Type(int type);
		char*	Get_File();
		void	Set_File(char* file);
	private:
		int	__id;
		int	__type;
		char*	__file;
};

#endif
