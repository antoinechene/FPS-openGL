#include <math.h>
#include <fbxsdk.h>
#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include "GetPosition.h"
#include "GlFunctions.h"
#include "DrawScene.h"
#include "Texture.h"


extern KFbxAnimLayer* gCurrentAnimationLayer;

void DrawScene(KFbxScene* pScene, 
		KTime& pTime)
{
	KFbxXMatrix lDummyGlobalPosition;

	int i, lCount = pScene->GetRootNode()->GetChildCount();

	for (i = 0; i < lCount; i++)
	{
		DrawNodeRecursive(pScene->GetRootNode()->GetChild(i), pTime, lDummyGlobalPosition);
	}
}

void DrawSceneAtPose(KFbxScene* pScene, KTime& pTime, int pPoseIndex)
{
	KFbxXMatrix lDummyGlobalPosition;
	KFbxPose*   lPose = pScene->GetPose(pPoseIndex);

	int i, lCount = pScene->GetRootNode()->GetChildCount();
	for (i = 0; i < lCount; i++)
	{
		DrawNodeRecursiveAtPose(pScene->GetRootNode()->GetChild(i), pTime, lDummyGlobalPosition, lPose);
	}
}

void DrawNodeRecursive(KFbxNode* pNode, 
		KTime& pTime, 
		KFbxXMatrix& pParentGlobalPosition)
{
	KFbxXMatrix lGlobalPosition = GetGlobalPosition(pNode, pTime, &pParentGlobalPosition);

	KFbxXMatrix lGeometryOffset = GetGeometry(pNode);
	KFbxXMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

	DrawNode(pNode, pTime, pParentGlobalPosition, lGlobalOffPosition);

	int i, lCount = pNode->GetChildCount();

	for (i = 0; i < lCount; i++)
	{
		DrawNodeRecursive(pNode->GetChild(i), pTime, lGlobalPosition);
	}
}

void DrawNodeRecursiveAtPose(KFbxNode* pNode, 
		KTime& pTime, 
		KFbxXMatrix& pParentGlobalPosition,
		KFbxPose* pPose)
{
	KFbxXMatrix lGlobalPosition;

	lGlobalPosition = GetGlobalPosition(pNode, pTime, pPose, &pParentGlobalPosition);

	KFbxXMatrix lGeometryOffset = GetGeometry(pNode);
	KFbxXMatrix lGlobalOffPosition = lGlobalPosition * lGeometryOffset;

	DrawNode(pNode, pTime, pParentGlobalPosition, lGlobalOffPosition, pPose);

	int i, lCount = pNode->GetChildCount();

	for (i = 0; i < lCount; i++)
	{
		DrawNodeRecursiveAtPose(pNode->GetChild(i), pTime, lGlobalPosition, pPose);
	}
}

void DrawNode(KFbxNode* pNode, 
		KTime& pTime, 
		KFbxXMatrix& pParentGlobalPosition,
		KFbxXMatrix& pGlobalPosition,
		KFbxPose* pPose)
{
	KFbxNodeAttribute* lNodeAttribute = pNode->GetNodeAttribute();

	if (lNodeAttribute)
	{
		//   if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eMARKER)
		//       {
		//            DrawMarker(pGlobalPosition);
		//     }
		// else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eSKELETON)
		//  {
		//          DrawSkeleton(pNode, pParentGlobalPosition, pGlobalPosition);
		//  }
		if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eMESH)
		{
			DrawMesh(pNode, pTime, pGlobalPosition, pPose);
		}
		//  else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eNURB)
		//  {
		//    // Not supported yet. 
		// Should have been converted into a mesh in function ConvertNurbsAndPatch().
		//  }
		//  else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::ePATCH)
		//  {
		// Not supported yet. 
		// Should have been converted into a mesh in function ConvertNurbsAndPatch().
		//  }
		//  else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eCAMERA)
		//  {
		//        DrawCamera(pNode, pTime, pGlobalPosition);
		//  }
		else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eLIGHT)
		{
			DrawLight(pNode, pTime, pGlobalPosition);
		}
		//  else if (lNodeAttribute->GetAttributeType() == KFbxNodeAttribute::eNULL)
		//  {
		//      DrawNull(pGlobalPosition);
		//   }

	}
	// else
	// {
	//     DrawNull(pGlobalPosition);
	//  }
}

void DrawMarker(KFbxXMatrix& pGlobalPosition)
{
	GlDrawMarker(pGlobalPosition);  
}

void DrawSkeleton(KFbxNode* pNode, KFbxXMatrix& pParentGlobalPosition, KFbxXMatrix& pGlobalPosition)
{
	KFbxSkeleton* lSkeleton = (KFbxSkeleton*) pNode->GetNodeAttribute();

	if (lSkeleton->GetSkeletonType() == KFbxSkeleton::eLIMB_NODE &&
			pNode->GetParent() &&
			pNode->GetParent()->GetNodeAttribute() &&
			pNode->GetParent()->GetNodeAttribute()->GetAttributeType() == KFbxNodeAttribute::eSKELETON)
	{
		GlDrawLimbNode(pParentGlobalPosition, pGlobalPosition); 
	}
}

void DrawMesh(KFbxNode* pNode, KTime& pTime, KFbxXMatrix& pGlobalPosition, KFbxPose* pPose)
{
	KFbxMesh* lMesh = (KFbxMesh*) pNode->GetNodeAttribute();
	int lClusterCount = 0;
	int lSkinCount= 0;
	int lVertexCount = lMesh->GetControlPointsCount();

	if (lVertexCount == 0)
	{
		return;
	}

	KFbxVector4* lVertexArray = new KFbxVector4[lVertexCount];
	memcpy(lVertexArray, lMesh->GetControlPoints(), lVertexCount * sizeof(KFbxVector4));

	if (lMesh->GetDeformerCount(KFbxDeformer::eVERTEX_CACHE) &&
			(static_cast<KFbxVertexCacheDeformer*>(lMesh->GetDeformer(0, KFbxDeformer::eVERTEX_CACHE)))->IsActive())
	{
		ReadVertexCacheData(lMesh, pTime, lVertexArray);
	}
	else
	{
		if (lMesh->GetShapeCount())
		{
			ComputeShapeDeformation(pNode, lMesh, pTime, lVertexArray);
		}

		lSkinCount = lMesh->GetDeformerCount(KFbxDeformer::eSKIN);
		for( int i=0; i< lSkinCount; i++)
			lClusterCount += ((KFbxSkin *)(lMesh->GetDeformer(i, KFbxDeformer::eSKIN)))->GetClusterCount();
		if (lClusterCount)
		{
			ComputeSkinDeformation(pGlobalPosition, lMesh, pTime, lVertexArray, pPose);
		}
	}

	GlDrawMesh(pGlobalPosition, lMesh, lVertexArray);

	delete [] lVertexArray;
}

void ComputeShapeDeformation(KFbxNode* pNode,
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray)
{
	int lVertexCount = pMesh->GetControlPointsCount();

	KFbxVector4* lSrcVertexArray = pVertexArray;
	KFbxVector4* lDstVertexArray = new KFbxVector4[lVertexCount];
	memcpy(lDstVertexArray, pVertexArray, lVertexCount * sizeof(KFbxVector4));

	int lBlendShapeDeformerCount = pMesh->GetDeformerCount(KFbxDeformer::eBLENDSHAPE);
	for(int lBlendShapeIndex = 0; lBlendShapeIndex<lBlendShapeDeformerCount; ++lBlendShapeIndex)
	{
		KFbxBlendShape* lBlendShape = (KFbxBlendShape*)pMesh->GetDeformer(lBlendShapeIndex, KFbxDeformer::eBLENDSHAPE);

		int lBlendShapeChannelCount = lBlendShape->GetBlendShapeChannelCount();
		for(int lChannelIndex = 0; lChannelIndex<lBlendShapeChannelCount; ++lChannelIndex)
		{
			KFbxBlendShapeChannel* lChannel = lBlendShape->GetBlendShapeChannel(lChannelIndex);

			if(lChannel)
			{
				KFbxAnimCurve* lFCurve = pMesh->GetShapeChannel(lBlendShapeIndex, lChannelIndex, gCurrentAnimationLayer);
				if (!lFCurve) continue;
				double lWeight = lFCurve->Evaluate(pTime);

				//Find which shape should we use according to the weight.
				int lShapeCount = lChannel->GetTargetShapeCount();
				double* lFullWeights = lChannel->GetTargetShapeFullWeights();
				for(int lShapeIndex = 0; lShapeIndex<lShapeCount; ++lShapeIndex)
				{
					KFbxShape* lShape = NULL;
					if(lWeight > 0 && lWeight < lFullWeights[0])
					{
						lShape = lChannel->GetTargetShape(0);
					}
					if(lWeight > lFullWeights[lShapeIndex] && lWeight < lFullWeights[lShapeIndex+1])
					{
						lShape = lChannel->GetTargetShape(lShapeIndex+1);
					}

					if(lShape)
					{               
						for (int j = 0; j < lVertexCount; j++)
						{
							KFbxVector4 lInfluence = (lShape->GetControlPoints()[j] - lSrcVertexArray[j]) * lWeight * 0.01;
							lDstVertexArray[j] += lInfluence;
						}                       
					}
				}//For each target shape
			}//If lChannel is valid
		}//For each blend shape channel
	}//For each blend shape deformer
	memcpy(pVertexArray, lDstVertexArray, lVertexCount * sizeof(KFbxVector4));
	delete [] lDstVertexArray;
}

void ComputeClusterDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh,
		KFbxCluster* pCluster, 
		KFbxXMatrix& pVertexTransformMatrix,
		KTime pTime, 
		KFbxPose* pPose)
{
	KFbxCluster::ELinkMode lClusterMode = pCluster->GetLinkMode();

	KFbxXMatrix lReferenceGlobalInitPosition;
	KFbxXMatrix lReferenceGlobalCurrentPosition;
	KFbxXMatrix lAssociateGlobalInitPosition;
	KFbxXMatrix lAssociateGlobalCurrentPosition;
	KFbxXMatrix lClusterGlobalInitPosition;
	KFbxXMatrix lClusterGlobalCurrentPosition;

	KFbxXMatrix lReferenceGeometry;
	KFbxXMatrix lAssociateGeometry;
	KFbxXMatrix lClusterGeometry;

	KFbxXMatrix lClusterRelativeInitPosition;
	KFbxXMatrix lClusterRelativeCurrentPositionInverse;

	if (lClusterMode == KFbxLink::eADDITIVE && pCluster->GetAssociateModel())
	{
		pCluster->GetTransformAssociateModelMatrix(lAssociateGlobalInitPosition);
		lAssociateGeometry = GetGeometry(pCluster->GetAssociateModel());
		lAssociateGlobalInitPosition *= lAssociateGeometry;
		lAssociateGlobalCurrentPosition = GetGlobalPosition(pCluster->GetAssociateModel(), pTime, pPose);
		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;
		lReferenceGlobalCurrentPosition = pGlobalPosition;
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		lClusterGeometry = GetGeometry(pCluster->GetLink());
		lClusterGlobalInitPosition *= lClusterGeometry;
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);
		pVertexTransformMatrix = lReferenceGlobalInitPosition.Inverse() * lAssociateGlobalInitPosition * lAssociateGlobalCurrentPosition.Inverse() *
			lClusterGlobalCurrentPosition * lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
	}
	else
	{
		pCluster->GetTransformMatrix(lReferenceGlobalInitPosition);
		lReferenceGlobalCurrentPosition = pGlobalPosition;
		lReferenceGeometry = GetGeometry(pMesh->GetNode());
		lReferenceGlobalInitPosition *= lReferenceGeometry;
		pCluster->GetTransformLinkMatrix(lClusterGlobalInitPosition);
		lClusterGlobalCurrentPosition = GetGlobalPosition(pCluster->GetLink(), pTime, pPose);
		lClusterRelativeInitPosition = lClusterGlobalInitPosition.Inverse() * lReferenceGlobalInitPosition;
		lClusterRelativeCurrentPositionInverse = lReferenceGlobalCurrentPosition.Inverse() * lClusterGlobalCurrentPosition;
		pVertexTransformMatrix = lClusterRelativeCurrentPositionInverse * lClusterRelativeInitPosition;
	}
}

void ComputeLinearDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose)
{
	KFbxCluster::ELinkMode lClusterMode = ((KFbxSkin*)pMesh->GetDeformer(0, KFbxDeformer::eSKIN))->GetCluster(0)->GetLinkMode();

	int lVertexCount = pMesh->GetControlPointsCount();
	KFbxXMatrix* lClusterDeformation = new KFbxXMatrix[lVertexCount];
	memset(lClusterDeformation, 0, lVertexCount * sizeof(KFbxXMatrix));

	double* lClusterWeight = new double[lVertexCount];
	memset(lClusterWeight, 0, lVertexCount * sizeof(double));

	if (lClusterMode == KFbxCluster::eADDITIVE)
	{
		for (int i = 0; i < lVertexCount; ++i)
		{
			lClusterDeformation[i].SetIdentity();
		}
	}
	int lSkinCount = pMesh->GetDeformerCount(KFbxDeformer::eSKIN);
	for ( int lSkinIndex=0; lSkinIndex<lSkinCount; ++lSkinIndex)
	{
		KFbxSkin * lSkinDeformer = (KFbxSkin *)pMesh->GetDeformer(lSkinIndex, KFbxDeformer::eSKIN);

		int lClusterCount = lSkinDeformer->GetClusterCount();
		for ( int lClusterIndex=0; lClusterIndex<lClusterCount; ++lClusterIndex)
		{
			KFbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
			if (!lCluster->GetLink())
				continue;

			KFbxXMatrix lVertexTransformMatrix;
			ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

			int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
			for (int k = 0; k < lVertexIndexCount; ++k) 
			{            
				int lIndex = lCluster->GetControlPointIndices()[k];

				if (lIndex >= lVertexCount)
					continue;

				double lWeight = lCluster->GetControlPointWeights()[k];

				if (lWeight == 0.0)
				{
					continue;
				}
				KFbxXMatrix lInfluence = lVertexTransformMatrix;
				MatrixScale(lInfluence, lWeight);

				if (lClusterMode == KFbxCluster::eADDITIVE)
				{    
					MatrixAddToDiagonal(lInfluence, 1.0 - lWeight);
					lClusterDeformation[lIndex] = lInfluence * lClusterDeformation[lIndex];
					lClusterWeight[lIndex] = 1.0;
				}
				else // lLinkMode == KFbxLink::eNORMALIZE || lLinkMode == KFbxLink::eTOTAL1
				{
					MatrixAdd(lClusterDeformation[lIndex], lInfluence);
					lClusterWeight[lIndex] += lWeight;
				}
			}//For each vertex          
		}//lClusterCount
	}
	for (int i = 0; i < lVertexCount; i++) 
	{
		KFbxVector4 lSrcVertex = pVertexArray[i];
		KFbxVector4& lDstVertex = pVertexArray[i];
		double lWeight = lClusterWeight[i];

		if (lWeight != 0.0) 
		{
			lDstVertex = lClusterDeformation[i].MultT(lSrcVertex);
			if (lClusterMode == KFbxCluster::eNORMALIZE)
			{
				lDstVertex /= lWeight;
			}
			else if (lClusterMode == KFbxCluster::eTOTAL1)
			{
				lSrcVertex *= (1.0 - lWeight);
				lDstVertex += lSrcVertex;
			}
		} 
	}
	delete [] lClusterDeformation;
	delete [] lClusterWeight;
}

// Deform the vertex array in Dual Quaternion Skinning way.
void ComputeDualQuaternionDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose)
{
	KFbxCluster::ELinkMode lClusterMode = ((KFbxSkin*)pMesh->GetDeformer(0, KFbxDeformer::eSKIN))->GetCluster(0)->GetLinkMode();

	int lVertexCount = pMesh->GetControlPointsCount();
	int lSkinCount = pMesh->GetDeformerCount(KFbxDeformer::eSKIN);

	KFbxDualQuaternion* lDQClusterDeformation = new KFbxDualQuaternion[lVertexCount];
	memset(lDQClusterDeformation, 0, lVertexCount * sizeof(KFbxDualQuaternion));

	double* lClusterWeight = new double[lVertexCount];
	memset(lClusterWeight, 0, lVertexCount * sizeof(double));

	for ( int lSkinIndex=0; lSkinIndex<lSkinCount; ++lSkinIndex)
	{
		KFbxSkin * lSkinDeformer = (KFbxSkin *)pMesh->GetDeformer(lSkinIndex, KFbxDeformer::eSKIN);
		int lClusterCount = lSkinDeformer->GetClusterCount();
		for ( int lClusterIndex=0; lClusterIndex<lClusterCount; ++lClusterIndex)
		{
			KFbxCluster* lCluster = lSkinDeformer->GetCluster(lClusterIndex);
			if (!lCluster->GetLink())
				continue;

			KFbxXMatrix lVertexTransformMatrix;
			ComputeClusterDeformation(pGlobalPosition, pMesh, lCluster, lVertexTransformMatrix, pTime, pPose);

			KFbxQuaternion lQ = lVertexTransformMatrix.GetQ();
			KFbxVector4 lT = lVertexTransformMatrix.GetT();
			KFbxDualQuaternion lDualQuaternion(lQ, lT);

			int lVertexIndexCount = lCluster->GetControlPointIndicesCount();
			for (int k = 0; k < lVertexIndexCount; ++k) 
			{ 
				int lIndex = lCluster->GetControlPointIndices()[k];

				if (lIndex >= lVertexCount)
					continue;

				double lWeight = lCluster->GetControlPointWeights()[k];

				if (lWeight == 0.0)
					continue;

				KFbxDualQuaternion lInfluence = lDualQuaternion * lWeight;
				if (lClusterMode == KFbxCluster::eADDITIVE)
				{    
					lDQClusterDeformation[lIndex] = lInfluence;

					lClusterWeight[lIndex] = 1.0;
				}
				else // lLinkMode == KFbxLink::eNORMALIZE || lLinkMode == KFbxLink::eTOTAL1
				{
					if(lClusterIndex == 0)
					{
						lDQClusterDeformation[lIndex] = lInfluence;
					}
					else
					{
						double lSign = lDQClusterDeformation[lIndex].GetFirstQuaternion().DotProduct(lDualQuaternion.GetFirstQuaternion());
						if( lSign >= 0.0 )
						{
							lDQClusterDeformation[lIndex] += lInfluence;
						}
						else
						{
							lDQClusterDeformation[lIndex] -= lInfluence;
						}
					}
					// Add to the sum of weights to either normalize or complete the vertex.
					lClusterWeight[lIndex] += lWeight;
				}
			}//For each vertex
		}//lClusterCount
	}
	for (int i = 0; i < lVertexCount; i++) 
	{
		KFbxVector4 lSrcVertex = pVertexArray[i];
		KFbxVector4& lDstVertex = pVertexArray[i];
		double lWeightSum = lClusterWeight[i];

		if (lWeightSum != 0.0) 
		{
			lDQClusterDeformation[i].Normalize();
			lDstVertex = lDQClusterDeformation[i].Deform(lDstVertex);

			if (lClusterMode == KFbxCluster::eNORMALIZE)
			{
				lDstVertex /= lWeightSum;
			}
			else if (lClusterMode == KFbxCluster::eTOTAL1)
			{
				lSrcVertex *= (1.0 - lWeightSum);
				lDstVertex += lSrcVertex;
			}
		} 
	}
	delete [] lDQClusterDeformation;
	delete [] lClusterWeight;
}

void ComputeSkinDeformation(KFbxXMatrix& pGlobalPosition, 
		KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray,
		KFbxPose* pPose)
{
	KFbxSkin * lSkinDeformer = (KFbxSkin *)pMesh->GetDeformer(0, KFbxDeformer::eSKIN);
	KFbxSkin::ESkinningType lSkinningType = lSkinDeformer->GetSkinningType();

	if(lSkinningType == KFbxSkin::eLINEAR || lSkinningType == KFbxSkin::eRIGID)
	{
		ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
	}
	else if(lSkinningType == KFbxSkin::eDUALQUATERNION)
	{
		ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, pVertexArray, pPose);
	}
	else if(lSkinningType == KFbxSkin::eBLEND)
	{
		int lVertexCount = pMesh->GetControlPointsCount();

		KFbxVector4* lVertexArrayLinear = new KFbxVector4[lVertexCount];
		memcpy(lVertexArrayLinear, pMesh->GetControlPoints(), lVertexCount * sizeof(KFbxVector4));

		KFbxVector4* lVertexArrayDQ = new KFbxVector4[lVertexCount];
		memcpy(lVertexArrayDQ, pMesh->GetControlPoints(), lVertexCount * sizeof(KFbxVector4));

		ComputeLinearDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayLinear, pPose);
		ComputeDualQuaternionDeformation(pGlobalPosition, pMesh, pTime, lVertexArrayDQ, pPose);

		int lBlendWeightsCount = lSkinDeformer->GetControlPointIndicesCount();
		for(int lBWIndex = 0; lBWIndex<lBlendWeightsCount; ++lBWIndex)
		{
			double lBlendWeight = lSkinDeformer->GetControlPointBlendWeights()[lBWIndex];
			pVertexArray[lBWIndex] = lVertexArrayDQ[lBWIndex] * lBlendWeight + lVertexArrayLinear[lBWIndex] * (1 - lBlendWeight);
		}
	}
}


void ReadVertexCacheData(KFbxMesh* pMesh, 
		KTime& pTime, 
		KFbxVector4* pVertexArray)
{
	KFbxVertexCacheDeformer* lDeformer     = static_cast<KFbxVertexCacheDeformer*>(pMesh->GetDeformer(0, KFbxDeformer::eVERTEX_CACHE));
	KFbxCache*               lCache        = lDeformer->GetCache();
	int                      lChannelIndex = -1;
	unsigned int             lVertexCount  = (unsigned int)pMesh->GetControlPointsCount();
	bool                     lReadSucceed  = false;
	double*                  lReadBuf      = new double[3*lVertexCount];

	if (lCache->GetCacheFileFormat() == KFbxCache::eMC)
	{
		if ((lChannelIndex = lCache->GetChannelIndex(lDeformer->GetCacheChannel())) > -1)
		{
			lReadSucceed = lCache->Read(lChannelIndex, pTime, lReadBuf, lVertexCount);
		}
	}
	else // ePC2
	{
		lReadSucceed = lCache->Read((unsigned int)pTime.GetFrame(true), lReadBuf, lVertexCount);
	}

	if (lReadSucceed)
	{
		unsigned int lReadBufIndex = 0;

		while (lReadBufIndex < 3*lVertexCount)
		{
			pVertexArray[lReadBufIndex/3].SetAt(0, lReadBuf[lReadBufIndex]); lReadBufIndex++;
			pVertexArray[lReadBufIndex/3].SetAt(1, lReadBuf[lReadBufIndex]); lReadBufIndex++;
			pVertexArray[lReadBufIndex/3].SetAt(2, lReadBuf[lReadBufIndex]); lReadBufIndex++;
		}
	}

	delete [] lReadBuf;
}

void DrawLight(const KFbxNode* pNode, const KTime& pTime, const KFbxXMatrix& pGlobalPosition)
{
	const KFbxLight* lLight = pNode->GetLight();
	if (!lLight)
		return;

	KFbxColor lColor(1, 1, 1);
	double lConeAngle = 0.0;

	KFbxXMatrix lLightRotation;
	const KFbxVector4 lYNegativeAxis(-90.0, 0.0, 0.0);
	lLightRotation.SetR(lYNegativeAxis);
	const KFbxXMatrix lLightGlobalPosition = pGlobalPosition * lLightRotation;

	KFbxAnimCurve* fc;
	KFbxTypedProperty<fbxDouble3> lColorProperty = lLight->Color;
	fc = lColorProperty.GetCurve<KFbxAnimCurve>(gCurrentAnimationLayer, KFCURVENODE_COLOR_RED);
	if (fc) lColor.mRed = fc->Evaluate(pTime);
	fc = lColorProperty.GetCurve<KFbxAnimCurve>(gCurrentAnimationLayer, KFCURVENODE_COLOR_GREEN);
	if (fc) lColor.mGreen = fc->Evaluate(pTime);
	fc = lColorProperty.GetCurve<KFbxAnimCurve>(gCurrentAnimationLayer, KFCURVENODE_COLOR_BLUE);
	if (fc) lColor.mBlue = fc->Evaluate(pTime);

	if (lLight->LightType.Get() == KFbxLight::eSPOT)
	{
		KFbxTypedProperty<fbxDouble1> lConeAngleProperty = lLight->ConeAngle;
		fc = lConeAngleProperty.GetCurve<KFbxAnimCurve>(gCurrentAnimationLayer);
		if (fc) lConeAngle = fc->Evaluate(pTime);
	}

	GlDrawLight(lLightGlobalPosition, lLight, lColor, lConeAngle);
}


void MatrixScale(KFbxXMatrix& pMatrix, double pValue)
{
	int i,j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pMatrix[i][j] *= pValue;
		}
	}
}


void MatrixAddToDiagonal(KFbxXMatrix& pMatrix, double pValue)
{
	pMatrix[0][0] += pValue;
	pMatrix[1][1] += pValue;
	pMatrix[2][2] += pValue;
	pMatrix[3][3] += pValue;
}


void MatrixAdd(KFbxXMatrix& pDstMatrix, KFbxXMatrix& pSrcMatrix)
{
	int i,j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			pDstMatrix[i][j] += pSrcMatrix[i][j];
		}
	}
}


