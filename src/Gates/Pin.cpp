#include "Pin.h"

#include "Debug.h"

int Pin::radius = 15;

Pin::Pin(int xPos, int yPos, int gateId, bool isInput, int id)
{
    m_id = id;
    m_gateId = gateId;
    
    m_state = false;
    m_hover = false;
    m_connected = false;

    m_xPos = xPos;
    m_yPos = yPos;

    m_isInput = isInput;
}

Pin::~Pin()
{

}

bool Pin::IsInput()
{
    return m_isInput;
}

void Pin::SetConnected(bool connected)
{
    m_connected = connected;
}

bool Pin::GetConnected()
{
    return m_connected;
}

int Pin::Radius()
{
    return radius;
}

bool Pin::GetState()
{
    return m_state;
}

void Pin::SetState(bool state)
{
    m_state = state && m_connected;
}

int Pin::GetId()
{
    return m_id;
}

int Pin::GetGateId()
{
    return m_gateId;
}

int Pin::GetX()
{
    return m_xPos;
}

int Pin::GetY()
{
    return m_yPos;
}

void Pin::Move(int xDiff, int yDiff)
{
    m_xPos += xDiff;
    m_yPos += yDiff;
}

bool Pin::Hover(int x, int y)
{
    m_hover = false;

    if (MyMath::Pow((x-m_xPos)) + MyMath::Pow((y-m_yPos)) < MyMath::Pow(radius))
        m_hover = true;

    return m_hover;
}

void Pin::Draw(SDL_Renderer* renderer)
{
    if (m_state)
        filledCircleColor(renderer, m_xPos, m_yPos, radius, 0xff00ff00);
    else
        filledCircleColor(renderer, m_xPos, m_yPos, radius, 0xff000000);

    if (m_hover)
        filledCircleColor(renderer, m_xPos, m_yPos, radius*0.75f, 0xffffffff);
}


