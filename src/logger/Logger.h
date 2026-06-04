#pragma once
#include <pthread.h>
#include <string>

enum LogLevel
{
    LOG_INFO,
    LOG_DEBUG,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
};

class LogInfo
{
public:
    LogInfo(const char* file, int line, const char* func, pid_t pid, pthread_t tid, int level, const char* fmt, ...);
    LogInfo(const char* file, int line, const char* func, pid_t pid, pthread_t tid, int level);

    LogInfo(const char* file, int line, const char* func, pid_t pid, pthread_t tid, int level, void* pData, size_t nSize);

    ~LogInfo();

    operator std::string() const { return m_buf; }

private:
    bool        bAuto; //默认是false 流式日志，则为true
    std::string m_buf;
};

class CLoggerServer
{
};