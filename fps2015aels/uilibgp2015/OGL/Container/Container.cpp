#include "Container.h"

ID::Container::Container()
{
}

ID::Container::Container(uint16_t w, uint16_t h, uint32_t f,
			 uint32_t r, uint32_t g,
			 uint32_t b, uint32_t a) : Drawable(w, h, f, r, g, b, a)
{
}

ID::Container::~Container()
{
}
