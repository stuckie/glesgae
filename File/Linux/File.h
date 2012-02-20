#ifndef _FILE_H_
#define _FILE_H_

#include <cstdio>

namespace GLESGAE
{

class File : public BaseFile
{
	public:
		File(const std::string& filepath);
		~File();
		
		/// Open the file in the specified mode.
		FILEIO::FILE_STATUS open(const FILEIO::OPEN_MODE openMode, const FILEIO::FILE_MODE fileMode);
		
		/// Close the file - with an option to delete the data.
		FILEIO::FILE_STATUS close(const FILEIO::CLOSE_MODE mode = FILEIO::CLOSE_RETAIN_DATA);
		
		/// Delete buffer data.
		bool deleteBuffer();
		
		/// Read File - automatically reads all, or up to the specified amount till it reaches the end of the file.
		FILEIO::READ_STATUS read(const unsigned long amount = static_cast<unsigned long>(-1U));
		
		/// Write File - write out what's in the buffer.
		FILEIO::WRITE_STATUS write();
		
		/// Set Read position of file.
		FILEIO::READ_STATUS setReadPosition(const unsigned long readPosition);
		
		/// Set the file buffer.
		bool setBuffer(unsigned char* buffer, const unsigned long size, const bool copy = false);
		
		/// Create a new file buffer.
		/// Returns true if successful, false if there's an error.
		bool newBuffer(const unsigned long size);
		
	private:
		// No copying
		File(const File& rhs);
		File& operator=(const File& rhs);
		
		FILE* mFile;
};

}

#endif
