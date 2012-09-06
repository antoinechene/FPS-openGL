#ifndef	__KEYBOARD_MANAGER_H__
#define	__KEYBOARD_MANAGER_H__

#include "Singleton.hpp"
#include "Keymap.h"

namespace	ID
{
	class	Keyboard_Manager : public Singleton<Keyboard_Manager>
	{
		friend class	Singleton<Keyboard_Manager>;
		public:
			void	Write(char* str, Mod mod, Key sym, unsigned int maxLength);

		private:
			Keyboard_Manager();
			~Keyboard_Manager();
	};
};

#endif
