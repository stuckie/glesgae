#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <string>
#include <sstream>

// Quick function to convert anything to a string.
template <class T>
inline std::string toString (const T& t)
{
	std::stringstream ss;
	ss << t;
	return ss.str();
}

namespace GLESGAE
{

class Logger
{
	public:
		/// Creates or returns the current active instance of Logger.
		static Logger& getInstance();

		~Logger();

		enum Output {
			LOG_OUTPUT_FILE
		,	LOG_OUTPUT_TERMINAL
		,	LOG_OUTPUT_FILE_AND_TERMINAL
		,	LOG_OUTPUT_SILENT
		,	LOG_OUTPUT_DEFAULT
		};

		enum Type {
			LOG_TYPE_INFO
		,	LOG_TYPE_DEBUG
		,	LOG_TYPE_ERROR
		,	LOG_TYPE_DEFAULT
		};

		enum FileType {
			LOG_FILE_TEXT
		,	LOG_FILE_HTML
		,	LOG_FILE_UNOPENED
		};

		/// Set the default Output for Logger.
		void setOutput(const Output& output) { mOutput = output; }

		/// Set the default log Type for Logger.
		void setType(const Type& type) { mType = type; }

		/// Set the output file for Logger, and it's type.
		void setFile(const std::string& filename, const FileType& fileType);

		/// Closes the log file.
		void closeFile();

		/// Log a string.
		/// Optional parameters include overriding Type and Output.
		void log(const std::string& text, const Type type = LOG_TYPE_DEFAULT, const Output output = LOG_OUTPUT_DEFAULT);

	protected:
		/// Log text string to File.
		void logToFile(const std::string& text, const Type& type);

		/// Log text string to Terminal.
		void logToTerm(const std::string& text, const Type& type);

		/// Creates a log Header.
		std::string getHeader();

		/// Creates a log Footer.
		std::string getFooter();

	private:
		/// Private constructor to stop accidental creations outside of the instance.
		Logger();

		Output mOutput;				//!< Default Log Output
		Type mType;					//!< Default Log Type
		FileType mFileType;			//!< Current File Type
		std::string mFilename;		//!< Current File Name

		static Logger* mInstance;	//!< Active instance of the Logger
};

}

#endif
