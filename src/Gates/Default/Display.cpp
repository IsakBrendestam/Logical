#include "Display.h"

#include "Debug.h"

Display::Display(int xPos, int yPos): 
    Gate(xPos, yPos, 4, 0, "DISPLAY") 
{
    m_segmentOffColor = {191, 191, 191, 255};
    m_segmentOnColor = {225, 48, 35, 255};

    SetPositions();

    m_value = -1;

    for (int i = 0; i < m_nSegments; i++)
        m_segmentStates[i] = false;

}

void Display::Logic(double deltaTime)
{

    m_value = 0;
    
    if (m_inputs[0]->GetState())
        m_value += 1;
    if (m_inputs[1]->GetState())
        m_value += 2;
    if (m_inputs[2]->GetState())
        m_value += 4;
    if (m_inputs[3]->GetState())
        m_value += 8;

    if (!m_inputs[0]->GetConnected() && 
        !m_inputs[1]->GetConnected() && 
        !m_inputs[2]->GetConnected() && 
        !m_inputs[3]->GetConnected())
        m_value = -1;

    m_segmentStates[0] = m_value != -1 && (m_value != 1 && m_value != 4);
    m_segmentStates[1] = m_value != -1 && (m_value != 5 && m_value != 6);
    m_segmentStates[2] = m_value != -1 && (m_value != 2);
    m_segmentStates[3] = m_value != -1 && (m_value != 1 && m_value != 4 && m_value != 7);
    m_segmentStates[4] = m_value != -1 && (m_value == 0 || m_value == 2 || m_value == 6 || m_value == 8);
    m_segmentStates[5] = m_value != -1 && (m_value != 1 && m_value != 2 && m_value != 3 && m_value != 7);
    m_segmentStates[6] = m_value != -1 && (m_value != 0 && m_value != 1 && m_value != 7);
}

void Display::SetPositions()
{
    const int xOffset = 50;
    const int yOffset = 20;
    const int segmentW = m_rect.w / 12;
    const int segmentH = m_rect.h / 4;
    const int segmentOffset = 10;

    m_segments[0] = {m_rect.x + segmentW + xOffset + segmentOffset, m_rect.y + yOffset, segmentH, segmentW};

    m_segments[1] = {m_rect.x + segmentH + segmentW + xOffset + 2*segmentOffset, m_rect.y + yOffset + segmentOffset, segmentW, segmentH};

    m_segments[2] = {m_rect.x + segmentH + segmentW + xOffset + 2*segmentOffset, m_rect.y + segmentH + yOffset + 2*segmentOffset, segmentW, segmentH};

    m_segments[3] = {m_rect.x + segmentW + xOffset + segmentOffset, m_rect.y + 2*segmentH + yOffset + 2*segmentOffset, segmentH, segmentW};

    m_segments[4] = {m_rect.x + xOffset, m_rect.y + segmentH + yOffset + 2*segmentOffset, segmentW, segmentH};

    m_segments[5] = {m_rect.x + xOffset, m_rect.y + yOffset + segmentOffset, segmentW, segmentH};

    m_segments[6] = {m_rect.x + segmentW + xOffset + segmentOffset, m_rect.y + segmentH + yOffset + segmentOffset, segmentH, segmentW};
}

void Display::Draw(SDL_Renderer* renderer)
{
    Gate::Draw(renderer);
    SetPositions();

    for (int i = 0; i < m_nSegments; i++)
    {
        if (m_segmentStates[i])
            SDL_SetRenderDrawColor(renderer, m_segmentOnColor.r, m_segmentOnColor.g, m_segmentOnColor.b, m_segmentOnColor.a);
        else
            SDL_SetRenderDrawColor(renderer, m_segmentOffColor.r, m_segmentOffColor.g, m_segmentOffColor.b, m_segmentOffColor.a);
        SDL_RenderFillRect(renderer, &m_segments[i]);
    }
}