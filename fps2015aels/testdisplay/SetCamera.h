#ifndef _SET_CAMERA_H
#define _SET_CAMERA_H

void SetCamera(KFbxScene* pScene, 
		KTime& pTime, 
		KFbxAnimLayer* pAnimLayer,
		KArrayTemplate<KFbxNode*>& pCameraArray);

KFbxCamera* GetCurrentCamera(KFbxScene* pScene);

void CameraZoomIn(KFbxScene* pScene, int dY);

void CameraZoomOut(KFbxScene* pScene, int dY);

void CameraOrbit(KFbxScene* pScene, KFbxVector4 lOrigCamPos, double OrigRoll, int dX, int dY);

void CameraPan(KFbxScene* pScene, KFbxVector4 lOrigCamPos, KFbxVector4 lOrigCamCenter, 
		double OrigRoll, int dX, int dY);

KFbxCamera* GetCurrentCamera(KFbxScene* pScene, 
		KTime& pTime, 
		KArrayTemplate<KFbxNode*>& pCameraArray);
void GetCameraAnimatedParameters(KFbxNode* pNode, 
		KTime& pTime);
bool IsProducerCamera(KFbxScene*  pScene, KFbxCamera* pCamera);

 

#endif // #ifndef _SET_CAMERA_H

