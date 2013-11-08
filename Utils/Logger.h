#ifndef _LOGGER_H_
#define _LOGGER_H_

struct GAE_File_s;

typedef enum GAE_LOG_OUTPUT_e {
	GAE_LOG_OUTPUT_FILE
,	GAE_LOG_OUTPUT_TERMINAL
,	GAE_LOG_OUTPUT_FILE_AND_TERMINAL
,	GAE_LOG_OUTPUT_SILENT
,	GAE_LOG_OUTPUT_DEFAULT
} GAE_LOG_OUTPUT;

typedef enum GAE_LOG_TYPE_e {
	GAE_LOG_TYPE_INFO
,	GAE_LOG_TYPE_DEBUG
,	GAE_LOG_TYPE_ERROR
,	GAE_LOG_TYPE_VERBATIM
,	GAE_LOG_TYPE_DEFAULT
} GAE_LOG_TYPE;

typedef enum GAE_LOG_FILETYPE_e {
	GAE_LOG_FILE_TEXT
,	GAE_LOG_FILE_HTML
,	GAE_LOG_FILE_UNOPENED
} GAE_LOG_FILETYPE;

typedef struct GAE_Logger_s {
	GAE_LOG_OUTPUT output;
	GAE_LOG_TYPE type;
	GAE_LOG_FILETYPE fileType;

	struct GAE_File_s* file;
} GAE_Logger_t;

/* Create a new Logger construct */
GAE_Logger_t* GAE_Logger_create();

/* Set the file the Logger deals with */
GAE_Logger_t* GAE_Logger_setFile(GAE_Logger_t* logger, const char* fileName, const GAE_LOG_FILETYPE fileType);

/* Sets a footer and closes the file */
GAE_Logger_t* GAE_Logger_closeFile(GAE_Logger_t* logger);

/* Logs something out through this Logger - which may be to a file, terminal or both */
GAE_Logger_t* GAE_Logger_log(GAE_Logger_t* logger, const GAE_LOG_TYPE type, const GAE_LOG_OUTPUT output, const char* string, ... );

void GAE_Logger_delete(GAE_Logger_t* logger);

#endif
