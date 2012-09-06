#ifndef Tool_h
#define Tool_h

	char*	LoadShaderSource(const char* filename);
	GLuint	LoadShader(const char* filename, bool Type);
	GLuint	LinkShader(GLuint shader, GLuint shader2);
	void	ActivateProgram(GLuint prog);
	void	DesActivateProgram();

#endif

