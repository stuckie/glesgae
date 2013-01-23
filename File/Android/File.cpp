#include "../File.h"

#include "../../Platform/Application.h"
#include <cstring> // memcpy

using namespace GLESGAE;

File::File(const std::string& filepath)
: BaseFile(filepath)
, mFile(0)
{
}

File::~File()
{
	if (0 != mFile) {
		fclose(mFile);
		mFile = 0;
	}
}

FILEIO::FILE_STATUS File::open(const FILEIO::OPEN_MODE openMode, const FILEIO::FILE_MODE fileMode)
{
	if (mFileStatus != FILEIO::FILE_CLOSED) {
		Application::getInstance()->getLogger()->log("File: File already open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::FILE_ERROR;
	}
	
	if (0 != mFile) {
		Application::getInstance()->getLogger()->log("File: File handle open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::FILE_ERROR;
	}
	
	if (0 != mBuffer) {
		Application::getInstance()->getLogger()->log("File: Buffer already used\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::FILE_ERROR;
	}
	
	std::string openString;
	switch (openMode) {
		case FILEIO::OPEN_READ:
			openString = "r";
			mBufferOwned = true;
			break;
		case FILEIO::OPEN_WRITE:
			openString = "w";
			mBufferOwned = false;
			break;
		case FILEIO::OPEN_APPEND:
			openString = "a";
			mBufferOwned = false;
			break;
	};
	
	std::string fileString;
	switch (fileMode) {
		case FILEIO::FILE_ASCII:
			fileString = "";
			break;
		case FILEIO::FILE_BINARY:
			fileString = "b";
			break;
	};
	
	const std::string options(openString + fileString);
	mFile = fopen(mFilePath.c_str(), options.c_str());
	
	if (0 == mFile) {
		Application::getInstance()->getLogger()->log("File: File not found: " + mFilePath + "\n", Logger::LOG_TYPE_ERROR);
		mFileStatus = FILEIO::FILE_NOT_FOUND;
		return mFileStatus;
	}
	
	mFileStatus = FILEIO::FILE_OPEN;
	mOpenMode = openMode;
	
	fseek(mFile, 0, SEEK_END);
	mFileSize = ftell(mFile);
	rewind(mFile);
	
	return mFileStatus;
}

FILEIO::FILE_STATUS File::close(const FILEIO::CLOSE_MODE mode)
{
	if (mFileStatus != FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::FILE_ERROR;
	}
	
	if (0 == mFile) {
		Application::getInstance()->getLogger()->log("File: File handle already closed\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::FILE_ERROR;
	}
	
	fclose(mFile);
	mFile = 0;
	
	mFileStatus = FILEIO::FILE_CLOSED;
	
	if (mode == FILEIO::CLOSE_DELETE_DATA) {
		if (true == mBufferOwned) {
			delete [] mBuffer;
			mBuffer = 0;
			mBufferOwned = false;
			mBufferSize = 0U;
		}
	}
	
	return mFileStatus;
}

bool File::deleteBuffer()
{
	if (0 == mBuffer)
		return false;
	
	if (false == mBufferOwned)
		return false;
	
	delete [] mBuffer;
	mBuffer = 0;
	return true;
}

FILEIO::READ_STATUS File::read(const unsigned long amount)
{
	if (mOpenMode != FILEIO::OPEN_READ) {
		Application::getInstance()->getLogger()->log("File: File not in opened for reading\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (mFileStatus != FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (0 == mFile) {
		Application::getInstance()->getLogger()->log("File: File handle not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (false == mBufferOwned) {
		Application::getInstance()->getLogger()->log("File: Buffer not ours\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	unsigned long readAmount(amount);
	if (readAmount < mFileSize)
		mBufferSize = readAmount;
	else {
		mBufferSize = mFileSize;
		readAmount = mFileSize;
	}
	
	if (0 != mBuffer)
		delete [] mBuffer;
	
	mBuffer = new unsigned char[mBufferSize + 1U];
	memset(mBuffer, '\0', mBufferSize + 1U);
	if (0 == mBuffer) {
		Application::getInstance()->getLogger()->log("File: Creating zero buffer\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	mBufferOwned = true;
	const long read(fread(mBuffer, 1, mBufferSize, mFile));
	mReadPosition += static_cast<unsigned long>(read);
	
	if (static_cast<unsigned long>(read) == readAmount)
		return FILEIO::READ_OK;
	else if (feof(mFile))
		return FILEIO::READ_EOF;
	else {
		Application::getInstance()->getLogger()->log("File: Read Error - read:" + toString(read) + ", expected: " + toString(readAmount) + "\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
}

FILEIO::WRITE_STATUS File::write()
{
	if ((mOpenMode != FILEIO::OPEN_WRITE) && (mOpenMode != FILEIO::OPEN_APPEND)) {
		Application::getInstance()->getLogger()->log("File: File not open for writing\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::WRITE_ERROR;
	}
	
	if (mFileStatus != FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::WRITE_ERROR;
	}
	
	if (0 == mFile) {
		Application::getInstance()->getLogger()->log("File: File handle not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::WRITE_ERROR;
	}
	
	if (0 == mBuffer) {
		Application::getInstance()->getLogger()->log("File: No Buffer\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::WRITE_ERROR;
	}
	
	const long written(fwrite(mBuffer, 1, mBufferSize, mFile));
	if (static_cast<unsigned long>(written) == mBufferSize)
		return FILEIO::WRITE_OK;
	else {
		Application::getInstance()->getLogger()->log("File: File Write Error\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::WRITE_ERROR;
	}
}

FILEIO::READ_STATUS File::setReadPosition(const unsigned long readPosition)
{
	if (mFileStatus != FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (mOpenMode != FILEIO::OPEN_READ) {
		Application::getInstance()->getLogger()->log("File: File not open for reading\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (0 == mFile) {
		Application::getInstance()->getLogger()->log("File: File handle not open\n", Logger::LOG_TYPE_ERROR);
		return FILEIO::READ_ERROR;
	}
	
	if (mReadPosition < mFileSize) {
		mReadPosition = readPosition;
		fseek(mFile, mReadPosition, SEEK_SET);
		return FILEIO::READ_OK;
	}
	else {
		mReadPosition = mFileSize;
		fseek(mFile, 0, SEEK_END);
		return FILEIO::READ_EOF;
	}
}

bool File::setBuffer(unsigned char* buffer, const unsigned long size, const FILEIO::BUFFER_TYPE type)
{
	if (mFileStatus == FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File open, cannot set buffer\n", Logger::LOG_TYPE_ERROR);
		return false;
	}
	
	if (mBufferOwned == true)
		delete [] mBuffer;
	
	switch(type) {
		case FILEIO::BUFFER_COPY: {
			mBuffer = new unsigned char[size];
			if (0 == mBuffer)
				return false;
			memcpy(mBuffer, buffer, size);
			mBufferOwned = true;
			mBufferSize = size;
			mReadPosition = 0U;
		}
		break;
		case FILEIO::BUFFER_NOT_OWNED: {
			mBuffer = buffer;
			mBufferOwned = false;
			mBufferSize = size;
			mReadPosition = 0U;
		}
		break;
		case FILEIO::BUFFER_OWNED: {
			mBuffer = buffer;
			mBufferOwned = true;
			mBufferSize = size;
			mReadPosition = 0U;
		}
		break;
	}
	
	return true;
}

bool File::newBuffer(const unsigned long size)
{
	if (mFileStatus == FILEIO::FILE_OPEN) {
		Application::getInstance()->getLogger()->log("File: File open, cannot create buffer\n", Logger::LOG_TYPE_ERROR);
		return false;
	}
	
	if (mBufferOwned == true)
		delete [] mBuffer;
	
	mBuffer = new unsigned char[size];
	mBufferOwned = true;
	mBufferSize = size;
	mReadPosition = 0U;
	
	return true;
}
