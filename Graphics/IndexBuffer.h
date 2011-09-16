#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

namespace GLESGAE
{
	class IndexBuffer
	{
		public:
			enum FormatType {
				FORMAT_FLOAT			// unsupported by ES 1
			,	FORMAT_UNSIGNED_BYTE
			,	FORMAT_UNSIGNED_SHORT
			};

			IndexBuffer(unsigned char* const data, const unsigned int size, const FormatType format);
			IndexBuffer(const IndexBuffer& indexBuffer);

			/// Retrieve format details
			FormatType getFormat() const { return mFormat; }

			/// Retrieve data
			unsigned char* getData() const { return mData; }

			/// Retrieve size
			unsigned int getSize() const { return mSize; }
			
			/// Retrieve the Vbo Id
			unsigned int getVboId() const { return mVboId; }

		private:
			/// No equals operator, use copy constructor instead
			IndexBuffer& operator=(const IndexBuffer&);
			
			unsigned int mSize;
			unsigned char* mData;
			unsigned int mVboId;
			FormatType mFormat;
	};
}

#endif
