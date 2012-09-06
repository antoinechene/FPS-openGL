#ifndef Scene_h
#define Scene_h
#include <fbxsdk.h>

class	ShadingManager;
class Scene
{
	public:
		Scene();
		~Scene();

	private:
		KFbxScene*			gScene;
		KFbxAnimStack*			gCurrentAnimationStack; 
		KFbxAnimLayer*			gCurrentAnimationLayer;
		int				gSceneStatus;
		ShadingManager*			gShadingManager;
		KArrayTemplate<KFbxPose*>	gPoseArray;
		KArrayTemplate<KFbxNode*>	gCameraArray;
		KArrayTemplate<KString*>	gAnimStackNameArray;
		int				gPoseIndex;


};

#endif
