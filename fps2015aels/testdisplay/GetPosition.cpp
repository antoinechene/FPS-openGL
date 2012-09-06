#include <fbxsdk.h>
#include <math.h>
#include <fbxfilesdk/fbxfilesdk_nsuse.h>
#include "GetPosition.h"

KFbxXMatrix GetGlobalPosition(KFbxNode* pNode, KTime& pTime, KFbxXMatrix* pParentGlobalPosition)
{
	return pNode->EvaluateGlobalTransform(pTime);
}

KFbxXMatrix GetGlobalPosition(KFbxNode* pNode, KTime& pTime, KFbxPose* pPose, KFbxXMatrix* pParentGlobalPosition)
{
	KFbxXMatrix lGlobalPosition;
	bool        lPositionFound = false;

	if (pPose)
	{
		int lNodeIndex = pPose->Find(pNode);

		if (lNodeIndex > -1)
		{
			if (pPose->IsBindPose() || !pPose->IsLocalMatrix(lNodeIndex))
			{
				lGlobalPosition = GetPoseMatrix(pPose, lNodeIndex);
			}
			else
			{
				KFbxXMatrix lParentGlobalPosition;

				if (pParentGlobalPosition)
				{
					lParentGlobalPosition = *pParentGlobalPosition;
				}
				else
				{
					if (pNode->GetParent())
					{
						lParentGlobalPosition = GetGlobalPosition(pNode->GetParent(), pTime, pPose);
					}
				}
				KFbxXMatrix lLocalPosition = GetPoseMatrix(pPose, lNodeIndex);
				lGlobalPosition = lParentGlobalPosition * lLocalPosition;
			}

			lPositionFound = true;
		}
	}
	if (!lPositionFound)
	{
		lGlobalPosition = GetGlobalPosition(pNode, pTime, pParentGlobalPosition);
	}
	return lGlobalPosition;
}

KFbxXMatrix GetPoseMatrix(KFbxPose* pPose, int pNodeIndex)
{
	KFbxXMatrix lPoseMatrix;
	KFbxMatrix lMatrix = pPose->GetMatrix(pNodeIndex);

	memcpy((double*)lPoseMatrix, (double*)lMatrix, sizeof(lMatrix.mData));

	return lPoseMatrix;
}

KFbxXMatrix GetGeometry(KFbxNode* pNode) {
	KFbxVector4 lT, lR, lS;
	KFbxXMatrix lGeometry;

	lT = pNode->GetGeometricTranslation(KFbxNode::eSOURCE_SET);
	lR = pNode->GetGeometricRotation(KFbxNode::eSOURCE_SET);
	lS = pNode->GetGeometricScaling(KFbxNode::eSOURCE_SET);

	lGeometry.SetT(lT);
	lGeometry.SetR(lR);
	lGeometry.SetS(lS);

	return lGeometry;
}

