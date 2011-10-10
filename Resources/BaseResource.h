#ifndef _BASE_RESOURCE_H_
#define _BASE_RESOURCE_H_

namespace GLESGAE
{

	namespace Resources
	{
		typedef unsigned int Type;
		typedef unsigned int Id;
		typedef unsigned int Count;
		typedef unsigned int Group;
		
		extern Group INVALID;
		
		struct Locator
		{
			Id bank;
			Type type;
			Group group;
			Id resource;
			
			Locator() : bank(INVALID), type(INVALID), group(INVALID), resource(INVALID) {}
		};
		
		// System Resources
		extern Type Camera;
		extern Type Controller;
		extern Type IndexBuffer;
		extern Type Material;
		extern Type Matrix2;
		extern Type Matrix3;
		extern Type Matrix4;
		extern Type Mesh;
		extern Type Shader;
		extern Type ShaderUniformUpdater;
		extern Type Texture;
		extern Type Timer;
		extern Type Vector2;
		extern Type Vector3;
		extern Type Vector4;
		extern Type VertexBuffer;
	}
	
	class BaseResourceBank;
	class BaseResource
	{
		public:			
			virtual ~BaseResource();
			
			/// Get the Type of this Resource
			Resources::Type getType() const { return mType; }
			
			/// Get which Group this Resource belongs to
			Resources::Group getGroup() const { return mGroup; }
			
			/// Get the Id of this Resource
			Resources::Id getId() const { return mId; }
			
			/// Get the Instance Count of this Resource
			Resources::Count getCount() const { return *mCount; }
						
		protected:		
			/// Set the count
			void setCount(const Resources::Count& count) { *mCount = count; }
		
			/// Private constructor as this is a derived class only
			BaseResource(const Resources::Group group, const Resources::Type type, const Resources::Id id);
			
			/// Overloaded Copy Constructor, so we keep track of how many instances we have.
			BaseResource(const BaseResource& resource);
		
			/// Overloaded Assignment Operator, so we can keep track of everything.
			BaseResource& operator=(const BaseResource& resource)
			{
				mGroup = resource.mGroup;
				mType = resource.mType;
				mId = resource.mId;
				mCount = resource.mCount;
			
				return *this;
			}
	
			Resources::Group mGroup;
			Resources::Type mType;
			Resources::Id mId;
			mutable Resources::Count* mCount;
	};

}

#endif
