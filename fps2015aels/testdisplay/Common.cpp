#include <fbxsdk.h>
#include <fbxfilesdk/kfbxio/kfbxiosettings.h>
#include "Common.h"

#ifdef IOS_REF
    #undef  IOS_REF
    #define IOS_REF (*(pSdkManager->GetIOSettings()))
#endif

void InitializeSdkObjects(KFbxSdkManager*& pSdkManager, KFbxScene*& pScene)
{
	pSdkManager = KFbxSdkManager::Create();

	if (!pSdkManager)
	{
		printf("Unable to create the FBX SDK manager\n");
		exit(0);
	}

	KFbxIOSettings * ios = KFbxIOSettings::Create(pSdkManager, IOSROOT );
	pSdkManager->SetIOSettings(ios);

	KString lPath = KFbxGetApplicationDirectory();
#if defined(KARCH_ENV_WIN)
	KString lExtension = "dll";
#elif defined(KARCH_ENV_MACOSX)
	KString lExtension = "dylib";
#elif defined(KARCH_ENV_LINUX)
	KString lExtension = "so";
#endif
	pSdkManager->LoadPluginsDirectory(lPath.Buffer(), lExtension.Buffer());

	pScene = KFbxScene::Create(pSdkManager,"");
}

void DestroySdkObjects(KFbxSdkManager* pSdkManager)
{
	if (pSdkManager) 
		pSdkManager->Destroy();
	pSdkManager = NULL;
}

bool SaveScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename, int pFileFormat, bool pEmbedMedia)
{
	int lMajor, lMinor, lRevision;
	bool lStatus = true;

	KFbxExporter* lExporter = KFbxExporter::Create(pSdkManager, "");

	if( pFileFormat < 0 || pFileFormat >= pSdkManager->GetIOPluginRegistry()->GetWriterFormatCount() )
	{
		pFileFormat = pSdkManager->GetIOPluginRegistry()->GetNativeWriterFormat();

		if (!pEmbedMedia)
		{
			int lFormatIndex, lFormatCount = pSdkManager->GetIOPluginRegistry()->GetWriterFormatCount();

			for (lFormatIndex=0; lFormatIndex<lFormatCount; lFormatIndex++)
			{
				if (pSdkManager->GetIOPluginRegistry()->WriterIsFBX(lFormatIndex))
				{
					KString lDesc =pSdkManager->GetIOPluginRegistry()->GetWriterFormatDescription(lFormatIndex);
					char *lASCII = "ascii";
					if (lDesc.Find(lASCII)>=0)
					{
						pFileFormat = lFormatIndex;
						break;
					}
				}
			}
		}
	}
	IOS_REF.SetBoolProp(EXP_FBX_MATERIAL,        true);
	IOS_REF.SetBoolProp(EXP_FBX_TEXTURE,         true);
	IOS_REF.SetBoolProp(EXP_FBX_EMBEDDED,        pEmbedMedia);
	IOS_REF.SetBoolProp(EXP_FBX_SHAPE,           true);
	IOS_REF.SetBoolProp(EXP_FBX_GOBO,            true);
	IOS_REF.SetBoolProp(EXP_FBX_ANIMATION,       true);
	IOS_REF.SetBoolProp(EXP_FBX_GLOBAL_SETTINGS, true);

	if(lExporter->Initialize(pFilename, pFileFormat, pSdkManager->GetIOSettings()) == false)
	{
		printf("Call to KFbxExporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lExporter->GetLastErrorString());
		return false;
	}

	KFbxSdkManager::GetFileFormatVersion(lMajor, lMinor, lRevision);
	printf("FBX version number for this version of the FBX SDK is %d.%d.%d\n\n", lMajor, lMinor, lRevision);

	lStatus = lExporter->Export(pScene); 

	lExporter->Destroy();
	return lStatus;
}

bool LoadScene(KFbxSdkManager* pSdkManager, KFbxDocument* pScene, const char* pFilename)
{
	int lFileMajor, lFileMinor, lFileRevision;
	int lSDKMajor,  lSDKMinor,  lSDKRevision;
	//int lFileFormat = -1;
	int i, lAnimStackCount;
	bool lStatus;
	char lPassword[1024];

	KFbxSdkManager::GetFileFormatVersion(lSDKMajor, lSDKMinor, lSDKRevision);

	KFbxImporter* lImporter = KFbxImporter::Create(pSdkManager,"");

	const bool lImportStatus = lImporter->Initialize(pFilename, -1, pSdkManager->GetIOSettings());
	lImporter->GetFileVersion(lFileMajor, lFileMinor, lFileRevision);

	if( !lImportStatus )
	{
		printf("Call to KFbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", lImporter->GetLastErrorString());

		if (lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_YET ||
				lImporter->GetLastErrorID() == KFbxIO::eFILE_VERSION_NOT_SUPPORTED_ANYMORE)
		{
			printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);
			printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);
		}

		return false;
	}

	printf("FBX version number for this FBX SDK is %d.%d.%d\n", lSDKMajor, lSDKMinor, lSDKRevision);

	if (lImporter->IsFBX())
	{
		printf("FBX version number for file %s is %d.%d.%d\n\n", pFilename, lFileMajor, lFileMinor, lFileRevision);


		printf("Animation Stack Information\n");

		lAnimStackCount = lImporter->GetAnimStackCount();

		printf("    Number of Animation Stacks: %d\n", lAnimStackCount);
		printf("    Current Animation Stack: \"%s\"\n", lImporter->GetActiveAnimStackName().Buffer());
		printf("\n");

		for(i = 0; i < lAnimStackCount; i++)
		{
			KFbxTakeInfo* lTakeInfo = lImporter->GetTakeInfo(i);

			printf("    Animation Stack %d\n", i);
			printf("         Name: \"%s\"\n", lTakeInfo->mName.Buffer());
			printf("         Description: \"%s\"\n", lTakeInfo->mDescription.Buffer());

			printf("         Import Name: \"%s\"\n", lTakeInfo->mImportName.Buffer());

			printf("         Import State: %s\n", lTakeInfo->mSelect ? "true" : "false");
			printf("\n");
		}

		IOS_REF.SetBoolProp(IMP_FBX_MATERIAL,        true);
		IOS_REF.SetBoolProp(IMP_FBX_TEXTURE,         true);
		IOS_REF.SetBoolProp(IMP_FBX_LINK,            true);
		IOS_REF.SetBoolProp(IMP_FBX_SHAPE,           true);
		IOS_REF.SetBoolProp(IMP_FBX_GOBO,            true);
		IOS_REF.SetBoolProp(IMP_FBX_ANIMATION,       true);
		IOS_REF.SetBoolProp(IMP_FBX_GLOBAL_SETTINGS, true);
	}

	lStatus = lImporter->Import(pScene);

	if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
	{
		printf("Please enter password: ");

		lPassword[0] = '\0';

		scanf("%s", lPassword);
		KString lString(lPassword);

		IOS_REF.SetStringProp(IMP_FBX_PASSWORD,      lString);
		IOS_REF.SetBoolProp(IMP_FBX_PASSWORD_ENABLE, true);

		lStatus = lImporter->Import(pScene);

		if(lStatus == false && lImporter->GetLastErrorID() == KFbxIO::ePASSWORD_ERROR)
		{
			printf("\nPassword is wrong, import aborted.\n");
		}
	}

	lImporter->Destroy();
	return lStatus;
}

