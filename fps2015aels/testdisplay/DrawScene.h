#ifndef _DRAW_SCENE_H
#define _DRAW_SCENE_H
void DrawNodeRecursive(KFbxNode* pNode, 
		KTime& pTime, 
		KFbxXMatrix& pParentGlobalPosition);
void DrawNodeRecursiveAtPose(KFbxNode* pNode,
		KTime& pTime, 
		KFbxXMatrix& pParentGlobalPosition,
		KFbxPose* pPose);
void DrawNode(KFbxNode* pNode, 
		KTime& lTime, 
		KFbxXMatrix& pParentGlobalPosition,
		KFbxXMatrix& pGlobalPosition,
		KFbxPose* pPose = NULL);
void DrawMarker(KFbxXMatrix& pGlobalPosition);
void DrawSkeleton(KFbxNode* pNode, 
		KFbxXMatrix& pParentGlobalPosition, 
		KFbxXMatrix& pGlobalPosition);
void DrawMesh(KFbxNode* pNode, KTime& pTime,
		KFbxXMatrix& pGlobalPosition, KFbxPose* pPose);
void ComputeShapeDeformation(KFbxNode* pNode,
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray);
void ComputeClusterDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh,
		KFbxCluster* pCluster, 
		KFbxXMatrix& pVertexTransformMatrix,
		KTime pTime, 
		KFbxPose* pPose);
void ComputeLinearDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose);
void ComputeDualQuaternionDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose);
void ComputeSkinDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose);
void ReadVertexCacheData(KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray);
void DrawCamera(KFbxNode* pNode, 
		KTime& pTime, 
		KFbxXMatrix& pGlobalPosition);
void DrawLight(const KFbxNode* pNode, const KTime& pTime, const KFbxXMatrix& pGlobalPosition);
void DrawNull(KFbxXMatrix& pGlobalPosition);
void MatrixScale(KFbxXMatrix& pMatrix, double pValue);
void MatrixAddToDiagonal(KFbxXMatrix& pMatrix, double pValue);
void MatrixAdd(KFbxXMatrix& pDstMatrix, KFbxXMatrix& pSrcMatrix);
void DrawGrid(KFbxXMatrix& pGlobalPosition);
void DrawScene(KFbxScene* pScene, KTime& lTime);
void DrawSceneAtPose(KFbxScene* pScene, KTime& lTime, int pPoseIndex);
#endif 

