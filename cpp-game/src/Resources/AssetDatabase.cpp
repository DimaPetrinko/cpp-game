#include <vector>
#include "AssetDatabase.h"

namespace Resources
{
	std::unordered_map<std::string, Asset*> AssetDatabase::mAssets;

	void AssetDatabase::PutBack(Asset** asset)
	{
		(*asset)->DecreaseReferenceCount();
		if ((*asset)->GetReferenceCount() == 0) UnloadAsset(asset);
		*asset = nullptr;
	}

	void AssetDatabase::UnloadUnusedAssets()
	{
		std::vector<std::string> keysToErase;
		for (auto pair : mAssets)
		{
			if (pair.second->GetReferenceCount() > 0) continue;
			UnloadAsset(&pair.second);
			keysToErase.push_back(pair.first);
		}

		for (auto key : keysToErase) mAssets.erase(key);
	}

	void AssetDatabase::UnloadAllAssets()
	{
		for (auto pair : mAssets)
		{
			UnloadAsset(&pair.second);
		}
		mAssets.clear();
	}

	void AssetDatabase::UnloadAsset(Asset** asset)
	{
		delete (*asset);
		*asset = nullptr;
	}
}
