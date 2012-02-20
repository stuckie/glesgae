#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../Resources/Resource.h"
#include "../File/File.h"

namespace GLESGAE
{
	class Texture
	{
		public:
			enum TextureFormat {
				FORMAT_INVALID
			,	FORMAT_DXT1
			,	FORMAT_DXT5
			,	FORMAT_RGBA
			,	FORMAT_RGB
			};
			
			enum TextureType {
				TYPE_FILE
			,	TYPE_BUFFER
			};
			
			enum TextureFilter {
				FILTER_NONE
			,	FILTER_BILINEAR
			,	FILTER_TRILINEAR
			};
			
			Texture(const Resource<File>& image);
			Texture(const Resource<File>& buffer, const unsigned int width, const unsigned int height);
			~Texture();
			
			/// Get the File this Texture represents.
			const Resource<File>& getFile() const { return mFile; }
			
			/// Load the texture with the desired filter mode , and with options to retain data and specify DXT format.
			bool load(const TextureFilter filter, const bool retainData = false, const TextureFormat format = FORMAT_RGB);
			
			/// Delete this Texture.
			void kill();
			
			/// Save the texture.
			bool save();
			
			/// Retrieve this Texture's GL id.
			unsigned int getId() const { return mId; }
			
			/// Get Width.
			unsigned int getWidth() const { return mWidth; }
			
			/// Get Height.
			unsigned int getHeight() const { return mHeight; }
			
		private:
			Resource<File> mFile;
			unsigned int mId;
			unsigned int mWidth;
			unsigned int mHeight;
			TextureFormat mFormat;
			TextureType mType;
	};
}

#endif
