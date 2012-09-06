#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <fbxsdk.h>

class TextureManager
{
	public:
		TextureManager(const KString & pWorkingDir) : mWorkingDir(pWorkingDir) {}
		~TextureManager();

		void Clear();

		bool LoadTexture(const KFbxFileTexture * pTexture, unsigned int * pTextureObject = NULL);

	private:
		bool LoadTextureFromFile(const KString & pFilePath, unsigned int & pTextureObject);

		typedef KMap<const KFbxFileTexture *, unsigned int> TextureMapType;
		TextureMapType mTextureMap;
		KString mWorkingDir;
};

class ShadingManager
{
	public:
		enum ShadingMode
		{
			SHADING_MODE_WIREFRAME,
			SHADING_MODE_SHADED,
		};

		ShadingManager(const KString & pWorkingDir);
		~ShadingManager();

		void Initialize(const KFbxScene * pScene);
		void InitializeForOneFrame() const;

		ShadingMode GetShadingMode() const { return mShadingMode; }
		void SetShadingMode(ShadingMode pShadingMode) { mShadingMode = pShadingMode; }

		bool IsDrawNormal() const { return mDrawNormal; }
		void SetDrawNormal(bool pValue) { mDrawNormal = pValue; }

		double GetNormalScale() const { return mNormalScale; }
		void SetNormalScale(double pValue) { mNormalScale = pValue; }

		void SetMaterial(const KFbxNode * pNode, int pMaterialIndex) const;

		// Call glMultMatrix to set the transformation before calling SetLight
		void SetLight(KFbxLight::ELightType pType, const KFbxColor & pColor, double pSpotCutoff = 0) const;

	private:
		void Initialize(const KFbxNode * pNode);

		void SetMaterialProperty(const KFbxSurfaceMaterial * pMaterial,
				const char * pPropertyName, const char * pFactorPropertyName,
				unsigned int pOGLProperty) const;

		TextureManager * mTextureManager;
		ShadingMode mShadingMode;

		bool mDrawNormal;
		double mNormalScale;

		typedef KMap<const KFbxSurfaceMaterial *, unsigned int> TextureObjectsForMaterialType;
		TextureObjectsForMaterialType mTextureObjectsForMaterial;

		// For cache
		mutable const KFbxSurfaceMaterial * mLastMaterial;
		mutable unsigned int mLastTextureObject;

		mutable int mLightCount;
		int mOGLMaxLight;
};

#endif // #ifndef _TEXTURE_H
