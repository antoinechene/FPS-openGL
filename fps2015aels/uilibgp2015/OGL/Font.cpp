#include "Font.h"
#include <iostream>
#include <GL/glut.h>

ID::Font::Font()
{
}

ID::Font::~Font()
{
}

void	ID::Font::TextRender(const char* str, void* font, ID::Color* fg, int x, int y, int z)
{
	int		i;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(fg->r, fg->g, fg->b);
	glRasterPos3i(x, y, z);
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n')
		{
			y -= 20;
			glRasterPos3i(x, y, z);
		}
		else
			glutBitmapCharacter(font, str[i]);
		++i;
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

int		ID::Font::SizeText(void* font, const char* text, int* w, int* h)
{
	(void)font;
	(void)text;
	(void)w;
	(void)h;
	return 0;
//	return TTF_SizeText(font, text, w, h);
}

