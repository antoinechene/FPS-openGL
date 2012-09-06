#ifndef	__MAIN_CONTROL_H__
#define	__MAIN_CONTROL_H__

#include "../Drawable/Drawable.h"

namespace	ID
{
	class	Main_Control : public Drawable
	{
		public:
					Main_Control(uint16_t width, uint16_t height, uint32_t flags,
						     uint32_t rmask, uint32_t gmask,
						     uint32_t bmask, uint32_t amask);
					Main_Control(const Main_Control& mc);
			virtual		~Main_Control();
			Main_Control&	operator=(const Main_Control& mc);

			bool		GetInvalidate(void) const;
			virtual int	RefreshToSurface(Surface* surface, int x, int y);

		protected:
			virtual void	_SetInvalidate(bool invalidate);
	};
};

#endif
