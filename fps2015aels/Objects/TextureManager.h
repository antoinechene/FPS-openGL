#ifndef TextureMangaer_h
#define TextureManager_h

#include <fbxsdk.h>

class TextureManager
{
	public:
		TextureManager(const KString & pWorkingDir) : mWorkingDir(pWorkingDir) {}
		~TextureManager();
		void	Clear();
		bool	LoadTexture(const KFbxFileTexture * pTexture, unsigned int * pTextureObject = NULL);
	private:
		typedef KMap<const KFbxFileTexture *, unsigned int> TextureMapType;

		bool	LoadTextureFromFile(const KString & pFilePath, unsigned int & pTextureObject);
	private:
		TextureMapType	mTextureMap;
		KString		mWorkingDir;
};


#endif
