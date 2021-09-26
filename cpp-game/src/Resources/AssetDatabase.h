#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include "Asset.h"

#define ToAssetReference(x) dynamic_cast<Resources::Asset*>(x)

typedef uint64_t uuid_t;

#define QUAD_UUID 7815304873435757618
#define BASIC_SHADER_UUID 4868602585906568521
#define CHECKER3_UUID 16249532275758602479
#define IMAGE_UUID 12887210580381219683

namespace Resources
{
	class AssetDatabase
	{
	private:
		static AssetDatabase* sInstance;
		std::unordered_map<uuid_t, Asset*> mAssets;
		std::unordered_map<uuid_t, std::string> mPaths;
	public:
		AssetDatabase();
		~AssetDatabase();

		inline static AssetDatabase* Instance() { return sInstance; }
		template<typename T>  T* GetAsset(const uuid_t& filePath);
		void PutBack(Asset* asset);
		void UnloadUnusedAssets();
		void UnloadAllAssets();
		void UnloadAsset(Asset* asset);
	private:
		void UnloadAssetInternal(Asset* asset);
		void CheckFolder(const std::string& path, std::vector<std::string>* files);
		uuid_t ReadUUIDFromFile(const std::string& metaFilePath);
		uuid_t GenerateUUID();
		void WriteUUIDToFile(uuid_t uuid, const std::string& metaFilePath);
	};

	template<typename T> T* AssetDatabase::GetAsset(const uuid_t& uuid)
	{
		auto pathsIterator = mPaths.find(uuid);
		std::string path;
		if (pathsIterator != AssetDatabase::mPaths.end())
		{
			path = pathsIterator->second;
		}
		else
		{
			printf("No asset with uuid %i", uuid);
			return nullptr;
		}

		auto assetsIterator = mAssets.find(uuid);
		Asset* asset;
		if (assetsIterator != AssetDatabase::mAssets.end())
		{
			asset = assetsIterator->second;
		}
		else
		{
			asset = new T(path);
			mAssets.insert(std::pair<uuid_t, Asset*>(uuid, asset));
		}
		asset->IncreaseReferenceCount();
		return dynamic_cast<T*>(asset);
	}
}
