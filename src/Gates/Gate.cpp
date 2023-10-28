#include "Gate.h"

#include "Debug.h"

int Gate::ID;

Gate::Gate(int xPos, int yPos, int nInputs, int nOutputs, std::string type, int id)
{
    if (id == -1)
        m_id = ++ID;
    else
        m_id = id;

    m_type = type;

    m_moving = false;

    m_xPos = xPos;
    m_yPos = yPos;

    int maxConenctions = MyMath::Max(nInputs, nOutputs);

    m_height = Pin::Radius()*(maxConenctions*2 + 2);
    m_width = m_height*1.5;

    m_xPos -= m_width/2;
    m_yPos -= m_height/2;

    CreatePins(nInputs, nOutputs);

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = m_width;
    m_rect.h = m_height;

    m_color = { 52, 78, 65, 0 };
}

Gate::~Gate()
{
    for (auto& pin: m_inputs)
        delete pin;

    for (auto& pin: m_outputs)
        delete pin;
}

json Gate::Save()
{
    json data;

    data["id"] = m_id;
    data["xPos"] = m_xPos+m_width/2;
    data["yPos"] = m_yPos+m_height/2;
    data["nInpits"] = m_inputs.size();
    data["nOutputs"] = m_outputs.size();
    data["type"] = m_type;

    for (int i = 0; i < m_inputs.size(); i++)
        data["inPinIDs"][i] = m_inputs[i]->GetId();

    for (int i = 0; i < m_outputs.size(); i++)
        data["outPinIDs"][i] = m_outputs[i]->GetId();

    return data;
}

void Gate::CreatePins(int nInputs, int nOutputs)
{
    int offset = m_height/(nInputs*2);
    int currentOffset = offset;

    // Creating Inputs
    for (int i = 0; i < nInputs; i++)
    {
        m_inputs.push_back(new Pin(m_xPos, m_yPos+currentOffset, m_id, true, i));

        currentOffset += offset*2;
    }

    offset = m_height/(nOutputs*2);
    currentOffset = offset;

    // Creating Outputs
    for (int i = 0; i < nOutputs; i++)
    {
        m_outputs.push_back(new Pin(m_xPos+m_width, m_yPos+currentOffset, m_id, false, i));

        currentOffset += offset*2;
    }
}

Pin* Gate::GetInputPin(int index)
{
    if (index < m_inputs.size())
        return m_inputs[index];
    return nullptr;
}

Pin* Gate::GetOutputPin(int index)
{
    if (index < m_outputs.size())
        return m_outputs[index];
    return nullptr;
}

Pin* Gate::GetSelectedPin()
{
    for (auto& pin : m_inputs)
        if (pin->Hover(MS::x, MS::y) && MS::lBtnDown)
            return pin;

    for (auto& pin : m_outputs)
        if (pin->Hover(MS::x, MS::y) && MS::lBtnDown)
            return pin;

    return nullptr;
}

std::vector<Pin*> Gate::GetInputPins()
{
    return m_inputs;
}

std::vector<Pin*> Gate::GetOutputPins()
{
    return m_outputs;
}

int Gate::GetXPos()
{
    return m_xPos;
}

int Gate::GetYPos()
{
    return m_yPos;
}

int Gate::GetId()
{
    return m_id;
}

void Gate::Select(int x, int y)
{
    m_offsetX = m_xPos - x;
    m_offsetY = m_yPos - y;
}

void Gate::Move(int x, int y)
{
    int oldX = m_xPos;
    int oldY = m_yPos;

    // Move gate
    m_xPos = m_offsetX + x;
    m_yPos = m_offsetY + y;
    UpdateRect();

    // Move inputs
    for (auto& pin: m_inputs)
        pin->Move(m_xPos-oldX, m_yPos-oldY);

    // Move outputs
    for (auto& pin: m_outputs)
        pin->Move(m_xPos-oldX, m_yPos-oldY);
}

bool Gate::Hover(int x, int y)
{
    bool conenctionHover = false;

    for (auto& pin: m_inputs)
        conenctionHover = pin->Hover(x, y) || conenctionHover;

    for (auto& pin: m_outputs)
        conenctionHover = pin->Hover(x, y) || conenctionHover;

    // Only hover gate if not hovering a pin
    if (x > m_xPos && x < m_xPos + m_width &&
        y > m_yPos && y < m_yPos + m_height &&
        !conenctionHover)
        return true;
    return false;
}

void Gate::UpdateRect()
{
    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
}

void Gate::Logic(double deltaTime)
{

}

void Gate::Draw(SDL_Renderer* renderer)
{
    // Draw gate rect
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);

    // Draw inputs
    for (auto& pin: m_inputs)
        pin->Draw(renderer);

    // Draw outputs
    for (auto& pin: m_outputs)
        pin->Draw(renderer);
}
