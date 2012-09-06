#ifndef ShadingManager_h
#define	ShadingManager_h
#include <fbxsdk.h>

enum ShadingMode
{
	SHADING_MODE_WIREFRAME,
	SHADING_MODE_SHADED,
};

class ShadingManager
{
	public:
		ShadingManager(const KString & pWorkingDir);
		~ShadingManager();
		void	Initialize(const KFbxScene * pScene);
		void	InitializeForOneFrame() const;
		ShadingMode	GetShadingMode() const { return mShadingMode; }
		void	SetShadingMode(ShadingMode pShadingMode) { mShadingMode = pShadingMode; }
		bool	IsDrawNormal() const { return mDrawNormal; }
		void	SetDrawNormal(bool pValue) { mDrawNormal = pValue; }
		double	GetNormalScale() const { return mNormalScale; }
		void	SetNormalScale(double pValue) { mNormalScale = pValue; }
		void	SetMaterial(const KFbxNode * pNode, int pMaterialIndex) const;
		void	SetLight(KFbxLight::ELightType pType, const KFbxColor & pColor, double pSpotCutoff = 0) const;
	private:
		void	Initialize(const KFbxNode * pNode);
		void	SetMaterialProperty(const KFbxSurfaceMaterial * pMaterial,
				const char * pPropertyName, const char * pFactorPropertyName,
				unsigned int pOGLProperty) const;

	private:

		typedef KMap<const KFbxSurfaceMaterial *, unsigned int> TextureObjectsForMaterialType;


		TextureManager*				mTextureManager;
		ShadingMode				mShadingMode;
		bool					mDrawNormal;
		double					mNormalScale;
		TextureObjectsForMaterialType		mTextureObjectsForMaterial;

		mutable const KFbxSurfaceMaterial*	mLastMaterial;
		mutable unsigned int			mLastTextureObject;
		mutable int				mLightCount;
		int					mOGLMaxLight;
};


#endif
