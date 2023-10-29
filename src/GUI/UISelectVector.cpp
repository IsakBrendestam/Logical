#include "UISelectVector.h"

UISelectVector::UISelectVector(int x, int y, int w, int h, std::vector<std::string> options, int limit)
{
    int width = w*0.9;
    int height = 50;

    const int offset = h/10;

    int xPos = x + w/2 - width/2;
    int yPos = y + offset + height;

    for (int i = 0; i < options.size(); i++)
    {
        m_selects.push_back(new UISelect(xPos, yPos, width, height, options[i]));
        yPos += offset + height;
    }

    m_selectedIndex = -1;
}

UISelectVector::~UISelectVector()
{
    for (auto& sel : m_selects)    
        delete sel;
}

int UISelectVector::GetSelectedIndex()
{
    return m_selectedIndex;
}

std::string UISelectVector::GetValue(int index)
{
    if (index < 0 || index > m_selects.size())
        return "";

    return m_selects[index]->GetValue();
}

std::string UISelectVector::GetSelectedValue()
{
    return GetValue(m_selectedIndex);
}

void UISelectVector::Enable()
{
    for (auto& sel : m_selects)
        sel->Enable();
}

void UISelectVector::Disable()
{
    for (auto& sel : m_selects)
        sel->Disable();
}

void UISelectVector::Update()
{

    for (int i = 0; i < m_selects.size(); i++)
    {
        UISelect* currSel = m_selects[i];
        if (currSel->GetSelected() && m_selectedIndex != i)
        {
            if (m_selectedIndex != -1)
                m_selects[m_selectedIndex]->SetSelected(false);
            m_selectedIndex = i;
        }
        m_selects[i]->Update();
    }
}

void UISelectVector::Draw(SDL_Renderer* renderer)
{
    for (auto& sel : m_selects)
        sel->Draw(renderer);
}