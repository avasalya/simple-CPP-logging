/* ==================================================== */
/*                     logging.h                        */
/* ==================================================== */

#ifndef LOGGING_H_
#define LOGGING_H_

#include <dirent.h>

#include <stdlib.h>
#include <iostream>

#include <string> 
#include <cstring>

#include <fstream>
#include <sstream>

#include <vector>

#include <ctime>    

#include <memory>
#include <thread>
#include <cstdlib>
#include <pthread.h>
#include <functional>
#include <future>
#include <mutex>

using namespace std;


/* ==================================================== */
/*              MACROS for Terminal logs                */
/* ==================================================== */
namespace terminal_logger
{

	constexpr auto none = "\033[00m";

	constexpr auto Red_Bold_Underline_highlight = "\033[01;04;31;47m";
	constexpr auto Red_Bold_Underline = "\033[01;04;31m";
	constexpr auto Red_Bold = "\033[01;31m";
	constexpr auto Red = "\033[00;31m";
	constexpr auto Purple = "\033[0;35m";

	constexpr auto Cyan = "\033[0;36m";
	constexpr auto Blue = "\033[0;34m";
	constexpr auto Green = "\033[0;32m";

	constexpr auto Black = "\033[0;30m";


	#define LOG_Emergency(args) cerr << Red_Bold_Underline_highlight << args << none << endl;
	#define LOG_Alert(args) cerr << Red_Bold_Underline << args << none << endl;
	#define LOG_Critical(args) cerr << Red_Bold << args << none << endl;
	#define LOG_Error(args) cerr << Red << args << none << endl;
	#define LOG_Warning(args) cerr << Purple << args << none << endl;

	#define LOG_Debug(args) cout << Cyan << args << none << endl;

	#define LOG_Info(args) cout << Blue << args << none << endl;
	#define LOG_Success(args) cout << Green << args << none << endl;

	#define LOG_General(args) cout << Black << args << none << endl;

	#define LOG_ERROR_THROW(exception_type, args)		\
	{													\
		stringstream s;									\
		s << args;										\
		LOG_Error(s.str())								\
		throw exception_type(s.str());					\
	}

}//namespace terminal_logger



/* ==================================================== */
/*     file_logger Class to write logs to file          */
/* ==================================================== */
namespace file_logger
{

	class file_logger
	{
	
	public:
		file_logger();

		~file_logger();

		string open_file();

		void close_file(string file_name);

		void logStrings_to_file(string file_name, const string &query);

		void logVecStrings_to_file(string file_name, const vector<string>& query);

		vector<string> add_strings(vector<string> &s1, vector<string> &s2);

	private:
		string file_name;
	};

}//namespace file_logger

#endif