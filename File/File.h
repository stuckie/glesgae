#ifndef _BASE_FILE_H_
#define _BASE_FILE_H_

#include <string>

namespace GLESGAE
{

namespace FILEIO
{
	enum OPEN_MODE
	{	OPEN_READ
	,	OPEN_WRITE
	,	OPEN_APPEND
	};
	
	enum FILE_MODE
	{	FILE_ASCII
	,	FILE_BINARY
	};
	
	enum FILE_STATUS
	{	FILE_ERROR
	,	FILE_OPEN
	,	FILE_CLOSED
	,	FILE_EOF
	,	FILE_NOT_FOUND
	};
	
	enum READ_STATUS
	{	READ_OK
	,	READ_ERROR
	,	READ_EOF
	};
	
	enum WRITE_STATUS
	{	WRITE_OK
	,	WRITE_ERROR
	};
	
	enum CLOSE_MODE
	{	CLOSE_RETAIN_DATA
	,	CLOSE_DELETE_DATA
	};
}

class BaseFile
{
	public:
		BaseFile(const std::string& filepath)
		: mFilePath(filepath)
		, mBuffer(0)
		, mReadPosition(0U)
		, mBufferSize(0U)
		, mFileSize(0U)
		, mFileStatus(FILEIO::FILE_CLOSED)
		, mOpenMode(FILEIO::OPEN_READ)
		, mBufferOwned(false)
		{
		}
		
		virtual ~BaseFile()
		{
			if ((0 != mBuffer) && (true == mBufferOwned)) {
				delete [] mBuffer;
				mBuffer = 0;
			}
		}
		
		/// Get filepath this File is tracking.
		const std::string& getFilePath() const { return mFilePath; }
		
		/// Open the file in the specified mode.
		virtual FILEIO::FILE_STATUS open(const FILEIO::OPEN_MODE openMode, const FILEIO::FILE_MODE fileMode) = 0;
		
		/// Close the file - with an option to delete the data.
		virtual FILEIO::FILE_STATUS close(const FILEIO::CLOSE_MODE mode = FILEIO::CLOSE_RETAIN_DATA) = 0;
		
		/// Current File Status.
		FILEIO::FILE_STATUS status() const { return mFileStatus; }
		
		/// Delete buffer data.
		/// Return true on success, false on failure.
		virtual bool deleteBuffer() = 0;
		
		/// Read File - automatically reads all, or up to the specified amount till it reaches the end of the file.
		virtual FILEIO::READ_STATUS read(const unsigned long amount = static_cast<unsigned long>(-1U)) = 0;
		
		/// Write File - write out what's in the buffer.
		virtual FILEIO::WRITE_STATUS write() = 0;
		
		/// Set Read position of file.
		virtual FILEIO::READ_STATUS setReadPosition(const unsigned long readPosition) = 0;
		
		/// Get current Read Position of file.
		unsigned long getReadPosition() const { return mReadPosition; }
		
		/// Get read-only file buffer.
		const unsigned char* readBuffer() const { return mBuffer; }
		
		/// Get read-only buffer as Cstring.
		const char* stringBuffer() const { return reinterpret_cast<char*>(mBuffer); }
		
		/// Get writable file buffer.
		unsigned char* writeBuffer() { return mBuffer; }
		
		/// Get the buffer size.
		unsigned long getBufferSize() const { return mBufferSize; }
		
		/// Set the file buffer, with an option to make a copy of it.
		/// Returns true if successful, false if there's an error.
		virtual bool setBuffer(unsigned char* buffer, const unsigned long size, const bool copy = false) = 0;
		
		/// Create a new file buffer.
		/// Returns true if successful, false if there's an error.
		virtual bool newBuffer(const unsigned long size) = 0;
		
	protected:
		std::string mFilePath;
		unsigned char* mBuffer;
		unsigned long mReadPosition;
		unsigned long mBufferSize;
		unsigned long mFileSize;
		FILEIO::FILE_STATUS mFileStatus;
		FILEIO::OPEN_MODE mOpenMode;
		bool mBufferOwned;
		
	private:
		// No copying Files
		BaseFile(const BaseFile& rhs);
		BaseFile& operator=(const BaseFile& rhs);
};

}

#endif

#if defined(LINUX) || defined(PANDORA)
#include "Linux/File.h"
#elif defined(WIN32)
#include "Win32/File.h"
#elif defined(ANDROID)
#include "Android/File.h"
#elif defined(IOS) || defined(OSX)
#include "Mac/File.h"
#endif
