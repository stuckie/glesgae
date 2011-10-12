#include "BaseResource.h"
#include "BaseResourceBank.h"

#include "../Platform/Application.h"
#include "ResourceManager.h"

#include <assert.h>

using namespace GLESGAE;

Resources::Type Resources::Camera					= HashString("Camera");
Resources::Type Resources::Controller				= HashString("Controller");
Resources::Type Resources::IndexBuffer				= HashString("IndexBuffer");
Resources::Type Resources::Material					= HashString("Material");
Resources::Type Resources::Matrix2					= HashString("Matrix2");
Resources::Type Resources::Matrix3					= HashString("Matrix3");
Resources::Type Resources::Matrix4					= HashString("Matrix4");
Resources::Type Resources::Mesh						= HashString("Mesh");
Resources::Type Resources::Shader					= HashString("Shader");
Resources::Type Resources::ShaderUniformUpdater		= HashString("ShaderUniformUpdater");
Resources::Type Resources::Texture					= HashString("Texture");
Resources::Type Resources::Timer					= HashString("Timer");
Resources::Type Resources::Vector2					= HashString("Vector2");
Resources::Type Resources::Vector3					= HashString("Vector3");
Resources::Type Resources::Vector4					= HashString("Vector4");
Resources::Type Resources::VertexBuffer				= HashString("VertexBuffer");

/// Private constructor as this is a derived class only
BaseResource::BaseResource(const Resources::Group group, const Resources::Type type, const Resources::Id id)
: mGroup(group)
, mType(type)
, mId(id)
, mCount(new Resources::Count)
{
	*mCount = 0;
}

/// Overloaded Copy Constructor, so we keep track of how many instances we have.
BaseResource::BaseResource(const BaseResource& resource)
: mGroup(resource.mGroup)
, mType(resource.mType)
, mId(resource.mId)
, mCount(resource.mCount)
{

}

BaseResource::~BaseResource()
{
}

