#include "Connection.h"

#include "Debug.h"

Connection::Connection(Pin* pin)
{
    m_state = false;
    m_inPin = nullptr;
    m_outPin = nullptr;
    SetFirstPin(pin);
}

Connection::~Connection()
{
    if (m_inPin != nullptr)
    {
        m_inPin->SetState(false);
        m_inPin->SetConnected(false);
    }
    
    if (m_outPin != nullptr)
    {
        m_outPin->SetState(false);
        m_outPin->SetConnected(false);
    }
}

json Connection::Save()
{
    json data;
    data["output"]["pinId"] = m_outPin->GetId();
    data["output"]["gateId"] = m_outPin->GetGateId();
    data["input"]["pinId"] = m_inPin->GetId();
    data["input"]["gateId"] = m_inPin->GetGateId();
    return data;
}

Pin* Connection::GetFirstPin()
{
    if (m_firstIn)
        return m_inPin;
    return m_outPin;
}

void Connection::SetFirstPin(Pin* pin)
{
    if (pin->IsInput())
    {
        SetInPin(pin);
        m_firstIn = true;
    }
    else
    {
        SetOutPin(pin);
        m_firstIn = false;
    }
}

void Connection::SetSecondPin(Pin* pin)
{
    if (pin->IsInput() && m_inPin == nullptr)
        SetInPin(pin);
    else if (!pin->IsInput() && m_outPin == nullptr)
        SetOutPin(pin);
}

Pin* Connection::GetInPin()
{
    return m_inPin;
}

void Connection::SetInPin(Pin* pin)
{
    m_inPin = pin;
    m_inPin->SetConnected(true);
}

Pin* Connection::GetOutPin()
{
    return m_outPin;
}

void Connection::SetOutPin(Pin* pin)
{
    m_outPin = pin;
    m_outPin->SetConnected(true);
}

void Connection::Update()
{
    if (!(m_outPin != nullptr && m_inPin != nullptr))
        return;

    m_state = m_outPin->GetState();
    m_inPin->SetState(m_state);
}

bool Connection::IsConnected()
{
    return m_outPin != nullptr;
}

void Connection::Draw(SDL_Renderer* renderer)
{
    if (m_state)
        m_color = 0xff00ff00;
    else
        m_color = 0xff000000;

    if (m_outPin == nullptr && m_inPin != nullptr)
        thickLineColor(renderer, m_inPin->GetX(), m_inPin->GetY(), MS::x, MS::y, 10, m_color);
    
    if (m_inPin == nullptr && m_outPin != nullptr)
        thickLineColor(renderer, m_outPin->GetX(), m_outPin->GetY(), MS::x, MS::y, 10, m_color);

    if (m_inPin != nullptr && m_outPin != nullptr)
        thickLineColor(renderer, m_inPin->GetX(), m_inPin->GetY(), m_outPin->GetX(), m_outPin->GetY(), 10, m_color); 

}