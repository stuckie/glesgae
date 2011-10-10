#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

namespace GLESGAE
{
	class VertexBuffer
	{
		public:
			const static unsigned int FORMAT_SIZE = 8U;
			
			enum BufferType
			{
				FORMAT_STATIC
			,	FORMAT_DYNAMIC
			,	FORMAT_STREAM
			};
			
			enum FormatType
			{
				INVALID_FORMAT
				// Float
			,	FORMAT_CUSTOM_4F
			,	FORMAT_CUSTOM_3F
			,	FORMAT_CUSTOM_2F
			,	FORMAT_POSITION_2F
			,	FORMAT_POSITION_3F
			,	FORMAT_POSITION_4F
			,	FORMAT_NORMAL_3F
			,	FORMAT_COLOUR_3F	// Not available in GLES1
			,	FORMAT_COLOUR_4F
			,	FORMAT_TEXTURE_2F
			,	FORMAT_TEXTURE_3F
			,	FORMAT_TEXTURE_4F
				// Unsigned/Byte
			,	FORMAT_CUSTOM_2B
			,	FORMAT_CUSTOM_3B
			,	FORMAT_CUSTOM_4B
			,	FORMAT_POSITION_2B
			,	FORMAT_POSITION_3B
			,	FORMAT_POSITION_4B
			,	FORMAT_NORMAL_3B
			,	FORMAT_COLOUR_3UB	// Not available in GLES1
			,	FORMAT_COLOUR_4UB
			,	FORMAT_TEXTURE_2B
			,	FORMAT_TEXTURE_3B
			,	FORMAT_TEXTURE_4B
				// Short
			,	FORMAT_CUSTOM_2S
			,	FORMAT_CUSTOM_3S
			,	FORMAT_CUSTOM_4S
			,	FORMAT_POSITION_2S
			,	FORMAT_POSITION_3S
			,	FORMAT_POSITION_4S
			,	FORMAT_NORMAL_3S
			,	FORMAT_COLOUR_3S	// Not available in GLES1
			,	FORMAT_COLOUR_4S	// Not available in GLES1
			,	FORMAT_TEXTURE_2S
			,	FORMAT_TEXTURE_3S
			,	FORMAT_TEXTURE_4S
			};

			class Format
			{
				public:
					Format() : mType(INVALID_FORMAT), mSize(0U), mOffset(0U) {}
					Format(const FormatType type, unsigned int offset)
					: mType(type)
					, mSize(0U)
					, mOffset(offset)
					{
						switch (mType)
						{
							case FORMAT_CUSTOM_2F:
							case FORMAT_POSITION_2F:
							case FORMAT_TEXTURE_2F:
								mSize = sizeof(float) * 2;
								break;
							case FORMAT_CUSTOM_3F:
							case FORMAT_POSITION_3F:
							case FORMAT_NORMAL_3F:
							case FORMAT_COLOUR_3F:
							case FORMAT_TEXTURE_3F:
								mSize = sizeof(float) * 3;
								break;
							case FORMAT_CUSTOM_4F:
							case FORMAT_POSITION_4F:
							case FORMAT_COLOUR_4F:
							case FORMAT_TEXTURE_4F:
								mSize = sizeof(float) * 4;
								break;
							case FORMAT_CUSTOM_2B:
							case FORMAT_POSITION_2B:
							case FORMAT_TEXTURE_2B:
								mSize = sizeof(char) * 2;
								break;
							case FORMAT_CUSTOM_3B:
							case FORMAT_POSITION_3B:
							case FORMAT_NORMAL_3B:
							case FORMAT_COLOUR_3UB:
							case FORMAT_TEXTURE_3B:
								mSize = sizeof(char) * 3;
								break;
							case FORMAT_CUSTOM_4B:
							case FORMAT_POSITION_4B:
							case FORMAT_COLOUR_4UB:
							case FORMAT_TEXTURE_4B:
								mSize = sizeof(char) * 4;
							case FORMAT_CUSTOM_2S:
							case FORMAT_POSITION_2S:
							case FORMAT_TEXTURE_2S:
								mSize = sizeof(short) * 2;
								break;
							case FORMAT_CUSTOM_3S:
							case FORMAT_POSITION_3S:
							case FORMAT_NORMAL_3S:
							case FORMAT_COLOUR_3S:
							case FORMAT_TEXTURE_3S:
								mSize = sizeof(short) * 3;
								break;
							case FORMAT_CUSTOM_4S:
							case FORMAT_POSITION_4S:
							case FORMAT_COLOUR_4S:
							case FORMAT_TEXTURE_4S:
								mSize = sizeof(short) * 4;
								break;
							default:
								break;
						};
					}

					/// Retrieve the type of this Format Identifier
					FormatType getType() const { return mType; }

					/// Retrieve the offset of this Format Identifier
					unsigned int getOffset() const { return mOffset; }

					/// Retrieve the size of this Format Identifier
					unsigned int getSize() const { return mSize; }

				private:
					FormatType mType;
					unsigned int mSize;
					unsigned int mOffset;
			};

			VertexBuffer(unsigned char* const data, const unsigned int size, const Format format[], const BufferType bufferType = FORMAT_STATIC);
			VertexBuffer(unsigned char* const data, const unsigned int size, const BufferType bufferType = FORMAT_STATIC);
			VertexBuffer(const VertexBuffer& vertexBuffer);
			~VertexBuffer();

			/// Retrieve format details
			const Format* getFormat() const { return mFormat; }

			/// Retrieve data
			unsigned char* getData() const { return mData; }

			/// Retrieve size
			unsigned int getSize() const { return mSize; }

			/// Retrieve stride
			unsigned int getStride() const { return mStride; }
			
			/// Retrieve the Buffer Type
			BufferType getType() const { return mType; }
			
			/// Retrieve the Vbo Id
			unsigned int getVboId() const { return mVboId; }
			
			/// Set the Vbo Id
			void setVboId(const unsigned int vboId) { mVboId = vboId; }

			/// Add a Format Identifier
			void addFormatIdentifier(const FormatType formatType, const unsigned int amount);

		private:
			// No Equals Operator
			VertexBuffer& operator=(const VertexBuffer&);
			
			unsigned int mSize;
			unsigned char* mData;
			unsigned int mStride;
			BufferType mType;
			unsigned int mVboId;			// using unsigned int rather than GLuint to keep GL dependency away from the header.
			Format mFormat[FORMAT_SIZE];
	};
}

#endif
