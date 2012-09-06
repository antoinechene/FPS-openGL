#ifndef __EVENTOBJ_H__
#define __EVENTOBJ_H__

#include "PhysObj.h"

class	EventObj : public PhysObj
{
public:
		EventObj(Vec3f, Vec3f, Vec3f, Vec3f, bool a = false);
	virtual	~EventObj(void);
	virtual void	Activate(void) = 0;
	virtual void	Desactivate(void) = 0;
	bool		GetState(void);
protected:
	bool	_state;
};

#endif

