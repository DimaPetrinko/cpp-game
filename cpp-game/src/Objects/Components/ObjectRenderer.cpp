#include "ObjectRenderer.h"

#include "Resources/AssetDatabase.h"

namespace Objects::Components
{
	ObjectRenderer::ObjectRenderer(Graphics::Mesh* mesh, Graphics::Texture* texture, Graphics::Shader* shader)
		: mMesh(mesh), mTexture(texture), mShader(shader) {}

	ObjectRenderer::~ObjectRenderer()
	{
		mOwner = nullptr;

		auto assetDatabase = Resources::AssetDatabase::Instance();
		if (mMesh != nullptr) assetDatabase->PutBack(ToAssetReference(mMesh));
		if (mTexture != nullptr) assetDatabase->PutBack(ToAssetReference(mTexture));
		if (mShader != nullptr) assetDatabase->PutBack(ToAssetReference(mShader));
	}

	void ObjectRenderer::SetOwner(Object* owner)
	{
		mOwner = owner;
	}
}