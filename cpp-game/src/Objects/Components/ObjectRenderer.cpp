#include "ObjectRenderer.h"

#include "Resources/AssetDatabase.h"

namespace Objects::Components
{
	ObjectRenderer::ObjectRenderer(Graphics::Mesh* mesh, Graphics::Texture* texture, Graphics::Shader* shader)
		: mMesh(mesh), mTexture(texture), mShader(shader) {}

	ObjectRenderer::~ObjectRenderer()
	{
		mOwner = nullptr;

		if (mMesh != nullptr) Resources::AssetDatabase::PutBack(ToAssetReference(mMesh));
		if (mTexture != nullptr) Resources::AssetDatabase::PutBack(ToAssetReference(mTexture));
		if (mShader != nullptr) Resources::AssetDatabase::PutBack(ToAssetReference(mShader));
	}

	void ObjectRenderer::SetOwner(Object* owner)
	{
		mOwner = owner;
	}
}