#ifndef _INIT_SCENE_H
#define _INIT_SCENE_H

#include "Texture.h"

void ConvertNurbsAndPatch(KFbxSdkManager* pSdkManager, 
		KFbxScene* pScene);
void FillCameraArray(KFbxScene* pScene, 
		KArrayTemplate<KFbxNode*>& pCameraArray);
void FillPoseArray(KFbxScene* pScene, 
		KArrayTemplate<KFbxPose*>& pPoseArray);
void PreparePointCacheData(KFbxScene* pScene);

void ConvertNurbsAndPatchRecursive(KFbxSdkManager* pSdkManager, 
		KFbxNode* pNode);
void FillCameraArrayRecursive(KFbxNode* pNode, 
		KArrayTemplate<KFbxNode*>& pCameraArray);
void LoadSupportedTexturesRecursive(const KFbxNode* pNode, TextureManager * pTextureManager);

#endif // #ifndef _INIT_SCENE_H
