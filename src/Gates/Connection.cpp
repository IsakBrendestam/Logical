#include "Connection.h"

#include "Debug.h"

Connection::Connection(Pin* pin1)
{
    m_state = false;
    SetPin1(pin1);
    m_pin2 = nullptr;
}

Pin* Connection::GetPin1()
{
    return m_pin1;
}

void Connection::SetPin1(Pin* pin)
{
    m_pin1 = pin;
    m_pin1->SetConnected(true);
}

Pin* Connection::GetPin2()
{
    return m_pin2;
}

void Connection::SetPin2(Pin* pin)
{
    m_pin2 = pin;
    m_pin2->SetConnected(true);
}

void Connection::Update()
{
    m_state = m_pin1->GetState();
    if (m_pin2 != nullptr)
        m_pin2->SetState(m_state);
}

bool Connection::IsConnected()
{
    return m_pin2 != nullptr;
}

void Connection::Draw(SDL_Renderer* renderer)
{
    if (m_pin1 == nullptr)
        return;

    if (m_state)
        m_color = 0xff00ff00;
    else
        m_color = 0xff000000;

    if (m_pin2 == nullptr)
        thickLineColor(renderer, m_pin1->GetX(), m_pin1->GetY(), MS::x, MS::y, 10, m_color);

    if (m_pin1 != nullptr && m_pin2 != nullptr)
        thickLineColor(renderer, m_pin1->GetX(), m_pin1->GetY(), m_pin2->GetX(), m_pin2->GetY(), 10, m_color); 

}