#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <string.h>

char*	LoadShaderSource(const char* filename)
{
	char*	src;
	FILE*	fp;
	long	size;
	long	i;

	src = NULL;
	fp = NULL;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		std::cout<<"error to open file"<<std::endl;
		return (NULL);
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	src = (char*)malloc(size + 1);
	if (src == NULL)
	{
		fclose(fp);
		std::cout<<"error of allocation"<<std::endl;
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		src[i] = fgetc(fp);
		++i;
	}
	src[size] = '\0';
	fclose(fp);
	return (src);
}

GLuint	LoadShader(const char* filename, bool type)
{
	GLuint	shader;
	char*	src;
	GLint	Status;
	char*	log;
	GLsizei	logsize;

	logsize = 0;
	Status = GL_TRUE;
	src = NULL;
	if (type)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	if (!glIsShader(shader))
	{
		std::cout<<"error of creation shader"<<std::endl;
		return (0);
	}
	src = LoadShaderSource(filename);
	if (src == NULL)
	{
		glDeleteShader(shader);
		return (0);
	}
	glShaderSource(shader, 1, (const GLchar**)&src, NULL);
	glCompileShader(shader);
	free (src);
	src = NULL;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &Status);
	if (Status != GL_TRUE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
		log = (char*) malloc(logsize + 1);
		if (log == NULL)
		{
			std::cout<<"error of allocation"<<std::endl;
			return (0);
		}
		memset(log, '\0', logsize + 1);
		glGetShaderInfoLog(shader, logsize, &logsize, log);
		std::cout<<"error of compilation in the shader "<<filename<<std::endl;
		std::cout<<"error is "<<log<<std::endl;
		free (log);
		glDeleteShader(shader);
		return (0);
	}
	return (shader);
}

GLuint	LinkShader(GLuint shader, GLuint shader2)
{
	GLuint	Prog;
	GLint	status;
	GLsizei	logsize;
	char*	log;

	logsize = 0;
	status = GL_TRUE;
	Prog = glCreateProgram();
	glAttachShader(Prog, shader);
	glAttachShader(Prog, shader2);

	glLinkProgram(Prog);
	glGetProgramiv(Prog, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		glGetProgramiv(Prog, GL_INFO_LOG_LENGTH, &logsize);
		log = (char*) malloc(logsize + 1);
		if (log == NULL)
		{
			std::cout<<"error of allocation"<<std::endl;
			return (0);
		}
		memset(log, '\0', logsize + 1);
		glGetProgramInfoLog(Prog, logsize, &logsize, log);
		std::cout<<"error of linkage Program and shader"<<std::endl;
		std::cout<<log<<std::endl;
		free (log);
		glDeleteProgram(Prog);
		return (0);
	}
	return (Prog);
}

void	ActivateProgram(GLuint prog)
{
	glUseProgram(prog);
}

void	DesActivateProgram()
{
	glUseProgram(0);
}


