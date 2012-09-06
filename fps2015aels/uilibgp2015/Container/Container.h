#ifndef	__CONTAINER_H__
#define	__CONTAINER_H__

#include "../Drawable/Drawable.h"

namespace	ID
{
	class	Container : public Drawable
	{
		public:
			Container(void);
			Container(uint16_t w, uint16_t h, uint32_t flags,
				  uint32_t rmask, uint32_t gmask,
				  uint32_t bmask, uint32_t amask);
		virtual	~Container(void);
	};
};
#endif
