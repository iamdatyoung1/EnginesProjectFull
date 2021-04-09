#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include<string>
#include<fstream>

class Debug 
{
public:
	//Making sure enum varrible is the same size as an unsigned short which is 2 bytes
	enum class MessageType : unsigned short {
		// This specific order
		//if i change the value 0 to 1 it will change the values for the rest
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator = (const Debug&) = delete;
	Debug& operator = (Debug&&) = delete;
	// if nothing is called in the OnCreate then this message here will be called
	static void OnCreate(const std::string& name_ = "GAME258EngineLog");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	//writing to the file
	static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line);
	static MessageType currentSev;
	//This is the file name 
	static std::string outputName;

};
#endif
