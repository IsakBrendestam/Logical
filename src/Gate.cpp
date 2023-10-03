#include "Gate.h"

#include <iostream>


/****************************************************/
/*                        Gate                      */
/****************************************************/


Gate::Gate(int xPos, int yPos, int nInputs, int nOutputs)
{
    m_moving = false;

    m_xPos = xPos;
    m_yPos = yPos;

    int maxConenctions = MyMath::Max(nInputs, nOutputs);

    m_height = Connection::Radius()*(maxConenctions*2 + 2);
    m_width = m_height*1.5;

    CreateConnections(nInputs, nOutputs);

    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
    m_rect.w = m_width;
    m_rect.h = m_height;

    m_color = { 52, 78, 65, 0 };

}

void Gate::CreateConnections(int nInputs, int nOutputs)
{
    int offset = m_height/(nInputs*2);
    int currentOffset = offset;

    for (int i = 0; i < nInputs; i++)
    {
        m_inputs.push_back(new Connection(m_xPos, m_yPos+currentOffset));

        currentOffset += offset*2;
    }

    offset = m_height/(nOutputs*2);
    currentOffset = offset;
    for (int i = 0; i < nOutputs; i++)
    {
        m_outputs.push_back(new Connection(m_xPos+m_width, m_yPos+currentOffset));

        currentOffset += offset*2;
    }
}

int Gate::GetXPos()
{
    return m_xPos;
}

int Gate::GetYPos()
{
    return m_yPos;
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

    m_xPos = m_offsetX + x;
    m_yPos = m_offsetY + y;
    UpdateRect();

    for (auto& connection: m_inputs)
        connection->Move(m_xPos-oldX, m_yPos-oldY);

    for (auto& connection: m_outputs)
        connection->Move(m_xPos-oldX, m_yPos-oldY);
}

bool Gate::Hover(int x, int y)
{
    for (auto& connection: m_inputs)
        connection->Hover(x, y);

    for (auto& connection: m_outputs)
        connection->Hover(x, y);


    if (x > m_rect.x && x < m_rect.x + m_rect.w &&
        y > m_rect.y && y < m_rect.y + m_rect.h)
        return true;
    return false;
}

void Gate::UpdateRect()
{
    m_rect.x = m_xPos;
    m_rect.y = m_yPos;
}

void Gate::Logic()
{

}

void Gate::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, m_color.r, m_color.g, m_color.b, m_color.a);
    SDL_RenderFillRect(renderer, &m_rect);

    for (auto& connection: m_inputs)
        connection->Draw(renderer);

    for (auto& connection: m_outputs)
        connection->Draw(renderer);
}


/****************************************************/
/*                       AndGate                    */
/****************************************************/


AndGate::AndGate(int xPos, int yPos): 
    Gate(xPos, yPos, 2, 1) 
{
    m_color = { 92, 118, 105, 0 };
}

void AndGate::Logic()
{
    m_outputs[0]->SetState(m_inputs[0]->GetState() && m_inputs[0]->GetState());
}