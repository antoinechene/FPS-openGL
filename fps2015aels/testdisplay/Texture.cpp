#include "Texture.h"

#define GLUT_DISABLE_ATEXIT_HACK
#if defined(__MACH__)
#include <GLUT/glut.h>
#else
#include <GLTools.h>

#include "GL/glut.h"
#include <GL/glew.h>
#include <GL/gl.h>

#endif

#ifndef GL_BGR
    #ifdef GL_BGR_EXT
        #define GL_BGR GL_BGR_EXT
    #else
        #error "GL_BGR is not defined, nor can define GL_BGR from GL_BGR_EXT"
    #endif
#endif

#include "targa.h"

TextureManager::~TextureManager()
{
	TextureMapType::ConstIterator iter = mTextureMap.Begin();
	for (; iter != mTextureMap.End(); ++iter)
	{
		const unsigned int lTextureObject = iter->GetValue();
		if (glIsTexture(lTextureObject))
			glDeleteTextures(1, &lTextureObject);
	}
}

void TextureManager::Clear()
{
	mTextureMap.Clear();
}

bool TextureManager::LoadTexture(const KFbxFileTexture * pTexture, unsigned int * pTextureObject)
{
	TextureMapType::RecordType * lTextureRecord = mTextureMap.Find(pTexture);
	if (lTextureRecord)
	{
		if (pTextureObject)
			*pTextureObject = lTextureRecord->GetValue();
		return true;
	}

	const KString lFileName = pTexture->GetFileName();
	unsigned int lTextureObject = 0;
	bool lStatus = LoadTextureFromFile(lFileName, lTextureObject);

	if (!lStatus)
	{
		const KString lRelativeFileName = mWorkingDir + "/" + pTexture->GetFileName();
		lStatus = LoadTextureFromFile(lRelativeFileName, lTextureObject);
	}

	if (lStatus)
	{
		K_ASSERT(glIsTexture(lTextureObject));
		mTextureMap.Insert(pTexture, lTextureObject);
		if (pTextureObject)
			*pTextureObject = lTextureObject;
		return true;
	}

	return false;
}

bool TextureManager::LoadTextureFromFile(const KString & pFilePath, unsigned int & pTextureObject)
{
	int		compo;
	GLenum		Format;
	int		w;
	int		h;
	GLbyte*		Bits;

	if (pFilePath.Right(3).Upper() == "TGA")
	{

		Bits  = gltReadTGABits(pFilePath, &w, &h, &compo, &Format);

		if (Bits != NULL)
		{
			glGenTextures(1, &pTextureObject);
			glBindTexture(GL_TEXTURE_2D, pTextureObject);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			glTexImage2D(GL_TEXTURE_2D, 0, compo, w, h, 0, Format,
					GL_UNSIGNED_BYTE, Bits);

			return true;
		}
	}

	return false;
}

	ShadingManager::ShadingManager(const KString & pWorkingDir)
: mTextureManager(new TextureManager(pWorkingDir)), mShadingMode(SHADING_MODE_SHADED),
	mDrawNormal(false), mNormalScale(1),
	mLastMaterial(NULL), mLastTextureObject(0),
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

void ShadingManager::Initialize(const KFbxNode* pNode)
{
	if (!pNode)
		return;

	if (pNode->GetNodeAttribute())
	{
		const int lMaterialCount = pNode->GetMaterialCount();
		for (int lMaterialIndex = 0; lMaterialIndex < lMaterialCount; ++lMaterialIndex)
		{
			const KFbxSurfaceMaterial * lMaterial = pNode->GetMaterial(lMaterialIndex);
			if (lMaterial)
			{
				const KFbxProperty lProperty = lMaterial->FindProperty(KFbxSurfaceMaterial::sDiffuse);
				if (lProperty.IsValid())
				{
					const int lTextureCount = lProperty.GetSrcObjectCount(KFbxFileTexture::ClassId);
					if (lTextureCount)
					{
						const KFbxFileTexture* lTexture = lProperty.GetSrcObject(FBX_TYPE(KFbxFileTexture), 0);
						if (lTexture)
						{
							unsigned int lTextureObject;
							mTextureManager->LoadTexture(lTexture, &lTextureObject);
							mTextureObjectsForMaterial.Insert(lMaterial, lTextureObject);
						}
					}
				}
			}
		}
	}

	const int lChildCount = pNode->GetChildCount();
	for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
	{
		Initialize(pNode->GetChild(lChildIndex));
	}
}

void ShadingManager::InitializeForOneFrame() const
{
	mLightCount = 0;
}

void ShadingManager::SetMaterial(const KFbxNode * pNode, int pMaterialIndex) const
{
	const KFbxSurfaceMaterial * lSurfaceMaterial = pNode->GetMaterial(pMaterialIndex);
	if (!lSurfaceMaterial)
		return;

	if (lSurfaceMaterial == mLastMaterial)
		return;

	mLastMaterial = lSurfaceMaterial;

	SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sEmissive, KFbxSurfaceMaterial::sEmissiveFactor, GL_EMISSION);

	SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sAmbient, KFbxSurfaceMaterial::sAmbientFactor, GL_AMBIENT);

	const TextureObjectsForMaterialType::RecordType * lRecord = mTextureObjectsForMaterial.Find(lSurfaceMaterial);
	if (lRecord)
	{
		glBindTexture(GL_TEXTURE_2D, lRecord->GetValue());
		mLastTextureObject = lRecord->GetValue();
	}
	else
	{
		mLastTextureObject = 0;
	}

	if (!mLastTextureObject)
	{
		SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sDiffuse, KFbxSurfaceMaterial::sDiffuseFactor, GL_DIFFUSE);
	}

	SetMaterialProperty(lSurfaceMaterial, KFbxSurfaceMaterial::sSpecular, KFbxSurfaceMaterial::sSpecularFactor, GL_SPECULAR);
	KFbxProperty lShininessProperty = lSurfaceMaterial->FindProperty(KFbxSurfaceMaterial::sShininess);
	if (lShininessProperty.IsValid())
	{
		double lShininess = 0;
		lShininess = lShininessProperty.Get(&lShininess);
		glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)lShininess);
	}
}

void ShadingManager::SetMaterialProperty(const KFbxSurfaceMaterial * pMaterial,
		const char * pPropertyName,
		const char * pFactorPropertyName,
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
			lColor[0] *= lFactor;
			lColor[1] *= lFactor;
			lColor[2] *= lFactor;
		}

		const GLfloat lMaterial[] = {(GLfloat)lColor[0], (GLfloat)lColor[1], (GLfloat)lColor[2], 1.0f};
		glMaterialfv(GL_FRONT, pOGLProperty, lMaterial);
	}
}

void ShadingManager::SetLight(KFbxLight::ELightType pType,
		const KFbxColor & pColor, double pSpotCutoff /* = 0 */) const
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
}
