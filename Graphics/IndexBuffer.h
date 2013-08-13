#ifndef _INDEX_BUFFER_H_
#define _INDEX_BUFFER_H_

namespace GLESGAE
{
	class IndexBuffer
	{
		public:
			
			struct UpdateData
			{
				bool retain;
				unsigned int offset;
				unsigned int size;
				unsigned char* data;
				
				UpdateData() : retain(false), offset(0), size(0), data(0) {}
			};
			
			enum DrawType {
				DRAW_STATIC
			,	DRAW_STREAM
			,	DRAW_DYNAMIC
			};
			
			enum IndexType {
				INDEX_FLOAT					// unsupported by ES 1
			,	INDEX_UNSIGNED_BYTE
			,	INDEX_UNSIGNED_SHORT
			,	INDEX_UNSIGNED_INT			// unsupported by unextended ES variants.
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

			IndexBuffer(unsigned char* const data, const unsigned int count, const IndexType type, const FormatType format, const DrawType drawType = DRAW_STATIC);
			IndexBuffer(const IndexBuffer& indexBuffer);
			IndexBuffer& operator=(const IndexBuffer& indexBuffer);
			~IndexBuffer();

			/// Retrieve format details
			FormatType getFormat() const { return mFormat; }
			
			/// Retrieve Index details
			IndexType getType() const { return mType; }
			
			/// Retrieve the draw type
			DrawType getDrawType() const { return mDrawType; }

			/// Retrieve data
			unsigned char* getData() const { return mData; }

			/// Retrieve element count
			unsigned int getCount() const { return mCount; }
			
			/// Retrieve data size
			unsigned int getSize() const { return mSize; }
			
			/// Retrieve the Vbo Id
			unsigned int* getVboId() const { return mVboId; }
			
			/// Set the Vbo Id
			void setVboId(unsigned int* vboId) { mVboId = vboId; }
			
			/// Set Update Data
			void setUpdateData(UpdateData* const updateData) { mUpdateData = updateData; }
			
			/// Get Update Data
			UpdateData* getUpdateData() { return mUpdateData; }

		private:
			unsigned int mCount;
			unsigned int mSize;
			unsigned char* mData;
			unsigned int* mVboId;
			FormatType mFormat;
			IndexType mType;
			DrawType mDrawType;
			UpdateData* mUpdateData;
	};
}

#endif
