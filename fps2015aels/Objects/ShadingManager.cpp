#include "ShadingManager.h"


ShadingManager::ShadingManager(const KString & pWorkingDir): mTextureManager(new TextureManager(pWorkingDir)), mShadingMode(SHADING_MODE_SHADED),
	mDrawNormal(false), mNormalScale(1), mLastMaterial(NULL), mLastTextureObject(0),
	mLightCount(0), mOGLMaxLight(0)
{

}

ShadingManager::~ShadingManager()
{
	delete mTextureManager;
}

void ShadingManager::Initialize(const KFbxScene * pScene)
{
	if (!pScene)
		return;

	mTextureManager->Clear();
	Initialize(pScene->GetRootNode());

	glGetIntegerv(GL_MAX_LIGHTS, &mOGLMaxLight);
}

