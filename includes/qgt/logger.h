#ifndef QUANTUNGRAPHICSTOOLKIT_LOGGER_H
#define QUANTUNGRAPHICSTOOLKIT_LOGGER_H

#include <cstdio>
#include <string>
#include <ctime>

typedef enum LogLevel {
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG
} LogLevel;

static LogLevel level = DEBUG;

void setLogLevel(LogLevel newLevel) {
	level = newLevel;
}

void log(LogLevel l, const std::string& msg) {
	time_t t;
	time(&t);
	auto local = localtime(&t);
	std::string lvl;
	switch (l) {
		case FATAL:
			lvl = "FATAL]";
			break;
		case ERROR:
			lvl = "ERROR]";
			break;
		case WARN:
			lvl = "WARN] ";
			break;
		case INFO:
			lvl = "INFO] ";
			break;
		case DEBUG:
			lvl = "DEBUG]";
			break;
	}
	if (l <= level) {
		printf("[%02d:%02d:%02d] [%s %s\n", local->tm_hour, local->tm_min, local->tm_sec, lvl.c_str(), msg.c_str());
	}
}

#endif //QUANTUNGRAPHICSTOOLKIT_LOGGER_H
