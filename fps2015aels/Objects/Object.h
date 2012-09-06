#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Vec3f.h"
#include "Mesh.h"

class	Object
{
	public:
		enum O_TYPE
		{
			O_SPHERE,
			O_PLAN,
			O_CUBE,
			O_CAMERA,
			O_STATIC
		};
	public:
		Object(void);
		Object(Vec3f, Vec3f, Vec3f, bool);
		virtual	~Object(void);
		inline O_TYPE	GetType(void)
		{
			return (this->_type);
		}
	//	inline bool	isStatic(void)
	//	{
	//		return (this->c_static);
	//	}
	protected:
		O_TYPE	_type;
	public:
		Vec3f		pos;
		Vec3f		rot;
		Vec3f		scale;
		Mesh*		m;
	//	const bool	c_solid;
};

#endif

