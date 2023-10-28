#pragma once

class System
{
public:
    static void ShutDown();
    static bool IsRunning();

private:
    static bool m_running;
};