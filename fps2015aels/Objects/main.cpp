#include "FBXLoader.h"
#include "Ball.h"
#include "Display.h"
#include "./Shader/Tools.h"

int	main(int argc, char** argv)
{
	Display*	disp;
	FBXLoader	load;
//	GLuint		shader;
//	GLuint		Prog;
//	GLuint		shader2;

//	shader = LoadShader("./Shader/test.vert");


	disp = Display::GetInstance();
	disp->Init(argc, argv);
	load.Import(argv[1]);
//	load.Import(argv[2]);

//	shader = LoadShader("./Shader/Shadow.vert", 1);
//	shader2 = LoadShader("./Shader/Shadow.frag", 0);

//	Prog = LinkShader(shader, shader2);
//	ActivateProgram(Prog);
	glutMainLoop();
	return (0);
}
