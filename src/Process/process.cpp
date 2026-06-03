#include "process.h"

CProcess::CProcess() : m_func(nullptr)
{
    memset(pipes, 0, sizeof(pipes));
}

CProcess::~CProcess()
{
    if (m_func != nullptr)
    {
        delete m_func;
        m_func = nullptr;
    }
}

int CProcess::CreateSubProcess()
{
    if (m_func == nullptr)
        return -1;

    int ret = socketpair(AF_LOCAL, SOCK_STREAM, 0, pipes);
    if (ret == -1)
        return -2;

    pid_t pid = fork();

    if (pid == -1)
        return -3;

    if (pid == 0)
    {
        // 子进程
        close(pipes[1]);
        pipes[1] = 0;
        ret      = (*m_func)();
        exit(0);
    }
    // 父进程
    close(pipes[0]);
    pipes[0] = 0;
    m_pid    = pid;
    return 0;
}
