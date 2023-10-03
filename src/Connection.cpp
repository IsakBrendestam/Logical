#include "Connection.h"

int Connection::id;
int Connection::radius = 15;

Connection::Connection(int xPos, int yPos)
{
    m_id = ++id;
    m_state = false;
    m_hover = false;

    m_xPos = xPos;
    m_yPos = yPos;
}

int Connection::Radius()
{
    return radius;
}

bool Connection::GetState()
{
    return m_state;
}

void Connection::SetState(bool state)
{
    m_state = state;
}

int Connection::GetId()
{
    return m_id;
}

void Connection::Move(int xDiff, int yDiff)
{
    m_xPos += xDiff;
    m_yPos += yDiff;
}

bool Connection::Hover(int x, int y)
{
    m_hover = false;

    if ((x-m_xPos)^2 + (y-m_yPos)^2 < radius^2)
        m_hover = true;

    return m_hover;
}

void Connection::Draw(SDL_Renderer* renderer)
{
    filledCircleColor(renderer, m_xPos, m_yPos, radius, 0xff000000);
    if (m_hover)
        filledCircleColor(renderer, m_xPos, m_yPos, radius*0.75f, 0xffffffff);
}


