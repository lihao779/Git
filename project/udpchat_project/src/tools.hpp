#pragma once
#include <string.h>
#include <time.h>
#include <iostream>
#include <string>

class TimeStamp
{
    public:
        static void GetTimeStamp(std::string& timeStamp)
        {
            time_t sys_time;
            time(&sys_time);
            //struct tm *localtime(const time_t *timep)
            struct tm* t = localtime(&sys_time);
            //yyyy-mm-dd hh:mm:ss;
            char buf[30] = {0};
            snprintf(buf, sizeof(buf) - 1,"%04d-%02d-%2d %02d:%02d:%02d",
                    t->tm_year + 1900,t->tm_mon + 1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
            timeStamp.assign(buf,strlen(buf));

        }
};



enum LogLevel
{
    INFO = 0,
    WARNING,
    ERROR,
    FATAL,
    DEBUG
};
const char* LevelInfo[] = 
{
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
    "DEBUG"
};


std::ostream& Log(LogLevel log,const char* file,int line,const std::string& msg)
{
    std::string timeStamp;
    TimeStamp::GetTimeStamp(timeStamp);
    std::cout << "[" << timeStamp << " " << LevelInfo[log] << " " << file << ":" << line << "]  " << msg << std::endl;
    return std::cout;
}

#define LOG(log,msg) Log(log,__FILE__,__LINE__,msg)
