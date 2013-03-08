#ifndef _TEXTURE_H_
#define _TEXTURE_H_

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
			
			Texture(File* const image);
			Texture(File* const buffer, const unsigned int width, const unsigned int height);
			Texture(const Texture& texture);
			Texture& operator=(const Texture& texture);
			~Texture();
			
			/// Load the texture with the desired filter mode , and with options to retain data and specify DXT format.
			bool load(const TextureFilter filter, const bool retainData = false, const TextureFormat format = FORMAT_RGB);
			
			/// Retrieve the file buffer.
			File* getFile();
			
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
			File* mFile;
			unsigned int mId;
			unsigned int mWidth;
			unsigned int mHeight;
			TextureFormat mFormat;
			TextureType mType;
	};
}

#endif

