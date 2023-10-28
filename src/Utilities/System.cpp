#include "System.h"

bool System::m_running = true;

void System::ShutDown()
{
    m_running = false;
}

bool System::IsRunning()
{
    return m_running;
}