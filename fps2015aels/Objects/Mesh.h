#ifndef Mesh_h
#define Mesh_h

#include <fbxsdk.h>
#include "Vec3f.h"
#include <iostream>
#include <vector>
#include "Vec2f.h"

class Point;
class Material;
class Texture;
class Polygon;
class StaticObj;
class Mesh
{
	public:
		Mesh();
		~Mesh();
		void	FillControlPoint(KFbxMesh* mesh);
		void	FillControlPoint(Point** CP, int nb);
		void	FillMesh(int nb);
		void	FillMesh(KFbxMesh* mesh);
		void	TestDraw(KFbxNode* Node, KFbxMesh* mesh);
		void	Draw(void);
		void	FillMat(KFbxXMatrix& mat);
		void	LoadNormal(int id, int vertexId, KFbxMesh* pMesh, Point* B);
		#include "MeshInline.hpp"
		//virtual bool	GenerateHitBox();
		void	CalcDist(StaticObj* obj);
		Vec3f	CalcCenter(Polygon* pol);

		void	ReadVertexCacheData(KFbxMesh* pMesh, KTime& pTime, KFbxVector4* pVertexArray);
		void	ComputeShapeDeformation(KFbxMesh* pMesh, KTime& pTime, KFbxVector4* pVertexArray);
		void	ComputeSkinDeformation(KFbxXMatrix& pGlobalPosition, KFbxMesh*
		pMesh,KTime& pTime, KFbxVector4* pVertexArray,KFbxPose* pPose);
		void	ComputeLinearDeformation(KFbxXMatrix& pGlobalPosition,KFbxMesh* pMesh, KTime& pTime, 
		KFbxVector4* pVertexArray, KFbxPose* pPose);
		void	MatrixAddToDiagonal(KFbxXMatrix& pMatrix, double pValue);
		void	MatrixScale(KFbxXMatrix& pMatrix, double pValue);
		void	MatrixAdd(KFbxXMatrix& pDstMatrix, KFbxXMatrix& pSrcMatrix);
		void	ComputeDualQuaternionDeformation(KFbxXMatrix& pGlobalPosition, KFbxMesh* pMesh, KTime& pTime, 
		KFbxVector4* pVertexArray, KFbxPose* pPose);
		void	ComputeClusterDeformation(KFbxXMatrix& pGlobalPosition, KFbxMesh* pMesh, KFbxCluster* pCluster, KFbxXMatrix& pVertexTransformMatrix, KTime pTime, 
		KFbxPose* pPose);

		void	AnimInit(KFbxScene* gscene);
		void	AnimStackSelectionCallback(int pItem, KFbxScene* gscene);

		private:
			KFbxAnimLayer* gCurrentAnimationLayer;

			Polygon**		pol;
			GLfloat*		Matrice;
			Point**			ControlPoint;
			GLint			TextureDiffIndex;
			GLint			TextureAmbIndex;
			GLint			TextureEmIndex;
			GLint			TextureSpecularIndex;
			GLint			MatIndex;
			std::vector<Material*>	Mat;

};

#endif
