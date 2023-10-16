#include "Gate.h"

#include "Debug.h"


/****************************************************/
/*                        Gate                      */
/****************************************************/

int Gate::id = 0;


Gate::Gate(int xPos, int yPos, int nInputs, int nOutputs)
{
    m_id = ++id;

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

void Gate::CreatePins(int nInputs, int nOutputs)
{
    int offset = m_height/(nInputs*2);
    int currentOffset = offset;

    // Creating Inputs
    for (int i = 0; i < nInputs; i++)
    {
        m_inputs.push_back(new Pin(m_xPos, m_yPos+currentOffset, m_id, true));

        currentOffset += offset*2;
    }

    offset = m_height/(nOutputs*2);
    currentOffset = offset;

    // Creating Outputs
    for (int i = 0; i < nOutputs; i++)
    {
        m_outputs.push_back(new Pin(m_xPos+m_width, m_yPos+currentOffset, m_id, false));

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

Pin* Gate::GetSelectedPin(MouseState ms)
{
    for (auto& pin : m_inputs)
        if (pin->Hover(ms.x, ms.y) && ms.lBtnDown)
            return pin;

    for (auto& pin : m_outputs)
        if (pin->Hover(ms.x, ms.y) && ms.lBtnDown)
            return pin;

    return nullptr;
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
        conenctionHover = MyMath::Max(pin->Hover(x, y), conenctionHover);

    for (auto& pin: m_outputs)
        conenctionHover = MyMath::Max(pin->Hover(x, y), conenctionHover);

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

void Gate::Logic(MouseState ms)
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


/****************************************************/
/*                       AndGate                    */
/****************************************************/


AndGate::AndGate(int xPos, int yPos): 
    Gate(xPos, yPos, 2, 1) 
{
    m_color = { 92, 118, 105, 0 };
}

void AndGate::Logic(MouseState ms)
{
    m_outputs[0]->SetState(m_inputs[0]->GetState() && m_inputs[1]->GetState());
}

/****************************************************/
/*                       NotGate                    */
/****************************************************/


NotGate::NotGate(int xPos, int yPos): 
    Gate(xPos, yPos, 1, 1) 
{
    m_color = { 92, 118, 105, 0 };
}

void NotGate::Logic(MouseState ms)
{
    if (m_inputs[0]->GetConnected() && m_outputs[0]->GetConnected())
        m_outputs[0]->SetState(!m_inputs[0]->GetState());
}



/****************************************************/
/*                       Button                     */
/****************************************************/


Button::Button(int xPos, int yPos): 
    Gate(xPos, yPos, 0, 1) 
{
    m_color = { 92, 118, 105, 0 };
    m_btnX = m_rect.x + m_rect.w/2;
    m_btnY = m_rect.y + m_rect.h/2;
    m_btnR = m_rect.h/2*0.7f;
}

void Button::Logic(MouseState ms)
{
    m_hoverBtn = false;

    if (MyMath::Pow((ms.x-m_btnX)) + MyMath::Pow((ms.y-m_btnY)) < MyMath::Pow(m_btnR))
        m_hoverBtn = true;

    if (m_hoverBtn && ms.lBtnDown && !m_click)
    {
        m_outputs[0]->SetState(!m_outputs[0]->GetState());
        m_click = true;
    }
    
    if (!m_hoverBtn || !ms.lBtnDown)
        m_click = false;
}

void Button::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);

    m_btnX = m_rect.x + m_rect.h/2;
    m_btnY = m_rect.y + m_rect.h/2;
    
    if (m_click)
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xffffffff); 
    else if (m_hoverBtn)
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff888888);
    else
        filledCircleColor(renderer, m_btnX, m_btnY, m_btnR, 0xff000000);
}


/****************************************************/
/*                       Button                     */
/****************************************************/


Lamp::Lamp(int xPos, int yPos): 
    Gate(xPos, yPos, 1, 0) 
{
    m_color = { 92, 118, 105, 0 };
    m_lampX = m_rect.x + m_rect.h/2;
    m_lampY = m_rect.y + m_rect.h/2;
    m_lampR = m_rect.h/2*0.7f;
}

void Lamp::Logic(MouseState ms)
{
    m_state = false;
    if (m_inputs[0]->GetConnected())
        m_state = m_inputs[0]->GetState();
}

void Lamp::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);

    m_lampX = m_rect.x + m_rect.w/2;
    m_lampY = m_rect.y + m_rect.h/2;
    
    if (m_state)
        filledCircleColor(renderer, m_lampX, m_lampY, m_lampR, 0xff00ff00);
    else
        filledCircleColor(renderer, m_lampX, m_lampY, m_lampR, 0xff000000);
}