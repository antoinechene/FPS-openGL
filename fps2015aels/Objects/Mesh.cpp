#include <GLMatrixStack.h>
#include <GLTools.h>
#include "TGALoader.h"
#include "Mesh.h"
#include "Point.h"
#include "Material.h"
#include "Polygon.h"
#include "GetPosition.h"
#include "StaticObj.h"
#include <math3d.h>

#include "HitBox.h"
#define ABS(X) ((X) < 0.0f) ? -(X) :(X)

KFbxAnimStack* 			gCurrentAnimationStack; 
KArrayTemplate<KString*>	gAnimStackNameArray;

int				gSceneStatus;
KTime gPeriod, gStart, gStop, gCurrentTime;
//KFbxScene* gScene;

enum { UNLOADED, MUST_BE_LOADED, MUST_BE_REFRESHED, REFRESHED };

Mesh::Mesh()
{
	Matrice = new GLfloat[16];
	Matrice[0] = 1.f;
	Matrice[1] = 0.f;
	Matrice[2] = 0.f;
	Matrice[3] = 0.f;
	Matrice[4] = 0.f;
	Matrice[5] = 1.f;
	Matrice[6] = 0.f;
	Matrice[7] = 0.f;
	Matrice[8] = 0.f;
	Matrice[9] = 0.f;
	Matrice[10] = 1.f;
	Matrice[11] = 0.f;
	Matrice[12] = 0.f;
	Matrice[13] = 0.f;
	Matrice[14] = 0.f;
	Matrice[15] = 1.f;
}

Mesh::~Mesh()
{
	size_t	i;
	size_t	size;

	i = 0;
	while (this->pol[i] != NULL)
	{
		delete this->pol[i];
		++i;
	}
	delete this->Matrice;
	i = 0;
	while (this->ControlPoint[i] != NULL)
	{
		delete
		this->ControlPoint[i];
		++i;
	}
	i = 0;
	size = this->Mat.size();
	while (i < size)
	{
		delete this->Mat[i];
		++i;
	}
}

void	Mesh::AnimInit(KFbxScene* gScene)
{
	int i;

	// Create the submenu to select the current animation stack.
	int lCurrentAnimStackIndex = 0;

	// Add the animation stack names.
	for (i = 0; i < gAnimStackNameArray.GetCount(); i++)
	{
		// Track the current animation stack index.
		if (gAnimStackNameArray[i]->Compare(KFbxGet<KString>(gScene->ActiveAnimStackName)) == 0)
		{
			lCurrentAnimStackIndex = i;
		}
		AnimStackSelectionCallback(lCurrentAnimStackIndex, gScene);
	}
}

void	Mesh::AnimStackSelectionCallback(int pItem, KFbxScene* gScene)
{
	int lNbAnimStacks = gAnimStackNameArray.GetCount();
	if (!lNbAnimStacks || pItem >= lNbAnimStacks)
	{
		return;
	}

	// select the base layer from the animation stack
	gCurrentAnimationStack = gScene->FindMember(FBX_TYPE(KFbxAnimStack), gAnimStackNameArray[pItem]->Buffer());
	if (gCurrentAnimationStack == NULL)
	{
		// this is a problem. The anim stack should be found in the scene!
		return;
	}

	// we assume that the first animation layer connected to the animation stack is the base layer
	// (this is the assumption made in the FBXSDK)
	gCurrentAnimationLayer = gCurrentAnimationStack->GetMember(FBX_TYPE(KFbxAnimLayer), 0);
	gScene->GetEvaluator()->SetContext(gCurrentAnimationStack);

	KFbxTakeInfo* lCurrentTakeInfo = gScene->GetTakeInfo(*(gAnimStackNameArray[pItem]));
	if (lCurrentTakeInfo)
	{
		gStart = lCurrentTakeInfo->mLocalTimeSpan.GetStart();
		gStop = lCurrentTakeInfo->mLocalTimeSpan.GetStop();
	}
	else
	{
		// Take the time line value
		KTimeSpan lTimeLineTimeSpan;
		gScene->GetGlobalSettings().GetTimelineDefaultTimeSpan(lTimeLineTimeSpan);

		gStart = lTimeLineTimeSpan.GetStart();
		gStop  = lTimeLineTimeSpan.GetStop();
	}

	gCurrentTime = gStart;

	// Set the scene status flag to refresh 
	// the scene in the next timer callback.
	gSceneStatus = MUST_BE_REFRESHED;
}

void	Mesh::FillControlPoint(KFbxMesh* mesh)
{
	size_t	size;
	size_t	i;


	size = mesh->mControlPoints.GetCount();
	i = 0;
	this->ControlPoint = new Point*[size];

	while (i < size)
	{
		this->ControlPoint[i] = new Point(mesh->mControlPoints[i][0],mesh->mControlPoints[i][1],mesh->mControlPoints[i][2]);
		++i;
	}

}

void	Mesh::FillControlPoint(Point** CP, int nb)
{
	int	i;

	this->ControlPoint = new Point*[nb];
	i = 0;
	while (i < nb)
	{
		this->ControlPoint[i] = CP[i];
		++i;
	}
}

void	Mesh::FillMesh(int nb)
{
	int	i;

	this->pol = new Polygon* [3];
	i = 0;
	while (i < nb)
	{
		this->pol[i] = new Polygon(3);
		this->pol[0]->Mesh[i] = this->ControlPoint[i];

		++i;
	}
	this->pol[0]->Mesh[i] = NULL;
	this->pol[i] = NULL;
}

void	Mesh::TestDraw(KFbxNode* Node, KFbxMesh* mesh)
{
	int		lClusterCount;
	int		lSkinCount;
	int		lVertexCount;
	KFbxVector4* 	lVertexArray; 

	KTime		pTime;	//a voir
	KFbxXMatrix	pGlobalPosition;
	KFbxXMatrix	pParentGlobalPosition;
	//a voir	


	KFbxPose* 	pPose;	//a voir

	KFbxXMatrix lGlobalPosition = GetGlobalPosition(Node, pTime, &pParentGlobalPosition);

	KFbxXMatrix lGeometryOffset = GetGeometry(Node);
	KFbxXMatrix lGlobalOffPosition  = (pGlobalPosition * lGeometryOffset);

	pPose = NULL;
	lClusterCount = 0;
	lSkinCount= 0;
	lVertexCount = mesh->GetControlPointsCount();
	if (lVertexCount == 0)
		return;
	lVertexArray = new KFbxVector4[lVertexCount];
	memcpy(lVertexArray, mesh->GetControlPoints(), lVertexCount * sizeof(KFbxVector4));

	if (mesh->GetDeformerCount(KFbxDeformer::eVERTEX_CACHE) &&
			(static_cast<KFbxVertexCacheDeformer*>(mesh->GetDeformer(0, KFbxDeformer::eVERTEX_CACHE)))->IsActive())
		ReadVertexCacheData(mesh, pTime, lVertexArray);
	else
	{
		if (mesh->GetShapeCount())
			ComputeShapeDeformation(mesh, pTime, lVertexArray);

		lSkinCount = mesh->GetDeformerCount(KFbxDeformer::eSKIN);
		for( int i=0; i< lSkinCount; i++)
			lClusterCount += ((KFbxSkin *)(mesh->GetDeformer(i, KFbxDeformer::eSKIN)))->GetClusterCount();
		if (lClusterCount)
		{
			ComputeSkinDeformation(pGlobalPosition, mesh, pTime, lVertexArray, pPose);
		}
	}

	//copy vetex array
//	GlDrawMesh(pGlobalPosition, lMesh, lVertexArray);

	delete [] lVertexArray;
}

void Mesh::ComputeSkinDeformation(KFbxXMatrix& pGlobalPosition, 
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

void Mesh::ComputeShapeDeformation(KFbxMesh* pMesh, KTime& pTime, KFbxVector4* pVertexArray)
{
	int		lVertexCount;
	KFbxVector4*	lSrcVertexArray;
	KFbxVector4*	lDstVertexArray;
	int		lBlendShapeDeformerCount; 

	lVertexCount = pMesh->GetControlPointsCount();
	lSrcVertexArray = pVertexArray;
	lDstVertexArray = new KFbxVector4[lVertexCount];
	memcpy(lDstVertexArray, pVertexArray, lVertexCount * sizeof(KFbxVector4));

	lBlendShapeDeformerCount = pMesh->GetDeformerCount(KFbxDeformer::eBLENDSHAPE);
	for(int lBlendShapeIndex = 0; lBlendShapeIndex<lBlendShapeDeformerCount; ++lBlendShapeIndex)
	{
		KFbxBlendShape* lBlendShape;
		lBlendShape = (KFbxBlendShape*)pMesh->GetDeformer(lBlendShapeIndex, KFbxDeformer::eBLENDSHAPE);

		int lBlendShapeChannelCount;

		lBlendShapeChannelCount = lBlendShape->GetBlendShapeChannelCount();
		for(int lChannelIndex = 0; lChannelIndex<lBlendShapeChannelCount; ++lChannelIndex)
		{
			KFbxBlendShapeChannel* lChannel;
			lChannel = lBlendShape->GetBlendShapeChannel(lChannelIndex);

			if(lChannel)
			{
				KFbxAnimCurve*	lFCurve;

	//			lFCurve = NULL;
				lFCurve = pMesh->GetShapeChannel(lBlendShapeIndex, lChannelIndex, gCurrentAnimationLayer);

				if (!lFCurve)
					continue;
				double lWeight;
				int lShapeCount;
				double* lFullWeights;

				lWeight = lFCurve->Evaluate(pTime);
				lShapeCount = lChannel->GetTargetShapeCount();
				lFullWeights = lChannel->GetTargetShapeFullWeights();
				for(int lShapeIndex = 0; lShapeIndex<lShapeCount; ++lShapeIndex)
				{
					KFbxShape* lShape;
					lShape = NULL;

					if(lWeight > 0 && lWeight < lFullWeights[0])
						lShape = lChannel->GetTargetShape(0);
					if(lWeight > lFullWeights[lShapeIndex] && lWeight < lFullWeights[lShapeIndex + 1])
						lShape = lChannel->GetTargetShape(lShapeIndex+1);
					if(lShape)
					{               
						for (int j = 0; j < lVertexCount; j++)
						{
							KFbxVector4 lInfluence;

							lInfluence = (lShape->GetControlPoints()[j] - lSrcVertexArray[j]) * lWeight * 0.01;
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


void	 Mesh::ReadVertexCacheData(KFbxMesh* pMesh, KTime& pTime, KFbxVector4* pVertexArray)
{
	KFbxVertexCacheDeformer* lDeformer;
	KFbxCache*               lCache;
	int                      lChannelIndex;
	unsigned int             lVertexCount;
	bool                     lReadSucceed;
	double*                  lReadBuf;

	lDeformer     = static_cast<KFbxVertexCacheDeformer*>(pMesh->GetDeformer(0, KFbxDeformer::eVERTEX_CACHE));

	lCache        = lDeformer->GetCache();
	lChannelIndex = -1;
	lVertexCount  = (unsigned int)pMesh->GetControlPointsCount();
	lReadSucceed  = false;
	lReadBuf      = new double[3*lVertexCount];

	if (lCache->GetCacheFileFormat() == KFbxCache::eMC)
	{
		if ((lChannelIndex = lCache->GetChannelIndex(lDeformer->GetCacheChannel())) > -1)
			lReadSucceed = lCache->Read(lChannelIndex, pTime, lReadBuf, lVertexCount);
	}
	else
		lReadSucceed = lCache->Read((unsigned int)pTime.GetFrame(true), lReadBuf, lVertexCount);
	if (lReadSucceed)
	{
		unsigned int lReadBufIndex;

		lReadBufIndex = 0;
		while (lReadBufIndex < 3*lVertexCount)
		{
			pVertexArray[lReadBufIndex/3].SetAt(0, lReadBuf[lReadBufIndex]); lReadBufIndex++;
			pVertexArray[lReadBufIndex/3].SetAt(1, lReadBuf[lReadBufIndex]); lReadBufIndex++;
			pVertexArray[lReadBufIndex/3].SetAt(2, lReadBuf[lReadBufIndex]); lReadBufIndex++;
		}
	}
	delete [] lReadBuf;
}

void Mesh::MatrixScale(KFbxXMatrix& pMatrix, double pValue)
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


void Mesh::MatrixAddToDiagonal(KFbxXMatrix& pMatrix, double pValue)
{
	pMatrix[0][0] += pValue;
	pMatrix[1][1] += pValue;
	pMatrix[2][2] += pValue;
	pMatrix[3][3] += pValue;
}

void Mesh::MatrixAdd(KFbxXMatrix& pDstMatrix, KFbxXMatrix& pSrcMatrix)
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

void Mesh::ComputeDualQuaternionDeformation(KFbxXMatrix& pGlobalPosition, 
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
void	Mesh::ComputeClusterDeformation(KFbxXMatrix& pGlobalPosition, 
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



void Mesh::ComputeLinearDeformation(KFbxXMatrix& pGlobalPosition, 
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



void	Mesh::FillMesh(KFbxMesh* mesh)
{

	int			i;
	int			nbpol;
	int			j;
	int			polsize;
	int			index;
	int			Vid;

	Vid = 0;
	j = 0;
	nbpol = mesh->GetPolygonCount();
	this->pol = new Polygon* [nbpol + 1];
	while (j < nbpol)
	{
		i = 0;
		polsize = mesh->GetPolygonSize(j);
		this->pol[j] = new Polygon(polsize);
//		std::cout<<"polsize"<<polsize<<std::endl;
		while (i < polsize)
		{
			index = mesh->GetPolygonVertex(j, i);
			this->pol[j]->Mesh[i] = this->ControlPoint[index];
			this->LoadNormal(index, Vid, mesh, this->ControlPoint[index]);
			++i;
			++Vid;
		}
		this->pol[j]->Mesh[i] = NULL;
		++j;
	}
	this->pol[j] = NULL;
//	this->CalcDist();
//	this->CalcCenter();

}

float*	Multiply(StaticObj* obj, float* vect)
{
	float*		test;
//	GLfloat*	mat;
	test = new float[4];
	float*		res;

	res = obj->m->GetMatrice();
/*	rotz[0] = res[0];
	rotz[1] = res[1];
	rotz[2] = res[2];
	rotz[3] = res[3];
	rotz[4] = res[4];
	rotz[5] = res[5];
	rotz[6] = res[6];
	rotz[7] = res[7];
	rotz[8] = res[8];
	rotz[9] = res[9];
	rotz[10] = res[10];
	rotz[11] = res[11];
	rotz[12] = res[12];
	rotz[13] = res[13];
	rotz[14] = res[14];
	rotz[15] = res[15];
*/
//	m3dLoadIdentity44(identi);
//
//	m3dTranslationMatrix44(mat, obj->pos[0], obj->pos[1],obj->pos[2]);


//	m3dRotationMatrix44(rotx, obj->rot[0] , 1.0f, 0.0f, 0.0f);

//	m3dRotationMatrix44(roty, obj->rot[1] -90, 0.0f, 1.0f, 0.0f);
//	m3dRotationMatrix44(rotz, obj->rot[2], 0.0f, 0.0f, 1.0f);


//	m3dScaleMatrix44(scale, obj->scale[0], obj->scale[1], obj->scale[2]);

//	m3dMatrixMultiply44(res, identi, mat);

//	m3dMatrixMultiply44(res, identi, rotx);
//	m3dMatrixMultiply44(res, res, roty);
//	m3dMatrixMultiply44(res, res, rotz);


//	if (obj->scale[0] != 0 || obj->scale[1] != 0 || obj->scale[2] != 0)
//		m3dMatrixMultiply44(res, res, scale);

//	m3dMatrixMultiply44(res, identi, rotx);
//	m3dMatrixMultiply44(res, res, roty);
//	m3dMatrixMultiply44(res, res, rotz);

//	m3dMatrixMultiply44(res, res, mat);
//	m3dMatrixMultiply44(res, res, rotz);
//	if (obj->scale[0] != 0 || obj->scale[1] != 0 || obj->scale[2] != 0)
//	m3dMatrixMultiply44(res, res, scale);


//	res = identi;



	test[0] = res[0] * vect[0] + res[1] * vect[1] + res[2] * vect[2] + res[3] * vect[3];
	test[1] = res[4] * vect[0] + res[5] * vect[1] + res[6] * vect[2] + res[7] * vect[3];
	test[2] = res[8] * vect[0] + res[9] * vect[1] + res[10] * vect[2] + res[11] * vect[3];
	test[3] = res[12] * vect[0] + res[13] * vect[1] + res[14] * vect[2] + res[15] * vect[3];

	return (test);
}
void	Mesh::CalcDist(StaticObj* obj)
{
	size_t	i;
	size_t	j;
	Vec3f	p;
	float	DistMax;
	float	Calc;
	Vec3f	p2;
	Vec3f	Center;
	float	x;
	float	y;
	float	z;
	int	nb_hit = 0;

	x = 0;
	y = 0;
	z = 0;
	i = 0;
	Calc = 0;
	while (this->pol[i] != NULL)
	{
		j = 0;
		DistMax = -1;
		while (j < this->pol[i]->size )
		{
			p = this->pol[i]->Mesh[j]->GetPoint();
			if (this->pol[i]->Mesh[j + 1] != NULL)
			{
				p2 = this->pol[i]->Mesh[j + 1]->GetPoint();
			//	if (obj->scale[0] != 0)
			//		x = ((p[0] - p2[0]) * obj->scale[0]) * ((p[0] - p2[0]) * obj->scale[0]);
			//	else
					x = (p[0] - p2[0])  * (p[0] - p2[0]);
			//	if (obj->scale[1] != 0)
			//		y = ((p[1] - p2[1]) * obj->scale[1]) * ((p[1] - p2[1]) * obj->scale[1]);
			//	else
					y = (p[1] - p2[1])  * (p[1] - p2[1]);
			//	if (obj->scale[1] != 0)
			//		z = ((p[2] - p2[2]) * obj->scale[2]) * ((p[2] - p2[2]) * obj->scale[2]);
			//	else
					z = (p[2] - p2[2])  * (p[2] - p2[2]);

			//	std::cout<<"x "<<x <<" y "<<y <<" z "<<z <<std::endl;
				Calc = sqrtf(ABS(x + y + z));
	//			Calc = sqrtf(ABS((p[0] - p2[0]) + (p[1] - p2[1]) + (p[2] - p2[2])));
			}
			if (Calc > DistMax)
				DistMax = Calc;
			++j;
		}
//		Center = this->CalcCenter(this->pol[i]);
		if (DistMax > 0)
		{
			float*	test;
			float*	res;

			test = new float[4];
			Center = this->CalcCenter(this->pol[i]);


			test[0] = Center[0];
			test[1] = Center[1];
			test[2] = Center[2];
			test[3] = 0.0f;
			res = Multiply(obj, test);


			Center[0] = res[0];
			Center[1] = res[1];
			Center[2] = res[2];

			
			obj->AddHitbox(new HitBox((DistMax), Center, obj, nb_hit));
			nb_hit++;
		}
		++i;
	}
}


Vec3f	Mesh::CalcCenter(Polygon* pol)
{
	Vec3f	Center;
	Vec3f	P1;
	Vec3f	P2;
	Vec3f	P3;
	int	i;
	float*	test;

	test = new float[4];

	i = 0;
	P1 = pol->Mesh[0]->GetPoint();
	P2 = pol->Mesh[1]->GetPoint();
	P3 = pol->Mesh[2]->GetPoint();


	Center[0] = (P1[0] + P2 [0] + P3[0]) / 3;
	Center[1] = (P1[1] + P2 [1] + P3[1]) / 3;
	Center[2] = (P1[2] + P2 [2] + P3[2]) / 3;

	test[0] = Center[0];
	test[1] = Center[1];
	test[2] = Center[2];
	test[3] = 1.0f;

	
	return (Center);
}


void	Mesh::Draw(void)
{
	size_t	i;
	size_t	j;
	Vec3f	p;
	Vec3f	n;
	
	i = 0;
	while (this->pol[i] != NULL)
	{
		j = 0;
		glBegin(GL_POLYGON);
		while (this->pol[i]->Mesh[j] != NULL)
		{
			glColor3f(1.0f, 0.0f, 0.0f);
			p = this->pol[i]->Mesh[j]->GetPoint();
			n = this->pol[i]->Mesh[j]->GetNormal();
			glNormal3f(n[0], n[1], n[2]);
			glVertex3f(p[0], p[1], p[2]);
			++j;
		}
		++i;
		glEnd();
	}

}


void	Mesh::FillMat(KFbxXMatrix& mat)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			this->Matrice[i * 4 +j] = mat[i][j];
			++j;
		}
		++i;
	}
}

void	Mesh::LoadNormal(int id, int vertexId, KFbxMesh* pMesh, Point* B)
{
	for(int  l = 0; l < pMesh->GetElementNormalCount(); ++l)
	{
		KFbxGeometryElementNormal* leNormal = pMesh->GetElementNormal( l);
		if(leNormal->GetMappingMode() == KFbxGeometryElement::eBY_POLYGON_VERTEX)
		{
			switch (leNormal->GetReferenceMode())
			{
				case KFbxGeometryElement::eDIRECT:
					B->SetNormal((leNormal->GetDirectArray().GetAt(vertexId))[0],
						    (leNormal->GetDirectArray().GetAt(vertexId))[1],
						    (leNormal->GetDirectArray().GetAt(vertexId))[2]);
					break;
				case KFbxGeometryElement::eINDEX_TO_DIRECT:
					{
						int _id;
						_id = leNormal->GetIndexArray().GetAt(vertexId);
						B->SetNormal((leNormal->GetDirectArray().GetAt(id))[0], 
							    (leNormal->GetDirectArray().GetAt(id))[1],
							    (leNormal->GetDirectArray().GetAt(id))[2]);
					}
					break;
				default:
					break; // other reference modes not shown here!
			}
		}
	}
}


