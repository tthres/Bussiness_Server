#pragma once
#include <pthread.h>
#include <string>
#include <CThread/Thread.h>

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
public:
    CLoggerServer();
    ~CLoggerServer();

    CLoggerServer(const CLoggerServer&)            = delete;
    CLoggerServer& operator=(const CLoggerServer&) = delete;

    //日志服务器的启动
    int Start();

    int Close();

private:
    int  ThreadFunc();
    void WriteLog(const std::string& data);

private:
    CThread      m_thread;
    CEpoll       m_epoll;
    CSocketBase* m_server;
    std::string  m_path;
    FILE*        m_file;
};