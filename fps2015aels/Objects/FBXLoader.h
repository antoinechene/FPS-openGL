#ifndef FBXLoader_h
#define FBXLoader_h
#include <fbxsdk.h>
#include <iostream>

class Mesh;
class Point;
class FBXLoader
{
	public:
				FBXLoader();
				~FBXLoader();
		int		Import(char* name);
		void		PrintNode(KFbxNode* pNode);
		void		GetAttributeTypeName(KFbxNode* pNode,KFbxNodeAttribute::EAttributeType type);
		Mesh*		ConstructObject(KFbxNode* node, KFbxMesh* mesh);
//		void		PrintAll(void);
//		Hitbox*	ConstructBatch(KFbxMesh* mesh, Node* node);
//		Camera*		ConstructCamera(KFbxNode* node);
//		void 		LoadNormal(int id ,int indexV, KFbxMesh* mesh, Point* B);

//		bool		GetMaterial(KFbxGeometry* g, Object* o);
//		void		GetElementUV(KFbxMesh* m, int i, int j, _GLBatch* b);
//		void		GetBinormal(KFbxMesh* m);
//		void		GetVertexColor(KFbxMesh* m, int vertexId, int id);
//		bool		DisplayTextureNames( KFbxProperty &pProperty, KString& pConnectionString);
//		void		GetMaterialConnection(KFbxMesh* m, Object* o);
///		bool		GetMaterialTextureConnection(KFbxSurfaceMaterial* _mat, char* h, int mat_id, int l, _GLBatch* b);
//		bool		GetTexture(KFbxGeometry* g, Object* o);
//		bool		FindTextureInfo(KFbxProperty prop, bool& disp, int mat_i, Object* o);
//		void		TextureInfoFinded(KFbxTexture* _t, int blend_mode, Texture* t);
//		void		DisplayPivotsAndLimits(KFbxNode*
//		pNode, Node* node);
//		GLfloat*	MultiplyV(GLfloat* v , Node* node);

	private:
		KFbxScene*	scene;
	//	void	__PrintNode(Node*);
	//	size_t	floor;
	//	Node*	Root;


};

#endif 
