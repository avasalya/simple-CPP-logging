/* ==================================================== */
/*              Testing Cpp_Logging_Library             */
/* ==================================================== */



//A logging library in C++ with the following features:

// DONE - can log strings to a file or to the terminal depending on the configuration

// DONE - multithreaded

// DONE - has automated tests with your choice of testing framework [used Cmake CTest]

// DONE - complie using CMake
//        mkdir build && mkdir tmp
//        cd build && cmake ../
//        make -j8 && sudo make -j8 install && main
//        make test


#include "logging.h"

using namespace file_logger;
using namespace terminal_logger;


int main()
{

	/* ==================================================== */
	/*                Testing - variable                    */
	/* ==================================================== */

	shared_ptr<file_logger::file_logger> fLog;
	fLog = make_shared<file_logger::file_logger>();

	vector<string> s1 = {"thank ", "you" , "for ", "your ", "support\n"};
	vector<string> s2 = {"thank ", "you" , "for ", "your ", "support"};






	/* ==================================================== */
	/*           TEST - terminal log configuration          */
	/* ==================================================== */

	cout << "\n***use below expressions to log strings & common data types on the terminal***\n"<<endl;

	int Level = 0;

	LOG_Emergency("use this to 'Log_Emergency' messages on terminal: Level=" << Level << " - highest")cout<<"\n";
	LOG_Alert("use this to 'Log_Alert' messages on terminal: Level=1\n")
	LOG_Critical("use this to 'Log_Critical' messages on terminal: Level=2\n")

	LOG_Error("use this to 'Log_Error' messages on terminal: Level=3\n")
	LOG_Warning("use this to 'Log_Warning' messages on terminal: Level=4\n")

	LOG_Debug("use this to 'Log_Debug' messages on terminal: Level=5\n")

	LOG_Info("use this to 'Log_Info' messages on terminal: Level=6\n")
	LOG_Success("use this to 'Log_Success' messages on terminal: Level=7 - lowest\n")

	LOG_General("use this to 'Log_general' messages on terminal\n")

	LOG_Info("use 'LOG_ERROR_THROW' to catch std exceptions and throw Error message, such as-- 'LOG_ERROR_THROW(std::runtime_error, runtime_error --- 'name_your_reason')")


	cout << "\n***use below expressions (see code) to log strings to the file, with and without Multithreading***\n"<<endl;






	/* ==================================================== */
	/*            TEST - save log to file                   */
	/* ==================================================== */

	string dateStamp =fLog->open_file();

	LOG_General("\nan example -- displaying log strings on terminal which are being saved into files-->>");

	/* receive individual strings in loop*/
	auto name1 = "../tmp/Project_strings_log_" + dateStamp;
	for(auto j : s1)
	{
		LOG_General(j);
		fLog->logStrings_to_file(name1,j);
	}

	/*vector of strings*/
	auto name2 = "../tmp/Project_vector_of_strings_log_" + dateStamp;
	fLog->logVecStrings_to_file(name2, s2);

	// vector<string> D = fLog->add_strings(s1, s2);
	// for(unsigned int i=0; i<D.size(); ++i)
	// LOG_General( D[i] )






	/* ==================================================== */
	/*               TEST - Multithread --                  */
	/*      write logs to same file multiple times          */
	/* ==================================================== */

	auto name3 = "../tmp/Project_thread_strings_log_" + dateStamp;
	for(auto j : s1)
	{
		thread t1( &file_logger::file_logger::logStrings_to_file, fLog, name3, j);
		t1.join();
	}
	for(auto k : s2)
	{	thread t2( &file_logger::file_logger::logStrings_to_file, fLog, name3, k);
		t2.join();
	}


	auto name4 = "../tmp/Project_thread_vector_of_strings_log_" + dateStamp;
	thread t3( &file_logger::file_logger::logVecStrings_to_file, fLog, name4, s1);
	t3.join();
	thread t4( &file_logger::file_logger::logVecStrings_to_file, fLog, name4, s2);
	t4.join();






	/* ==================================================== */
	/*               TEST - Multithread --                  */
	/*      add two strings and log result to file          */
	/* ==================================================== */

	auto f1 = async( launch::async, &file_logger::file_logger::add_strings, fLog, ref(s1) ,ref(s2));
	vector<string> s = f1.get();
	// for(unsigned int i=0; i<s.size(); ++i)
		// LOG_General( s[i] )

	auto name5 = "../tmp/Project_thread_add_vector_of_strings_log_" + dateStamp;
	thread t5( &file_logger::file_logger::logVecStrings_to_file, fLog, name5, s);
	t5.join();






	/* ==================================================== */
	/*                 close log files                      */
	/* ==================================================== */

	/*closing log files*/
	fLog->close_file(name1);
	fLog->close_file(name2);
	fLog->close_file(name3);
	fLog->close_file(name4);
	fLog->close_file(name5);

	return 0;
}