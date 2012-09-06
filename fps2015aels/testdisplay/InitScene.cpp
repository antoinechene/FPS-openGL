#include <math.h>
#include <fbxsdk.h>
#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include "InitScene.h"
#include "Texture.h"

KString ExtractDirectory(KString pFilePath);

extern KFbxImporter* gImporter;


void ConvertNurbsAndPatch(KFbxSdkManager* pSdkManager, KFbxScene* pScene)
{
	ConvertNurbsAndPatchRecursive(pSdkManager, pScene->GetRootNode());
}


void ConvertNurbsAndPatchRecursive(KFbxSdkManager* pSdkManager, KFbxNode* pNode)
{
	KFbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

	if (lNodeAttribute)
	{
		if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eNURB ||
				lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::ePATCH)
		{
			KFbxGeometryConverter lConverter(pSdkManager);
			lConverter.TriangulateInPlace(pNode);
		}
	}

	int i, lCount = pNode->GetChildCount();

	for (i = 0; i < lCount; i++)
	{
		ConvertNurbsAndPatchRecursive(pSdkManager, pNode->GetChild(i));
	}
}


void FillCameraArray(KFbxScene* pScene, KArrayTemplate<KFbxNode*>& pCameraArray)
{
	pCameraArray.Clear();

	FillCameraArrayRecursive(pScene->GetRootNode(), pCameraArray);
}


void FillCameraArrayRecursive(KFbxNode* pNode, KArrayTemplate<KFbxNode*>& pCameraArray)
{
	int i, lCount;

	if (pNode)
	{
		if (pNode->GetNodeAttribute())
		{
			if (pNode->GetNodeAttribute()->GetAttributeType() == KFbxNodeAttribute::eCAMERA)
			{
				pCameraArray.Add(pNode);
			}
		}

		lCount = pNode->GetChildCount();

		for (i = 0; i < lCount; i++)
		{
			FillCameraArrayRecursive(pNode->GetChild(i), pCameraArray);
		}
	}
}


void FillPoseArray(KFbxScene* pScene, KArrayTemplate<KFbxPose*>& pPoseArray)
{
	int      i, lPoseCount;

	for (i=0, lPoseCount = pScene->GetPoseCount(); i < lPoseCount; i++)
	{
		pPoseArray.Add(pScene->GetPose(i));
	}
}

void PreparePointCacheData(KFbxScene* pScene)
{
	int lIndex, lNodeCount = KFbxGetSrcCount<KFbxNode>(pScene);

	for (lIndex=0; lIndex<lNodeCount; lIndex++)
	{
		KFbxNode* lNode = KFbxGetSrc<KFbxNode>(pScene, lIndex);

		if (lNode->GetGeometry()) 
		{
			int i, lVertexCacheDeformerCount = lNode->GetGeometry()->GetDeformerCount(KFbxDeformer::eVERTEX_CACHE);

			lVertexCacheDeformerCount = lVertexCacheDeformerCount > 0 ? 1 : 0;

			for (i=0; i<lVertexCacheDeformerCount; ++i )
			{
				// Get the Point Cache object
				KFbxVertexCacheDeformer* lDeformer = static_cast<KFbxVertexCacheDeformer*>(lNode->GetGeometry()->GetDeformer(i, KFbxDeformer::eVERTEX_CACHE));
				if( !lDeformer ) continue;
				KFbxCache* lCache = lDeformer->GetCache();
				if( !lCache ) continue;

				// Process the point cache data only if the constraint is active
				if (lDeformer->IsActive())
				{
					if (lCache->GetCacheFileFormat() == KFbxCache::ePC2)
					{

					}
					else if (lCache->GetCacheFileFormat() == KFbxCache::eMC)
					{
						if (!lCache->ConvertFromMCToPC2(KTime::GetFrameRate(pScene->GetGlobalSettings().GetTimeMode()), 0))
						{
							KString lTheErrorIs = lCache->GetError().GetLastErrorString();
						}
					}


					if (!lCache->OpenFileForRead())
					{
						KString lTheErrorIs = lCache->GetError().GetLastErrorString();

						lDeformer->SetActive(false);
					}
				}
			}
		}
	}
}

