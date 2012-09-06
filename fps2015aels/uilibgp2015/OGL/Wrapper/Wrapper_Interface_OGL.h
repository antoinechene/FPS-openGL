#ifndef	__WRAPPER_INTERFACE_OGL_H__
#define	__WRAPPER_INTERFACE_OGL_H__

#ifdef	__OGL

#ifndef	__MAKE_H
#include <pthread.h>
#include <vector>
#include <GL/glut.h>
#endif

#include "Wrapper_Interface_Template.h"
#include "../Singleton.hpp"
#include "../Surface.h"

namespace	ID
{
	class	Wrapper_Interface : public Wrapper_Interface_Template,
				    public Singleton<ID::Wrapper_Interface>
	{
		friend class	Singleton<ID::Wrapper_Interface>;
	public:
		typedef	void*	wrapper_surface;
		#include "Wrapper_Interface_OGL_inline.hpp"
	private:
		Wrapper_Interface(void);
		~Wrapper_Interface(void);
	};
};

#endif
#endif
