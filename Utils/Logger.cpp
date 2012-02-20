#include "Logger.h"

#include <string>
#include <fstream>
#include <iostream>
#include <ctime>

using namespace GLESGAE;

Logger::Logger()
: mOutput(LOG_OUTPUT_TERMINAL)
, mType(LOG_TYPE_DEBUG)
, mFileType(LOG_FILE_UNOPENED)
, mFilename("engine.log")
{
	
}

Logger::~Logger()
{
	closeFile();
}

void Logger::setFile(const std::string& filename, const FileType& fileType)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	mFilename = timeString + "_" + filename; 
	mFileType = fileType;
	
	std::ofstream logFile;
	logFile.open(mFilename.c_str());
	logFile << getHeader() << std::flush;
	logFile.close();
}

void Logger::closeFile()
{
	std::ofstream logFile;
	logFile.open(mFilename.c_str(), std::ios::app);
	logFile << getFooter() << std::flush;
	logFile.close();
	
	mFileType = LOG_FILE_UNOPENED;
}

void Logger::log(const std::string& text, const Type type, const Output output)
{
	bool outputText(true);
	Type logType(mType);
	Output logOutput(mOutput);
	
	// Check for non-defaults.
	if (type != LOG_TYPE_DEFAULT)
		logType = type;
		
	if (output != LOG_OUTPUT_DEFAULT)
		logOutput = output;
		
	if (LOG_OUTPUT_SILENT == logOutput) // if we're not going to output this, might as well leave now.
		return;
		
	// Check if we are actually going to output this.
	switch (logType) {
		case LOG_TYPE_DEBUG:
			#if !defined(DEBUG)
				outputText = false;
			#endif
			break;
		case LOG_TYPE_INFO:
		case LOG_TYPE_ERROR:
			outputText = true;
			break;
		default:
			log("Logger: Unknown log type! Tried to Log - " + text, LOG_TYPE_ERROR);
	}
	
	if (false == outputText)// if we're not going to output this, might as well leave now.
		return;
		
	// See where we're going to output this.
	switch (logOutput) {
		case LOG_OUTPUT_FILE:
			logToFile(text, logType);
			break;
		case LOG_OUTPUT_FILE_AND_TERMINAL:
			logToFile(text, logType);
			logToTerm(text, logType);
			break;
		case LOG_OUTPUT_TERMINAL:
			logToTerm(text, logType);
			break;
		default:
			log("Logger: Unknown log output! Tried to Log - " + text, LOG_TYPE_ERROR, LOG_OUTPUT_FILE_AND_TERMINAL);
	}
}

void Logger::logToTerm(const std::string& text, const Type& type)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	switch (type) {
		case LOG_TYPE_DEBUG:
			std::cout << "[DEBUG]" << timeString << "[DEBUG]" << text;
			break;
		case LOG_TYPE_INFO:
			std::cout << "[INFO]" << timeString << "[INFO]" << text;
			break;
		case LOG_TYPE_ERROR:
			std::cerr << "[ERROR]" << timeString << "[ERROR]" << text;
			break;
		default:
			break; // Should not get here.. so just ignore...
	}
}

void Logger::logToFile(const std::string& text, const Type& type)
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	std::string finalText;
	
	switch (mFileType) {
		case LOG_FILE_TEXT:
			switch (type) {
				case LOG_TYPE_DEBUG:
					finalText = ("[DEBUG]" + timeString + "[DEBUG]" + text);
					break;
				case LOG_TYPE_INFO:
					finalText = ("[INFO]" + timeString + "[INFO]" + text);
					break;
				case LOG_TYPE_ERROR:
					finalText = ("[ERROR]" + timeString + "[ERROR]" + text);
					break;
				default:
					break; // Should not get here.. so just ignore...
			}
			break;
		case LOG_FILE_HTML:
			switch (type) {
				case LOG_TYPE_DEBUG:
					finalText = ("\t<div id=\"DEBUG\">[" + timeString + "] " + text + "</div>");
					break;
				case LOG_TYPE_INFO:
					finalText = ("\t<div id=\"INFO\">[" + timeString + "] " + text + "</div>");
					break;
				case LOG_TYPE_ERROR:
					finalText = ("\t<div id=\"ERROR\">[" + timeString + "] " + text + "</div>");
					break;
				default:
					break; // Should not get here.. so just ignore...
			}
			break;
		case LOG_FILE_UNOPENED:
			log("Logger: There is no file open to output to!", LOG_TYPE_ERROR, LOG_OUTPUT_TERMINAL);
			return;
		default:
			break; // Should not get here.. so just ignore
	}
	
	std::ofstream logFile;
	logFile.open(mFilename.c_str(), std::ios::app);
	logFile << finalText << std::flush;
	logFile.close();
}

std::string Logger::getHeader()
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	std::string header;
	
	switch (mFileType) {
		case LOG_FILE_HTML:
			header = ("<html>\n\t<head>\n\t\t<title>GLESGAE Log</title>\n\t</head>\n\t<body>\n\t\t<h1>Started - " + timeString + "</h1>");
			break;
		case LOG_FILE_TEXT:
			header = "GLESGAE Log\nStarted - " + timeString + "\n";
			break;
		default:
			break;
	}
	
	return header;
}

std::string Logger::getFooter()
{
	time_t rawTime;
	time(&rawTime);
	std::string timeString(ctime(&rawTime));
	
	std::string footer;
	
	switch (mFileType) {
		case LOG_FILE_HTML:
			footer = ("\t\t<h1>Ended - " + timeString + "</h1>\n\t</body>\n</html>");
			break;
		case LOG_FILE_TEXT:
			footer = "Ended - " + timeString + "\n";
			break;
		default:
			break;
	}
	
	return footer;
}
