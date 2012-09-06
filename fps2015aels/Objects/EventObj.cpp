#include "EventObj.h"

EventObj::EventObj(Vec3f p, Vec3f r, Vec3f s, Vec3f v, bool a) : PhysObj(p, r, s, v), _state(a)
{

}

EventObj::~EventObj(void)
{

}

bool	EventObj::GetState(void)
{
	return (this->_state);
}

