#ifndef	__WRAPPER_INTERFACE_OGL_INLINE_HPP__
#define	__WRAPPER_INTERFACE_OGL_INLINE_HPP__

inline virtual int		Init(void)
{
	return 0;
}

inline virtual void		Destroy(void)
{
}

inline virtual int	LoadImage(Surface* s, const char* path,
				  int x, int y, bool )
{
//	Surface*	surf;
	ID::Rect	size(x, y);

	(void)s;
	(void)path;
//	surf = new Surface();
//	if (surf == 0)
//		return (-1);
/*	s->__surface = SDL_LoadBMP(path);
	if (s->__surface == NULL)
		return (-1);
	s->__w = s->__surface->w;
	s->__h = s->__surface->h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;
	size.w = s->w;
	size.h = s->h;
*/
/*	if (s->w != s->w + x ||
	    s->h != s->h + y)
		if (s->Resize(size.w, size.h) == -1)
			return (-1);
	if (resize == true)
	{
		//all-michael: APPELLE A L'ALGO DE RESIZE ICI
	}*/
//	if (this->BlitSurface(surf, &size, s, 0, 0) == -1)
//		return (-1);
//	*s = *surf;
	return (0);
}

inline virtual int	CreateSurface(Surface*, uint16_t,
				      uint16_t, uint32_t,
				      uint32_t, uint32_t,
				      uint32_t, uint32_t)
{
/*	s->__surface = SDL_CreateRGBSurface(f, w, h, 32,
					    rmask, gmask,
					    bmask, amask);
	if (s->__surface == NULL)
		return -1;
	s->__flags = f;
	s->__w = w;
	s->__h = h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;*/
	return 0;
}

inline virtual int	SetVideoMode(Surface*, uint16_t , uint16_t , uint32_t )
{
/*	s->__surface = SDL_SetVideoMode(w, h, 32, f);
	if (s->__surface == NULL)
		return -1;
	s->__flags = f;
	s->__w = w;
	s->__h = h;
	s->__pitch = s->__surface->pitch;
	s->pixels = s->__surface->pixels;*/
	return 0;
}

inline virtual void	DeleteSurface(Surface*)
{
//	SDL_FreeSurface(s->__surface);
}

inline virtual uint32_t	GetPixel(Surface*, uint16_t, uint16_t)
{
/*	int		bpp;
	uint8_t*	p;

	bpp = s->__surface->format->BytesPerPixel;
	p = (uint8_t*)s->__surface->pixels + y * s->__surface->pitch + x * bpp;
	if (bpp == 1)
		return *p;
	if (bpp == 2)
		return *(uint16_t*)p;
	if (bpp == 3)
	{
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
	}
	if (bpp == 4)
		return *(uint32_t*)p;*/
	return 0;
}

inline virtual void	SetPixel(Surface*,
				 uint16_t, uint16_t, uint32_t)
{
/*	int		bpp;
	uint8_t*	p;

	bpp = s->__surface->format->BytesPerPixel;
	p = (uint8_t*)s->pixels + y * s->__pitch + x * bpp;
	if (bpp == 1)
		*p = c;
	else if (bpp == 2)
		*(uint16_t*)p = c;
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (c >> 16) & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = c & 0xff;
		}
		else
		{
			p[0] = c & 0xff;
			p[1] = (c >> 8) & 0xff;
			p[2] = (c >> 16) & 0xff;
		}
	}
	else
		*(uint32_t*)p = c;*/
}

inline virtual int	FillRect(Surface*, ID::Rect*,
				 uint32_t)
{
//	return SDL_FillRect(s->__surface, (SDL_Rect*)r, c);
	return 0;
}

inline virtual int	BlitSurface(Surface* s,
				    int dest_x, int dest_y)
{
	if (s == NULL)
		return 0;
	if (s->GetBlend() == true)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	//	glEnable(GL_ALPHA_TEST);
	if (s->txtID != 0)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, s->txtID);
	}

	glBegin(GL_QUADS);
	if (s->txtID != 0)
		glTexCoord2i(0, 0);
	else
		glColor4fv(s->color);
	glVertex2i(dest_x,		glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));
	if (s->txtID != 0)
		glTexCoord2i(1, 0);
	else
		glColor4fv(s->color);
	glVertex2i(dest_x + s->w,	glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));
	if (s->txtID != 0)
		glTexCoord2i(1, 1);
	else
		glColor4fv(s->color);
	glVertex2i(dest_x + s->w,	glutGet(GLUT_WINDOW_HEIGHT) - dest_y);
	if (s->txtID != 0)
		glTexCoord2i(0, 1);
	else
		glColor4fv(s->color);
	glVertex2i(dest_x,		glutGet(GLUT_WINDOW_HEIGHT) - dest_y);
	glEnd();
/*
	glBegin(GL_QUADS);
	if (s->txtID != 0)
		glTexCoord2i(0, 0);
	else
		glColor4fv(s->color);
	if (s->zoomed != 1.0f)
		glVertex2i(dest_x,
			   glutGet(GLUT_WINDOW_HEIGHT) - (dest_y - s->h + s->h * s->zoomed));
	else
		glVertex2i(dest_x,		glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));

	if (s->txtID != 0)
		glTexCoord2i(1, 0);
	else
		glColor4fv(s->color);
	if (s->zoomed != 1.0f)
		glVertex2i(dest_x + s->w * s->zoomed,
			   glutGet(GLUT_WINDOW_HEIGHT) - (dest_y - s->h + s->h * s->zoomed));
	else
		glVertex2i(dest_x + s->w,	glutGet(GLUT_WINDOW_HEIGHT) - (dest_y + s->h));

	if (s->txtID != 0)
		glTexCoord2i(1, 1);
	else
		glColor4fv(s->color);
	if (s->zoomed != 1.0f)
		glVertex2i(dest_x + s->w * s->zoomed,
			   glutGet(GLUT_WINDOW_HEIGHT) - (dest_y - s->h));
	else
		glVertex2i(dest_x + s->w,	glutGet(GLUT_WINDOW_HEIGHT) - dest_y);

	if (s->txtID != 0)
		glTexCoord2i(0, 1);
	else
		glColor4fv(s->color);
	if (s->zoomed != 1.0f)
		glVertex2i(dest_x,		glutGet(GLUT_WINDOW_HEIGHT) - (dest_y - s->h));
	else
		glVertex2i(dest_x,		glutGet(GLUT_WINDOW_HEIGHT) - dest_y);
	glEnd();*/
//	SDL_Rect	dst_r;

//	dst_r.x = dest_x;
//	dst_r.y = dest_y;
	/*
	return SDL_BlitSurface(s->__surface, (SDL_Rect*)src_r, dest->__surface, &dst_r);*/
	if (s->txtID != 0)
	{
		glDisable(GL_TEXTURE_2D);
	}
	if (s->GetBlend() == true)
	{
	//	glDisable(GL_ALPHA_TEST);
		glDisable(GL_BLEND);
	}
	return 0;
}

#endif
