#include "Logger.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "../File/File.h"

#define TERMINAL_BUFFER_SIZE 512
#define FILE_BUFFER_SIZE 1024

#if defined(ANDROID)
	#include <android/log.h>
	#define ANDROID_INFO(...) ((void)__android_log_print(ANDROID_LOG_INFO, "[INFO] ", __VA_ARGS__))
	#define ANDROID_DEBUG(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "[DEBUG] ", __VA_ARGS__))
	#define ANDROID_ERROR(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "[ERROR] ", __VA_ARGS__))
	#define ANDROID_VERBATIM(...) ((void)__android_log_print(ANDROID_LOG_INFO, "", __VA_ARGS__))
#endif

void setFileHeader(char* header, const GAE_LOG_FILETYPE fileType);
void setFileFooter(char* footer, const GAE_LOG_FILETYPE fileType);
void logToFile(GAE_Logger_t* logger, const GAE_LOG_TYPE type, const char* string);
void logToTerm(const GAE_LOG_TYPE type, const char* string);

/* Create a new Logger construct */
GAE_Logger_t* GAE_Logger_create() {
	GAE_Logger_t* logger = (GAE_Logger_t*)malloc(sizeof(GAE_Logger_t));
	logger->output = GAE_LOG_OUTPUT_TERMINAL;
	logger->type = GAE_LOG_TYPE_VERBATIM;
	logger->fileType = GAE_LOG_FILE_UNOPENED;
	logger->file = 0;

	return logger;
}

/* Set the file the Logger deals with */
GAE_Logger_t* GAE_Logger_setFile(GAE_Logger_t* logger, const char* fileName, const GAE_LOG_FILETYPE fileType) {
	char fullFileName[256];
	char header[FILE_BUFFER_SIZE];
	time_t rawTime;

	if (0 == logger) return logger;
	time(&rawTime);
	assert(256 > (strlen(fileName) + strlen(ctime(&rawTime)) + 5));
	if (fileType == GAE_LOG_FILE_HTML)
		sprintf(fullFileName, "%s %s.html", ctime(&rawTime), fileName);
	else
		sprintf(fullFileName, "%s %s.log", ctime(&rawTime), fileName);

	logger->fileType = fileType;

	assert(0 == logger->file);
	logger->file = GAE_File_create(fullFileName);
	assert(logger->file);
	GAE_File_open(logger->file, GAE_FILE_OPEN_APPEND, GAE_FILE_ASCII, 0);
	setFileHeader(header, fileType);
	GAE_Logger_log(logger, GAE_LOG_TYPE_VERBATIM, GAE_LOG_OUTPUT_FILE, "%s", header);

	return logger;
}

/* Closes the file this Logger is dealing with */
GAE_Logger_t* GAE_Logger_closeFile(GAE_Logger_t* logger) {
	char footer[FILE_BUFFER_SIZE];
	if (0 == logger) return logger;

	setFileFooter(footer, logger->fileType);
	GAE_Logger_log(logger, GAE_LOG_TYPE_VERBATIM, GAE_LOG_OUTPUT_FILE, "%s", footer);
	GAE_File_close(logger->file, GAE_FILE_CLOSE_DELETE_DATA, 0);
	GAE_File_delete(logger->file);
	logger->file = 0;
	logger->fileType = GAE_LOG_FILE_UNOPENED;

	return logger;
}

/* Logs something out through this Logger - which may be to a file, terminal or both */
GAE_Logger_t* GAE_Logger_log(GAE_Logger_t* logger, const GAE_LOG_TYPE type, const GAE_LOG_OUTPUT output, const char* string, ... ) {
	GAE_LOG_TYPE logType = logger->type;
	GAE_LOG_OUTPUT logOutput = logger->output;
	char text[TERMINAL_BUFFER_SIZE];
	va_list args;
	if (0 == logger) return logger;

	va_start(args, string);
	vsprintf(text, string, args); /* potential buffer overflow */
	va_end(args);

	if (GAE_LOG_OUTPUT_SILENT == output)
		return logger;

	if (GAE_LOG_TYPE_DEFAULT != type)
		logType = type;

	if (GAE_LOG_OUTPUT_DEFAULT != output)
		logOutput = output;

	switch (logOutput) {
		case GAE_LOG_OUTPUT_FILE:
			logToFile(logger, logType, text);
			break;
		case GAE_LOG_OUTPUT_FILE_AND_TERMINAL:
			logToFile(logger, logType, text);
			logToTerm(logType, text);
			break;
		case GAE_LOG_OUTPUT_TERMINAL:
			logToTerm(logType, text);
			break;
		default:
			GAE_Logger_log(logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_FILE_AND_TERMINAL, "Logger: Unknown log output while trying to log: %s", text);
			break;
	}

	return logger;
}

void GAE_Logger_delete(GAE_Logger_t* logger) {
	if (0 == logger) return;

	if (0 != logger->file) {
		GAE_Logger_closeFile(logger);
	}

	free(logger);
}

void logToTerm(const GAE_LOG_TYPE type, const char* text) {
	time_t rawTime;
	char* timeString;

	time(&rawTime);
	timeString = ctime(&rawTime);
	
	switch (type) {
		case GAE_LOG_TYPE_DEBUG:
			#if defined(ANDROID)
				ANDROID_DEBUG("%s", text);
			#else
				printf("[DEBUG]%s[DEBUG]%s\n", timeString, text);
			#endif
			break;
		case GAE_LOG_TYPE_INFO:
			#if defined(ANDROID)
				ANDROID_INFO("%s", text);
			#else
				printf("[INFO]%s[INFO]%s\n", timeString, text);
			#endif
			break;
		case GAE_LOG_TYPE_ERROR:
			#if defined(ANDROID)
				ANDROID_ERROR("%s", text);
			#else
				printf("[ERROR]%s[ERROR]%s\n", timeString, text);
			#endif
			break;
		case GAE_LOG_TYPE_VERBATIM:
			#if defined(ANDROID)
				ANDROID_VERBATIM("%s", text);
			#else
				printf("%s", text);
			#endif
			break;
		default:
			break;
	}
}

void logToFile(GAE_Logger_t* logger, const GAE_LOG_TYPE type, const char* text) {
	time_t rawTime;
	char* timeString;
	char finalText[FILE_BUFFER_SIZE];
	
	time(&rawTime);
	timeString = ctime(&rawTime);
	
	switch (logger->fileType) {
		case GAE_LOG_FILE_TEXT:
			switch (type) {
				case GAE_LOG_TYPE_DEBUG:
					sprintf(finalText, "[DEBUG]%s[DEBUG]%s\n", timeString, text);
					break;
				case GAE_LOG_TYPE_INFO:
					sprintf(finalText, "[INFO]%s[INFO]%s\n", timeString, text);
					break;
				case GAE_LOG_TYPE_ERROR:
					sprintf(finalText, "[ERROR]%s[ERROR]%s\n", timeString, text);
					break;
				default:
                    sprintf(finalText, "%s\n", text);
					break;
			}
			break;
		case GAE_LOG_FILE_HTML:
			switch (type) {
				case GAE_LOG_TYPE_DEBUG:
					sprintf(finalText, "\t<div id=\"DEBUG\">[%s] %s</div>\n", timeString, text);
					break;
				case GAE_LOG_TYPE_INFO:
					sprintf(finalText, "\t<div id=\"INFO\">[%s] %s</div>\n", timeString, text);
					break;
				case GAE_LOG_TYPE_ERROR:
					sprintf(finalText, "\t<div id=\"ERROR\">[%s] %s</div>\n", timeString, text);
					break;
				default:
                    sprintf(finalText, "%s\n", text);
					break;
			}
			break;
		case GAE_LOG_FILE_UNOPENED:
			GAE_Logger_log(logger, GAE_LOG_TYPE_ERROR, GAE_LOG_OUTPUT_FILE_AND_TERMINAL, "Logger: No file opened.");
			return;
		default:
			break;
	}
	
	assert(logger->file);
	GAE_File_setBuffer(logger->file, (GAE_BYTE*)finalText, strnlen(finalText, FILE_BUFFER_SIZE), GAE_FILE_BUFFER_NOT_OWNED, 0);
	GAE_File_write(logger->file, 0);

}

void setFileHeader(char* header, const GAE_LOG_FILETYPE fileType) {
	time_t rawTime;
	char* timeString;

	time(&rawTime);
	timeString = ctime(&rawTime);
	
	switch (fileType) {
		case GAE_LOG_FILE_HTML:
			sprintf(header, "<html>\n\t<head>\n\t\t<title>GLESGAE Log</title>\n\t</head>\n\t<body>\n\t\t<h1>Started - %s</h1>\n", timeString);
			break;
		case GAE_LOG_FILE_TEXT:
			sprintf(header, "GLESGAE Log\nStarted - %s\n", timeString);
			break;
		default:
			break;
	}
}

void setFileFooter(char* footer, const GAE_LOG_FILETYPE fileType) {
	time_t rawTime;
	char* timeString;

	time(&rawTime);
	timeString = ctime(&rawTime);
	
	switch (fileType) {
		case GAE_LOG_FILE_HTML:
			sprintf(footer, "\t\t<h1>Ended - %s</h1>\n\t</body>\n</html>\n", timeString);
			break;
		case GAE_LOG_FILE_TEXT:
			sprintf(footer, "Ended - %s\n", timeString);
			break;
		default:
			break;
	}
}
