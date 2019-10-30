/* ==================================================== */
/*                     Logging.cpp                      */
/* ==================================================== */

#include "logging.h"

using namespace terminal_logger;

namespace file_logger
{

	/* ==================================================== */
	/*                     Constructor                      */
	/* ==================================================== */
	file_logger::file_logger(){}


	/* ==================================================== */
	/*                     Destructor                       */
	/* ==================================================== */
	file_logger::~file_logger(){}


	/* ==================================================== */
	/*            open file and generate name               */
	/* ==================================================== */
	string file_logger::open_file()
	{
		
		auto c = chrono::system_clock::now();
		time_t end_time = chrono::system_clock::to_time_t(c);
		auto t_str = strtok( ctime(&end_time), "\n");

		stringstream c_;
		c_<<t_str;

		string date_= c_.str();

		string file_extension = ".log";
		file_name.clear();
		file_name = file_name + date_ + file_extension;
		file_name =file_name.c_str();

		LOG_Info("logs are stored in '.log' file in 'tmp' folder")
		return file_name;
	}


	/* ==================================================== */
	/*           log string to file one-by-one              */
	/* ==================================================== */
	void file_logger::logStrings_to_file(string file_name, const string &query)
	{
		try
		{
			ofstream log_file(file_name, ios_base::out | ios_base::app);
			log_file << query << endl;
		}
		catch(exception &e)
		{
			LOG_ERROR_THROW(runtime_error, query)
		}
	}



	/* ==================================================== */
	/*         log multiple strings to a file at once       */
	/* ==================================================== */
	void file_logger::logVecStrings_to_file(string file_name, const vector<string>& query)
	{
		try
		{
			ofstream log_file(file_name, ios_base::out | ios_base::app);
			for (unsigned int i = 0; i < query.size(); ++i)
			{
				log_file << query[i]<< endl;
			}
		}
		catch(exception &e)
		{
			LOG_Error("caught exception "<< e.what())
		}
	}



	/* ==================================================== */
	/*                close log file(s)                     */
	/* ==================================================== */
	void file_logger::close_file(string file_name)
	{
		ifstream i;
		filebuf * fbuf = i.rdbuf();
		fbuf->open (file_name, ios::in);

		if(fbuf->is_open())
		{
			LOG_Info("closing file " << file_name);
			fbuf->close();
		}
	}

	
	/* ==================================================== */
	/*                    add strings                       */
	/* ==================================================== */
	vector<string> file_logger::add_strings(vector<string> &s1, vector<string> &s2)
	{
		int i =0;
		vector<string> s;
		s.resize(s1.size());

		if(s1.size() == s2.size())
		{
			try
			{
				for(vector<string>::iterator it=s1.begin(); it!= s1.end(); ++it)
				{
					s.at(i) = s2.at(i) + ' ' + s1.at(i);
					// LOG_Info(i <<" "<< s.at(i));
					i++;
				}
			}
			catch(exception &e)
			{
				LOG_Error("caught exception " << e.what())
			}
		}
		else
		{
			LOG_Error("can't add, strings have different length\n")
		}

		return s;
	}

}//namespace file_logger
