#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>

#ifdef _WIN32
#elif __linux__
#endif

//THIS IS NOT A INIT FILE, THIS IS JUST A LOG, LOADING AND CRASH REPORT LIBRARY

/*
LOG LEVEL is the output of the crash file
LOG LVL : 3 is nothing shown
LOG LVL : 2 is only crash or error
LOG LVL : 1 is same as 0 but with warning 
LOG LVL : 0 is everything and should be only for debugging
*/
#define LOGLEVEL 0

#if LOGLEVEL <= 2
	#define LOG_ERROR
#endif
#if LOGLEVEL <= 1
	#define LOG_WARNING
#endif
#if LOGLEVEL <= 0
	#define LOG_INFO
#endif // LOGLEVEL >= 0

//Toggle to 1 to see process initilisizing and to 0
#define LOGINIT 1

//Comment out/in what you need
#define KEYBOARD
#define MOUSE
#define SCREEN

#define logger Log::getInstance()


class Log
{

private:

	std::string name;
	std::string data;

#if LOGINIT == 1
	bool inInit;
	std::string initName;
	std::chrono::time_point<std::chrono::system_clock> duration;
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
#endif

	std::fstream file;
	Log() {
		file.open("log.txt", std::fstream::out | std::fstream::trunc);
		file << "Grab some milk and cookie, let's start the logs\n";
#if LOGINIT == 1
		inInit = false;
#endif
	};
	Log(Log const&);
	void operator= (Log const&) {};
	void write() { file << data; }

	std::string time() {

		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string str = std::ctime(&time);
		str.erase(str.size() - 1);
		return str;
	}

public:

	//Get the instance of the logger
	static Log& getInstance() {
		static Log instance;
		return instance;
	};

	void startInit(std::string name) {
#if LOGINIT == 1
		if (inInit)
		{
			crash("Last init did not finish");
			exit(1);
		}

		inInit = true;
		start = std::chrono::system_clock::now();
		initName = name;
		data = "\n[LOADING] - " + time() + " - " + initName + " is loading";
		write();
#endif
	};

	void initLog(std::string str)
	{
#if LOGINIT == 1
		data = "\n\t  - " + str;
		write();
#endif
	};

	void endInit()
	{
#if LOGINIT == 1
		inInit = false;
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		data = "\n[LOADING] - " + time() + " - " + initName + " succesfully loaded in " + std::to_string(elapsed_seconds.count()) + "s";
		write();
#endif
	}


	//Write a error in log file, this is a high prority log level
	void error(std::string str) {
#ifdef LOG_ERROR
		data = "\n[ ERROR ] - " + time() + " - " + str;
		write();
#endif
	};

	//write warning in log file, this is a mid prority log level
	void warning(std::string str) {
#ifdef LOG_WARNING
		data = "\n[WARNING] - " + time() + " - " + str;
		write();
#endif
	};
	
	//write info in log file, this is the lowest prority log level
	void info(std::string str) {
#ifdef LOG_INFO
		data = "\n[DEFAULT] - " + time() + " - " + str;
		write();
#endif // LOG_INFO
	};

	//Write program crashes in log file, this one cannot be removed
	void crash(std::string str)
	{
		data = "\n[ CRASH ] - " + time() + " - " + str;
		write();
	};

	~Log(){
		file.close();
	};
};
