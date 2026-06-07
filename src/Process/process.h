#pragma once
#include <functional>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <memory>
#include "Function/Function.h"

// 进程管理类，用来创建进程，并设置进程入口函数
class CProcess
{
public:
    CProcess();
    ~CProcess();
    template<typename _FUNCTION_, typename... _ARGS_>
    int SetEntryFunction(_FUNCTION_ func, _ARGS_... args)
    {
        m_func = new CFunction<_FUNCTION_, _ARGS_...>(func, args...);
        return 0;
    }

    int CreateSubProcess();

private:
    CFunctionBase* m_func;
    pid_t          m_pid;
    int            pipes[2];
};