#include "BaseResource.h"
#include "BaseResourceBank.h"

#include "../Platform/Application.h"
#include "ResourceManager.h"

#include <assert.h>

using namespace GLESGAE;

Resources::Group Resources::INVALID					= static_cast<Group>(-1);

Resources::Type Resources::Camera					= static_cast<Type>(-1000);
Resources::Type Resources::Controller				= static_cast<Type>(-1001);
Resources::Type Resources::IndexBuffer				= static_cast<Type>(-1002);
Resources::Type Resources::Material					= static_cast<Type>(-1003);
Resources::Type Resources::Matrix2					= static_cast<Type>(-1004);
Resources::Type Resources::Matrix3					= static_cast<Type>(-1005);
Resources::Type Resources::Matrix4					= static_cast<Type>(-1006);
Resources::Type Resources::Mesh						= static_cast<Type>(-1007);
Resources::Type Resources::Shader					= static_cast<Type>(-1008);
Resources::Type Resources::ShaderUniformUpdater		= static_cast<Type>(-1009);
Resources::Type Resources::Texture					= static_cast<Type>(-1010);
Resources::Type Resources::Timer					= static_cast<Type>(-1011);
Resources::Type Resources::Vector2					= static_cast<Type>(-1012);
Resources::Type Resources::Vector3					= static_cast<Type>(-1013);
Resources::Type Resources::Vector4					= static_cast<Type>(-1014);
Resources::Type Resources::VertexBuffer				= static_cast<Type>(-1015);

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

