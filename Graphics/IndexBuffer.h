#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

namespace GLESGAE
{
	class IndexBuffer
	{
		public:
			enum IndexType {
				INDEX_FLOAT				// unsupported by ES 1
			,	INDEX_UNSIGNED_BYTE
			,	INDEX_UNSIGNED_SHORT
			,	INDEX_UNSIGNED_INT		// unsupported by unextended ES variants.
			};
			
			enum FormatType {
				FORMAT_POINTS
			,	FORMAT_LINES
			,	FORMAT_LINE_STRIP
			,	FORMAT_LINE_LOOP
			,	FORMAT_TRIANGLES
			,	FORMAT_TRAINGLE_STRIP
			,	FORMAT_TRIANGLE_FAN
			};

			IndexBuffer(unsigned char* const data, const unsigned int size, const IndexType type, const FormatType format);
			IndexBuffer(const IndexBuffer& indexBuffer);

			/// Retrieve format details
			FormatType getFormat() const { return mFormat; }
			
			/// Retrieve Index details
			IndexType getType() const { return mType; }

			/// Retrieve data
			unsigned char* getData() const { return mData; }

			/// Retrieve size
			unsigned int getSize() const { return mSize; }
			
			/// Retrieve the Vbo Id
			unsigned int getVboId() const { return mVboId; }
			
			/// Set the Vbo Id
			void setVboId(const unsigned int vboId) { mVboId = vboId; }

		private:
			/// No equals operator, use copy constructor instead
			IndexBuffer& operator=(const IndexBuffer&);
			
			unsigned int mSize;
			unsigned char* mData;
			unsigned int mVboId;
			FormatType mFormat;
			IndexType mType;
	};
}

#endif
