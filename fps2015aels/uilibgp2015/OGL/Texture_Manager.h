#ifndef _TEXTURE_MANAGER_H__
#define _TEXTURE_MANAGER_H__

#ifndef	__MAKE_H
#include <map>
#include <string.h>
#endif

#include "Singleton.hpp"

namespace	ID
{
	class	StrCompare
	{
	public:
		inline int	operator()(char const* pKeyA, char const* pKeyB) const
		{
			return strcmp(pKeyA, pKeyB);
		}
	};

	class	Texture_Manager : public ID::Singleton<Texture_Manager>
	{
		friend class	ID::Singleton<Texture_Manager>;
	public:
		Texture_Manager();
		~Texture_Manager();

		void	Clear();
		bool	LoadTexture(const char* pTexture, unsigned int* pTextureObject);

	private:
		bool	LoadTextureFromFile(const char* pFilePath, unsigned int & pTextureObject);

		typedef std::map<const char*, unsigned int, StrCompare> TextureMapType;

		TextureMapType	mTextureMap;
	};
};
/*
class	ShadingManager
{
public:
	enum ShadingMode
	{
		SHADING_MODE_WIREFRAME,
		SHADING_MODE_SHADED,
	};

	ShadingManager();
	~ShadingManager();

	bool	LoadTexture(const char* filename, unsigned int* textureID);
	void	SetWorkingdir(const KString& pWorkingDir);
	void	Initialize(const KFbxScene* pScene);
	void	InitializeForOneFrame() const;

    ShadingMode GetShadingMode() const { return mShadingMode; }
    void SetShadingMode(ShadingMode pShadingMode) { mShadingMode = pShadingMode; }

    bool IsDrawNormal() const { return mDrawNormal; }
    void SetDrawNormal(bool pValue) { mDrawNormal = pValue; }

    double GetNormalScale() const { return mNormalScale; }
    void SetNormalScale(double pValue) { mNormalScale = pValue; }

    void SetMaterial(const KFbxNode* pNode, int pMaterialIndex) const;

    // Call glMultMatrix to set the transformation before calling SetLight
    void SetLight(KFbxLight::ELightType pType, const KFbxColor & pColor, double pSpotCutoff = 0) const;

private:
    void Initialize(const KFbxNode* pNode);

    void SetMaterialProperty(const KFbxSurfaceMaterial* pMaterial,
        const char* pPropertyName, const char* pFactorPropertyName,
        unsigned int pOGLProperty) const;

    Texture_Manager* mTexture_Manager;
    ShadingMode mShadingMode;
    
    bool mDrawNormal;
    double mNormalScale;

    typedef KMap<const KFbxSurfaceMaterial*, unsigned int> TextureObjectsForMaterialType;
    TextureObjectsForMaterialType mTextureObjectsForMaterial;

    // For cache
    mutable const KFbxSurfaceMaterial* mLastMaterial;
    mutable unsigned int mLastTextureObject;

    mutable int mLightCount;
    int mOGLMaxLight;
};
*/
#endif

