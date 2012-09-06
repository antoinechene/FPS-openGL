#include "Display.h"
#include "Scene.h"
#include "Node.h"
#include "Object.h"
#include "Mesh.h"
#include "Camera.h"
#include "Material.h"
#include "Texture.h"
#include "Balls.h"
#include "Hitbox.h"
#include "Octree.h"

#define Timer 25 
char*	itoa(int nb);

Display::Display()
{
	this->old_x = 0;
	this->old_y = 0;
	this->filling = false;
	this->NBTriangle = 0;

}
Display::~Display()
{
}

void	Selecti(int Value)
{
	(void)Value;
}

void	Menu()
{
	int	sub1;
	int	sub2;

	sub1 = glutCreateMenu(&Selecti);
	glutAddMenuEntry("abc",1);
	glutAddMenuEntry("abcd",1);
	sub2 = glutCreateMenu(&Selecti);
	glutAddMenuEntry("abcde",1);
	glutAddMenuEntry("abcdefg",1);
	glutAddSubMenu("plop",sub1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void	Display::Update(int value)
{
	Scene*	scene;
	std::vector<Balls*>*	ball;
	size_t			size;
	size_t			i;

	i = 0;
	scene = Scene::GetInstance();
	ball = scene->GetBallList();
	size = ball->size();
	while (i < size)
	{
		(*ball)[i]->Update(scene->GetGravity());
		++i;
	}

	(void)value;
	glutPostRedisplay();
	glutTimerFunc(Timer, Update, 0);

}
int	Display::Init(int argc, char** argv)
{
//	gltSetWorkingDirectory(argv[0]);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA |GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Viewer");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(RenderScene);
	glutSpecialFunc(keyboard_s);
	glutTimerFunc(Timer, Update, 0);
	glutPassiveMotionFunc(mouse);
	glutMouseFunc(callback);
	glViewport(0, 0, 800, 600);
	glutSetCursor(GLUT_CURSOR_NONE);
	GLenum err = glewInit();
	atexit(clean);
	if (GLEW_OK != err)
	{
		fprintf(stderr,"GLEW Error %s\n", glewGetErrorString(err));
		return (1);
	}
	gluPerspective(45.0f, (GLfloat) 800 / (GLfloat)600, 0.0f, 1000.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);
	Menu();
	shadermanager.InitializeStockShaders();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	return (0);
}

void	Display::ChangeSize(int w, int h)
{
	Display*	disp;

	disp = Display::GetInstance();
	glViewport(0, 0, w , h);
	disp->GetFrustum()->SetPerspective(25.0f, (float)w / (float)h, 0.05f, 100.0f);
	disp->GetProjection()->LoadMatrix(disp->GetFrustum()->GetProjectionMatrix());
	disp->GetTransPipeline()->SetMatrixStacks(*disp->GetModelView(), *disp->GetProjection());
}

void	Display::RenderScene(void)
{
	Display*	disp;
	char*		fps;
	char*		NBTriangle;
	Scene*		scene;



	scene = Scene::GetInstance();
	disp = Display::GetInstance();
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
/*
	ID_Mesh*		mesh;
	std::vector<_GLBatch*>*	batch;
	size_t			j;
	size_t			sizeB;
	GLfloat			col[] =  {1.0f, 0.0f, 0.0f, 1.0f};
	Box*			b;

	disp = Display::GetInstance();

	b = scene->oct->Skybox;	
	mesh =b ->GetHitbox();
	batch = mesh->GetMesh();
	j = 0;
	sizeB = batch->size();
	while (j < sizeB)
	{
		std::cout<<"plop"<<std::endl;
		disp->GetManager()->UseStockShader(GLT_SHADER_FLAT,
								disp->GetTransPipeline()->GetModelViewProjectionMatrix(),
								 col);
		(*batch)[j]->Draw();
		++j;
	}*/
disp->DrawHitbox(scene->oct->Skybox);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	fps = disp->GameCycle();
	disp->WriteText(fps, 0);
	NBTriangle = disp->TransformNBTriangle();
	disp->WriteText(NBTriangle, 300);
	disp->DrawAll();
	glutSwapBuffers();
	delete[] fps;
	delete[] NBTriangle;
}

void	Display::DrawSphere()
{
	GLfloat			col[4];
	Scene*			scene;
	Balls*			ball;
	std::vector<Balls*>*	List;
	size_t			size;
	size_t			i;

	scene = Scene::GetInstance();

	List = scene->GetBallList();

	i = 0;
	size = List->size();
	while (i < size)
	{
		ball = (*List)[i];
		col[0] = ball->GetColor()->GetR();
		col[1] = ball->GetColor()->GetG();
		col[2] = ball->GetColor()->GetB();
		col[3] = 1.0f;

		this->GetModelView()->PushMatrix();
		this->GetModelView()->Translate(ball->GetPos()->GetX(), ball->GetPos()->GetY(),
		ball->GetPos()->GetZ());


		this->GetManager()->UseStockShader(GLT_SHADER_FLAT,
								this->GetTransPipeline()->GetModelViewProjectionMatrix(),
								 col);
		ball->GetMesh()->Draw();
		this->GetModelView()->PopMatrix();
		++i;
	}

}

void	Display::DrawAll(void)
{
	size_t			i;
	size_t			end;
	Scene*			scene;
	Node*			Root;
	Display*		disp;
	Camera*			cam;
	M3DMatrix44f		CamMat;
	std::vector<Camera*>*	listCam;
	M3DVector3f		up;
	GLfloat			col[] =  {0.0f, 1.0f, 1.0f, 1.0f};


	disp = Display::GetInstance();
	scene = Scene::GetInstance();
	Root = scene->GetRoot();
	listCam = scene->GetCamList();
	cam = (*listCam)[scene->GetActualCam()];
	cam->GetCam()->GetForwardVector(up);
	cam->GetCam()->GetCameraMatrix(CamMat);
	disp->GetModelView()->PushMatrix(CamMat);
	disp->GetFrustum()->SetPerspective(cam->GetFov() ,
					  (float)cam->GetWidth() / (float)cam->GetHeight(),
					   cam->GetNear(), cam->GetFar());
	disp->GetProjection()->LoadMatrix(disp->GetFrustum()->GetProjectionMatrix());
	disp->GetTransPipeline()->SetMatrixStacks(*disp->GetModelView(), *disp->GetProjection());
	
	this->GetManager()->UseStockShader(GLT_SHADER_FLAT,
								this->GetTransPipeline()->GetModelViewProjectionMatrix(),
								 col);
	(*(scene->GetSky()->GetMesh()->GetMesh()))[0]->Draw();
	this->DrawSphere();
	if (Root == NULL)
		end = 0;
	else
		end = Root->GetChild()->size();
	i = 0;
	while (i < end)
	{
		this->DrawAllR((*(Root->GetChild()))[i], cam);
		++i;
	}
	disp->GetModelView()->PopMatrix();
}
/*
void	Diaplay:DrawBox(Box* box)
{
	size_t	i;
	size_t	size;

/	box->GetHitBox();


}
*/
void	Display::DrawHitbox(Box* hit)
{
	ID_Mesh*		mesh;
	std::vector<_GLBatch*>*	batch;
	size_t			j;
	size_t			sizeB;
	GLfloat			col[] =  {1.0f, 0.0f, 0.0f, 1.0f};
	Display*		disp;

	disp = Display::GetInstance();

	mesh = hit->GetHitbox();
	batch = mesh->GetMesh();
	j = 0;
	sizeB = batch->size();
	while (j < sizeB)
	{
		this->GetManager()->UseStockShader(GLT_SHADER_FLAT,
								this->GetTransPipeline()->GetModelViewProjectionMatrix(),
								 col);
		(*batch)[j]->Draw();
		++j;
	}
}

void	Display::DrawAllR(Node* n, Camera* cam)
{
	Hitbox*			hit;
	size_t			i;
	size_t			end;
	Object*			obj;
	std::vector<_GLBatch*>*	batch;
	ID_Mesh*		mesh;
	Display*		disp;
	size_t			sizeB;
	size_t			j;
	M3DVector4f		lightpos = {0.0f, 100.0f, 0.0f, 1.0f};
	M3DVector4f		Vlightpos;
	M3DMatrix44f		CamMat;


	disp = Display::GetInstance();
	hit = n->GetHitbox();
	cam->GetCam()->GetCameraMatrix(CamMat);
	m3dTransformVector4(Vlightpos, lightpos, CamMat);
	disp->GetModelView()->PushMatrix();
	disp->GetModelView()->MultMatrix(*(n->GetMatObj()));
	if (hit != NULL)
	{
		obj = hit->GetMesh();
		if (obj->GetType() == Mesh)
		{
			mesh = (ID_Mesh*)obj;
			batch = mesh->GetMesh();
			j = 0;
			sizeB = batch->size();
			while (j < sizeB)
			{
				this->SetShader((*batch)[j], mesh, Vlightpos);
				(*batch)[j]->Draw();
				++j;
			}
		}
//		scene
		this->DrawHitbox(hit);
	}
	disp->GetModelView()->PopMatrix();
	i = 0;
	end = n->GetChild()->size();
	while (i < end)
	{
		this->DrawAllR((*(n->GetChild()))[i], cam);
		++i;
	}
}


void	Display::SetShader(_GLBatch* batch, ID_Mesh* mesh, M3DVector4f Vlightpos)
{
	GLfloat			col[] =  {1.0f, 1.0f, 1.0f, 1.0f};
	Display*		disp;
	static size_t		idT = 999;
	Material*		mat;

	mat = NULL;
	disp = Display::GetInstance();
	if (batch->GetTextDiffIndex() == 1)
	{
		this->GetManager()->UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,
							this->GetTransPipeline()->GetModelViewMatrix(),
							this->GetTransPipeline()->GetProjectionMatrix(),
							Vlightpos, col, 0);
		if (batch->GetMatIndex() != -1)
		{
			mat = (*mesh->GetMatList())[batch->GetMatIndex()];
			if (mat->GetTexture()->size() > 0)
			{
				if (idT != (*mat->GetTexture())[0]->GetID())
				{
					mat = (*mesh->GetMatList())[batch->GetMatIndex()];
					idT = (*mat->GetTexture())[0] ->GetID();
					glBindTexture(GL_TEXTURE_2D, idT);
				}
			}
		}
	}
	else
	{
		disp->GetManager()->UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF,
		disp->GetTransPipeline()->GetModelViewMatrix(), disp->GetTransPipeline()->GetProjectionMatrix(), Vlightpos, col);
	}
}

void	Display::clean(void)
{	
	Scene::Kill();
	Display::Kill();
}

void	Display::keyboard(unsigned char key, int x, int y)
{
	(void)x;
	(void)y;
	Display*	disp;
	Scene*		scene;
	size_t		size;


	scene = Scene::GetInstance();
	size = (scene->GetCamList())->size();
	disp = Display::GetInstance();

	if (key == ' ')
		std::cout<<"space "<<std::endl;
	if (key == 'r' || key == 'R')
	{
		if (disp->filling)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		disp->filling = !disp->filling;
	}
	else if (key == '+')
	{
		scene->SetActualCam((scene->GetActualCam() + 1) % size);
//		delete this->Sky;
//		this->Sky = new SkyBox();
		scene->CreateSkybox();

	}
	else if (key == '-')
	{
		
		scene->SetActualCam((scene->GetActualCam() - 1) % size);
		scene->CreateSkybox();
	}
	else if (key == 'q')
	{
		exit(42);
	//	glutDestroyWindow();
//		glutLeaveMainLoop();
		std::cout<<"quit"<<std::endl;
		disp->clean();
	}

}

void	Display::keyboard_s(int key, int x, int y)
{
	float			linear;
	float			angular;
	Scene*			scene;
	std::vector<Camera*>*	cam;
	int			actualcam;
	Display*		disp;

	(void)x;
	(void)y;
	disp = Display::GetInstance();
	scene = Scene::GetInstance();
	linear = 0.5f;
	angular = float(m3dDegToRad(5.0f));
	cam = scene->GetCamList();
	actualcam = scene->GetActualCam();

	if (key == GLUT_KEY_UP)
		(*cam)[actualcam]->GetCam()->MoveForward(linear);
	else if (key == GLUT_KEY_DOWN)
		(*cam)[actualcam]->GetCam()->MoveForward(-linear);
	else if (key == GLUT_KEY_LEFT)
		(*cam)[actualcam]->GetCam()->RotateWorld(angular, 0.0f, 1.0f, 0.0f);
	else if (key == GLUT_KEY_RIGHT)
		(*cam)[actualcam]->GetCam()->RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
	else if (key == GLUT_KEY_PAGE_UP)
		(*cam)[actualcam]->GetCam()->TranslateLocal(0.0f, 1.0f, 0.0f);
	else if (key == GLUT_KEY_PAGE_DOWN)
		(*cam)[actualcam]->GetCam()->TranslateLocal(0.0f, -1.0f, 0.0f);
}
void	Display::mouse(int x, int y)
{
	int			move_x;
	int			move_y;
	Display*		disp;
	Scene*			scene;
	std::vector<Camera*>*	listCam;
	int			ActualCam;
	Camera*			cam;
	float			angular;
//	M3DVector3f		up;
	

	scene = Scene::GetInstance();
	disp = Display::GetInstance();
	listCam = scene->GetCamList();
	ActualCam = scene->GetActualCam();
	angular = float(m3dDegToRad(1.0f));

	cam = (*listCam)[ActualCam];
	move_y = y - disp->old_y;
	move_x = x - disp->old_x;

//	std::cout<<"difx "<<move_x<<"diff y"<<move_y<<std::endl;
	if (move_x > 0)
		cam->GetCam()->RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
	else if (move_x < 0)
		cam->GetCam()->RotateWorld(angular, 0.0f, 1.0f, 0.0f);
	if (move_y > 0)
		cam->GetCam()->RotateLocal(angular, 1.0f, 0.0f, 0.0f);
	else if (move_y < 0)
		cam->GetCam()->RotateLocal(-angular, 1.0f, 0.0f, 0.0f);
//	cam->GetCam()->GetForwardVector(up);
	disp->old_x = x;
	disp->old_y = y;
//	std::cout<<"x "<<disp->old_x<<" y "<<disp->old_y<<std::endl;
	if (move_x != 0 || move_y != 0)
		glutWarpPointer(400, 300);
}

void	Display::callback(int button, int state, int x, int y)
{
	Display*		disp;
	std::vector<Camera*>*	listCam;
	int			ActualCam;
	Camera*			cam;
	Scene*			scene;
	M3DVector3f		vel;
	M3DVector3f		pos;
	M3DVector3f		col;
	Balls*			Test;


	scene = Scene::GetInstance();
	listCam = scene->GetCamList();
	ActualCam = scene->GetActualCam();
	cam = (*listCam)[ActualCam];




	disp = Display::GetInstance();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		cam->GetCam()->GetForwardVector(vel);
		m3dLoadVector3(vel, vel[0] * 50.f, vel[1] * 50.f, vel[2] * 50.f);
		m3dLoadVector3(pos, cam->GetCam()->GetOriginX(),
		cam->GetCam()->GetOriginY(), cam->GetCam()->GetOriginZ());
		m3dLoadVector3(col, 255, 255, 255);
		Test = new Balls(vel, pos, col, 1.0f);
//		((_GLBatch)(Test->Mesh)).FindPMin();
		scene->AddBalls(Test);

	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		disp->old_x = x;
		disp->old_y = y;
	}
}

void	Display::WriteText(char* text, int Dep)
{
	int	i;
	int	size;

	glColor3f(1.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	size = strlen(text);
	i = 0;
	while (i < size)
	{
		glRasterPos2f(Dep + (i * 15) , glutGet(GLUT_WINDOW_HEIGHT) -20);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		++i;
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

char*	Display::TransformNBTriangle()
{
	Display*	disp;
	char*		nb;

	nb = new char [16];
	disp = Display::GetInstance();
	
	strcpy(nb, (char*)"Triangles: ");
	strcat(nb, itoa(disp->NBTriangle));
	return (nb);
}

char*	Display::GameCycle()
{
	static double	current_time = 0;
	static double	last_time = 0;
	double		fps;
	double		res;
	char*		ret;
	char*		ito;

	ret = new char[10];
	strcpy(ret, "FPS:");
	fps = 0;
	last_time = current_time;
	current_time = (double)glutGet(GLUT_ELAPSED_TIME) / 1000;
	res = (current_time -last_time);
	if (res)
	{
		fps = 1.0 / res;
		std::cout<<"fps "<<fps<<std::endl;
		ito = itoa(fps);
		strcat(ret, ito);
		delete[] ito;
	}
	else
		strcat(ret, "inf");
	return (ret);
}

