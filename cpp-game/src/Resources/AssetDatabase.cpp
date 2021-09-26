#include "AssetDatabase.h"

#include <filesystem>
#include <fstream>
#include <random>

namespace Resources
{
	AssetDatabase* AssetDatabase::sInstance{};

	AssetDatabase::AssetDatabase()
	{
		sInstance = this;

		std::vector<std::string> files;
		std::string path = "res/";
		CheckFolder(path, &files);

		for (const std::string& file : files)
		{
			if (std::filesystem::path(file).extension() == ".meta") continue; // skipping metas from the list

			std::string metaFilePath = file + ".meta";
			uuid_t uuid;
			if (std::filesystem::exists(metaFilePath))
			{
				uuid = ReadUUIDFromFile(metaFilePath);
			}
			else
			{
				uuid = GenerateUUID();
				WriteUUIDToFile(uuid, metaFilePath);
			}
			mPaths[uuid] = file;
		}

		// write a variant of this method to pack assets into a binary file
	}

	AssetDatabase::~AssetDatabase()
	{
		UnloadAllAssets();
	}

	void AssetDatabase::PutBack(Asset* asset)
	{
		asset->DecreaseReferenceCount();
	}

	void AssetDatabase::UnloadUnusedAssets()
	{
		std::vector<uuid_t> keysToErase;
		for (auto pair : mAssets)
		{
			if (pair.second->GetReferenceCount() > 0) continue;
			UnloadAssetInternal(pair.second);
			keysToErase.push_back(pair.first);
		}

		for (auto key : keysToErase) mAssets.erase(key);
	}

	void AssetDatabase::UnloadAllAssets()
	{
		for (auto pair : mAssets)
		{
			UnloadAssetInternal(pair.second);
		}
		mAssets.clear();
	}

	void AssetDatabase::UnloadAsset(Asset* asset)
	{
		for (auto pair : mAssets)
		{
			if (pair.second != asset) continue;
			mAssets.erase(pair.first);
			break;
		}
		UnloadAssetInternal(asset);
	}

	void AssetDatabase::UnloadAssetInternal(Asset* asset)
	{
		delete asset;
	}

	void AssetDatabase::CheckFolder(const std::string& path, std::vector<std::string>* files)
	{
		for (const auto & entry : std::filesystem::directory_iterator(path))
		{
			std::string newPath = entry.path();
			if (std::filesystem::is_directory(newPath)) CheckFolder(newPath, files);
			else files->push_back(newPath);
		}
	}

	uuid_t AssetDatabase::ReadUUIDFromFile(const std::string& metaFilePath)
	{
		std::ifstream s(metaFilePath);
		std::string line;
		std::getline(s, line);
		uuid_t uuid = std::stoull(line);
		s.close();
		return uuid;
	}

	uuid_t AssetDatabase::GenerateUUID()
	{
		std::random_device device;
		std::mt19937_64 generator(device());
		std::uniform_int_distribution<uuid_t> distribution;
		return distribution(generator);
	}

	void AssetDatabase::WriteUUIDToFile(uuid_t uuid, const std::string& metaFilePath)
	{
		std::ofstream s(metaFilePath);
		s << uuid;
		s.close();
	}
}
