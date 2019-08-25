#pragma once
#pragma warning(disable : 4996)

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
		file << "Noodles ready ? you're here for a time!\n\n";
#if LOGINIT == 1
		inInit = false;
#endif
	};
	Log(Log const&);
	void operator= (Log const&) {};
	void write() { file << data; }

	std::string time() {

		std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string str = "<";
		str += std::ctime(&time);
		str.erase(str.size() - 1);
		str += "> ";
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
			crash("init","Last init did not finish");
			exit(1);
		}

		inInit = true;
		start = std::chrono::system_clock::now();
		initName = name;
		data = time() + "[LOADING] [" + initName + "] start loading\n";
		write();
#endif
	};

	void initLog(std::string str)
	{
#if LOGINIT == 1
		data = time() + "\t\t  - " + str + "\n";
		write();
#endif
	};

	void endInit()
	{
#if LOGINIT == 1
		inInit = false;
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		data = time() + "[LOADING] [" + initName + "] succesfully loaded in " + std::to_string(elapsed_seconds.count()) + "s\n";
		write();
#endif
	}


	//Write a error in log file, this is a high prority log level
	void error(std::string name, std::string str) {
#ifdef LOG_ERROR
		data = time() + "[ ERROR ] [" + name + "] " + str + "\n";
		write();
#endif
	};

	//write warning in log file, this is a mid prority log level
	void warning(std::string name, std::string str) {
#ifdef LOG_WARNING
		data = time() + "[WARNING] [" + name + "] " + str + "\n";
		write();
#endif
	};
	
	//write info in log file, this is the lowest prority log level
	void info(std::string name, std::string str) {
#ifdef LOG_INFO
		data = time() + "[DEFAULT] [" + name + "] " + str + "\n";
		write();
#endif // LOG_INFO
	};

	//Write program crashes in log file, this one cannot be removed
	void crash(std::string name, std::string str)
	{
		data = time() + "[ CRASH ] [" + name + "] " + str + "\n";
		write();
	};

	~Log(){
		file.close();
	};
};
