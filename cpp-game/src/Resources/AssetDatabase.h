#pragma once

#include <unordered_map>
#include "Asset.h"

#define ToAssetReference(x) (Resources::Asset**)(void**)&x

namespace Resources
{
	class AssetDatabase
	{
	private:
		static std::unordered_map<std::string, Asset*> mAssets;
	public:
		template<typename T> static T* GetAsset(const std::string& filePath);

		static void PutBack(Asset** asset);
		static void UnloadUnusedAssets();
		static void UnloadAllAssets();
		static void UnloadAsset(Asset** asset);
		// unload speciffic asset
	};

	template<typename T> T* AssetDatabase::GetAsset(const std::string& filePath)
	{
		std::string path = "res/" + filePath;
		auto iterator = mAssets.find(path);
		Asset* asset;
		if (iterator != AssetDatabase::mAssets.end())
		{
			asset = iterator->second;
		}
		else
		{
			asset = new T(path);
			mAssets.insert(std::pair<std::string, Asset*>(path, asset));
		}
		asset->IncreaseReferenceCount();
		return (T*)asset;
	}
}
