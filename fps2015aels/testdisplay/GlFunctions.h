#ifndef _GL_FUNCTIONS_H
#define _GL_FUNCTIONS_H

void GlGetWindowSize(int& pWidth, int& pHeight);

void GlSetCameraPerspective(double pFieldOfViewY,
		double pAspect,
		double pNearPlane,
		double pFarPlane,
		KFbxVector4& pEye,
		KFbxVector4& pCenter,
		KFbxVector4& pUp);
void GlSetCameraOrthogonal(double pLeftPlane,
		double pRightPlane,
		double pBottomPlane,
		double pTopPlane,
		double pNearPlane,
		double pFarPlane,
		KFbxVector4& pEye,
		KFbxVector4& pCenter,
		KFbxVector4& pUp);

void GlDrawMarker(KFbxXMatrix& pGlobalPosition);
void GlDrawLimbNode(KFbxXMatrix& pGlobalBasePosition, 
		KFbxXMatrix& pGlobalEndPosition);
void GlDrawMesh(const KFbxXMatrix &pGlobalPosition, 
		const KFbxMesh* pMesh, 
		const KFbxVector4* pVertexArray);
void GlDrawCamera(KFbxXMatrix& pGlobalPosition, 
		double pRoll);
void GlDrawLight(const KFbxXMatrix& pGlobalPosition, const KFbxLight* pLight,
		const KFbxColor& pColor, double pConeAngle);
void GlDrawCrossHair(KFbxXMatrix& pGlobalPosition);
void GlDrawGrid(KFbxXMatrix& pGlobalPosition);

#endif // #ifndef _GL_FUNCTIONS_H

