#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

namespace GLESGAE
{
	class Texture
	{
		public:
			enum TextureFormat {
				INVALID_FORMAT
			,	RGBA
			,	RGB
			};
			
			Texture() : mId(), mData(0), mWidth(), mHeight(), mType(INVALID_FORMAT) {}
			
			/// Load as BMP
			void loadBMP(const std::string& fileName);

			/// Retrieve this Texture's GL id
			unsigned int getId() const { return mId; }
			
			/// Get Width
			unsigned int getWidth() const { return mWidth; }
			
			/// Get Height
			unsigned int getHeight() const { return mHeight; }
			
		protected:
			/// Create GL Id
			void createGLid();

		private:
			// No copying
			Texture(const Texture&);
			Texture& operator=(const Texture&);
			
			unsigned int mId;
			unsigned char* mData;
			unsigned int mWidth;
			unsigned int mHeight;
			TextureFormat mType;
	};
}

#endif
