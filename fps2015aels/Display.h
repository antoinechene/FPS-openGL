#ifndef Display_h
#define Display_h
#include "./uilibgp2015/Singleton.hpp"
#include <GLShaderManager.h>
#include <GLTools.h>
#include <GLFrustum.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <GLFrame.h>
#include <GL/glut.h>

class Node;
class Camera;
class _GLBatch;
class ID_Mesh;
class Box;
class Display : public ID::Singleton<Display>
{
	friend class ID::Singleton<Display>;
	public:
				Display();
				~Display();
		int		Init(int argc, char** argv);
		static void	ChangeSize(int w, int h);
		static void	RenderScene(void);
		static void	clean(void);
		void		DrawAll(void);
		void		DrawAllR(Node* n, Camera* cam);
		static void	keyboard(unsigned char key, int x, int y);
		static void	keyboard_s(int key, int x, int y);
		static void	mouse(int x, int y);
		static void	callback(int button, int state, int x, int y);
		char*		GameCycle();
		char*		TransformNBTriangle();
		void		WriteText(char* text, int Dep);
		#include "DisplayInline.hpp"
		void		SetShader(_GLBatch* batch,
		ID_Mesh* mesh, M3DVector4f vlightpos);
		void		DrawSphere();
		static void	Update(int value);
		void		DrawHitbox(Box* hit);

	public:
		bool	filling;
		int	old_x;
		int	old_y;
		int	NBTriangle;
	private:
		GLShaderManager		shadermanager;
		GLMatrixStack		modelViewMatrix;
		GLMatrixStack		projectionMatrix;
		GLFrustum		viewFrustum;
		GLGeometryTransform	transformPipeline;
};

#endif
