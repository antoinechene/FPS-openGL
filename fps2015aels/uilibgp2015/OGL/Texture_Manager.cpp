#include "Texture_Manager.h"
#include "targa.h"

#ifndef	__MAKE_H
#include <string.h>
#include <GL/glut.h>
#endif

ID::Texture_Manager::Texture_Manager()
{
}

ID::Texture_Manager::~Texture_Manager()
{
	TextureMapType::iterator	it;
	TextureMapType::iterator	end;

	it = this->mTextureMap.begin();
	end = this->mTextureMap.end();
	while (it != end)
	{
		if (glIsTexture((*it).second))
			glDeleteTextures(1, &((*it).second));
		++it;
	}
}

void	ID::Texture_Manager::Clear()
{
	mTextureMap.clear();
}

bool	ID::Texture_Manager::LoadTexture(const char* filename, unsigned int* pTextureObject)
{
	TextureMapType::iterator	lTextureRecord = mTextureMap.find(filename);
	unsigned int			lTextureObject = 0;

	if (lTextureRecord != this->mTextureMap.end())
	{
		*pTextureObject = (*lTextureRecord).second;
		return true;
	}
	if (LoadTextureFromFile(filename, lTextureObject) && glIsTexture(lTextureObject))
	{
		mTextureMap.insert(std::pair<const char*, unsigned int>(filename, lTextureObject));
		if (pTextureObject)
			*pTextureObject = lTextureObject;
		return true;
	}
	return false;
}

bool	ID::Texture_Manager::LoadTextureFromFile(const char* filename, unsigned int & pTextureObject)
{
	int	len;

	len = strlen(filename);
	if (len < 4)
		return false;
	if (strcmp(filename + len - 3, "TGA") == 0 ||
	    strcmp(filename + len - 3, "tga") == 0)
	{
		tga_image lTGAImage;

		if (tga_read(&lTGAImage, filename) == TGA_NOERR)
		{
			// Make sure the image is left to right
			if (tga_is_right_to_left(&lTGAImage))
				tga_flip_horiz(&lTGAImage);

			// Make sure the image is bottom to top
			if (tga_is_top_to_bottom(&lTGAImage))
				tga_flip_vert(&lTGAImage);

			// Make the image BGR 24
			tga_convert_depth(&lTGAImage, 24);

			glGenTextures(1, &pTextureObject);
			glBindTexture(GL_TEXTURE_2D, pTextureObject);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glTexImage2D(GL_TEXTURE_2D, 0, 3,
				     lTGAImage.width, lTGAImage.height,
				     0, GL_BGR, GL_UNSIGNED_BYTE, lTGAImage.image_data);
			tga_free_buffers(&lTGAImage);
			return true;
		}
	}
	return false;
}
/*
ShadingManager::ShadingManager() : mTexture_Manager(new Texture_Manager),
				   mShadingMode(SHADING_MODE_SHADED),
				   mDrawNormal(false),
				   mNormalScale(1),
				   mLastMaterial(NULL),
				   mLastTextureObject(0),
				   mLightCount(0),
				   mOGLMaxLight(0)
{
	glGetIntegerv(GL_MAX_LIGHTS, &mOGLMaxLight);
	mTexture_Manager->Clear();
}

ShadingManager::~ShadingManager()
{
	delete mTexture_Manager;
}

bool	ShadingManager::LoadTexture(const char* filename, unsigned int* textureID)
{
	return this->mTexture_Manager->LoadTexture(filename, textureID);
}

void	ShadingManager::SetWorkingdir(const KString& pWorkingDir)
{
	this->mTexture_Manager->SetWorkingdir(pWorkingDir);
}

void 	ShadingManager::Initialize(const KFbxScene* pScene)
{
	if (!pScene)
		return ;
	this->Initialize(pScene->GetRootNode());
}

void	ShadingManager::Initialize(const KFbxNode* pNode)
{
	if (!pNode)
		return ;
	if (pNode->GetNodeAttribute())
	{
		const int lMaterialCount = pNode->GetMaterialCount();
		for (int lMaterialIndex = 0; lMaterialIndex < lMaterialCount; ++lMaterialIndex)
		{
			const KFbxSurfaceMaterial* lMaterial = pNode->GetMaterial(lMaterialIndex);
			if (!lMaterial)
				continue ;
			const KFbxProperty lProperty = lMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
			if (!lProperty.IsValid())
				continue ;
			const int lTextureCount = lProperty.GetSrcObjectCount(KFbxFileTexture::ClassId);
			if (!lTextureCount)
				continue ;
			const KFbxFileTexture* lTexture = lProperty.GetSrcObject(FBX_TYPE(KFbxFileTexture), 0);
			if (lTexture)
			{
				unsigned int lTextureObject;
				mTexture_Manager->LoadTexture(lTexture->GetFileName(), &lTextureObject);
				mTextureObjectsForMaterial.Insert(lMaterial, lTextureObject);
			}
		}
	}

	const int lChildCount = pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		Initialize(pNode->GetChild(lChildIndex));
	}
}

void	ShadingManager::InitializeForOneFrame() const
{
	mLightCount = 0;
}

void	ShadingManager::SetMaterial(const KFbxNode* pNode, int pMaterialIndex) const
{
	const KFbxSurfaceMaterial*	lSurfaceMaterial = pNode->GetMaterial(pMaterialIndex);
	if (!lSurfaceMaterial)
		return;

    if (lSurfaceMaterial == mLastMaterial)
        return;

    mLastMaterial = lSurfaceMaterial;

    // Set emissive material
    SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sEmissive, KFbxSurfaceMaterial::sEmissiveFactor, GL_EMISSION);

    // Set ambient material
    SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sAmbient, KFbxSurfaceMaterial::sAmbientFactor, GL_AMBIENT);

    const TextureObjectsForMaterialType::RecordType* lRecord = mTextureObjectsForMaterial.Find(lSurfaceMaterial);
    if (lRecord)
    {
        glBindTexture(GL_TEXTURE_2D, lRecord->GetValue());
        mLastTextureObject = lRecord->GetValue();
    }
    else
    {
        mLastTextureObject = 0;
    }
    
    // No texture, set diffuse material property
    if (!mLastTextureObject)
    {
        SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sDiffuse, KFbxSurfaceMaterial::sDiffuseFactor, GL_DIFFUSE);
    }

    // Set specular material if exists
    SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sSpecular, KFbxSurfaceMaterial::sSpecularFactor, GL_SPECULAR);
    KFbxProperty lShininessProperty = lSurfaceMaterial->FindProperty(KFbxSurfaceMaterial::sShininess);
    if (lShininessProperty.IsValid())
    {
        double lShininess = 0;
        lShininess = lShininessProperty.Get(&lShininess);
        glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)lShininess);
    }
}

void ShadingManager::SetMaterialProperty(const KFbxSurfaceMaterial* pMaterial,
                                         const char* pPropertyName,
                                         const char* pFactorPropertyName,
                                         unsigned int pOGLProperty) const
{
    const KFbxProperty lProperty = pMaterial->FindProperty(pPropertyName);
    const KFbxProperty lFactorProperty = pMaterial->FindProperty(pFactorPropertyName);
    if (lProperty.IsValid() && lFactorProperty.IsValid())
    {
        fbxDouble3 lColor = fbxDouble3(0, 0, 0);
        lColor = lProperty.Get(&lColor);
        double lFactor = 1;
        lFactor = lFactorProperty.Get(&lFactor);
        if (lFactor != 1)
        {
            lColor[0]*= lFactor;
            lColor[1]*= lFactor;
            lColor[2]*= lFactor;
        }

        const GLfloat lMaterial[] = {(GLfloat)lColor[0], (GLfloat)lColor[1], (GLfloat)lColor[2], 1.0f};
        glMaterialfv(GL_FRONT, pOGLProperty, lMaterial);
    }
}

void ShadingManager::SetLight(KFbxLight::ELightType pType,
                              const KFbxColor& pColor, double pSpotCutoff) const
{
    if (mLightCount >= mOGLMaxLight)
        return;

    static const GLfloat lLightPos[] = {1.0f, 1.0f, 1.0f, 1.0f};
    static const GLfloat lLightDirection[] = {1.0f, 1.0f, 1.0f, 0.0f};
    const GLenum lLightEnum = GL_LIGHT0 + mLightCount++;
    glEnable(lLightEnum);
    if (pType == KFbxLight::eDIRECTIONAL)
    {
        glLightfv(lLightEnum, GL_POSITION, lLightDirection);
    }
    else
    {
        glLightfv(lLightEnum, GL_POSITION, lLightPos);
    }

    const GLfloat lLightColor[] = {(GLfloat)pColor[0], (GLfloat)pColor[1], (GLfloat)pColor[2], 1};
    glLightfv(lLightEnum, GL_DIFFUSE, lLightColor);
    glLightfv(lLightEnum, GL_SPECULAR, lLightColor);

    if (pType == KFbxLight::eSPOT && pSpotCutoff != 0.0)
        glLightf(lLightEnum, GL_SPOT_CUTOFF, pSpotCutoff);
}*/
