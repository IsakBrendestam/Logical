#include "InputHandler.h"

#include "Debug.h"

std::string InputHandler::m_inputText = "";

void InputHandler::Event(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_BACKSPACE && m_inputText.length() > 0)
                m_inputText.pop_back();
            else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & CPY_KEY)
                SDL_SetClipboardText(m_inputText.c_str());
            else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & CPY_KEY)
				m_inputText += SDL_GetClipboardText();

            break;

        case SDL_TEXTINPUT:
			if (!(SDL_GetModState() & CPY_KEY && 
                 (event.text.text[ 0 ] == 'c' || 
                  event.text.text[ 0 ] == 'C' || 
                  event.text.text[ 0 ] == 'v' || 
                  event.text.text[ 0 ] == 'V' )))
				m_inputText += event.text.text;

            break;
    }

    Log(m_inputText);
}

void InputHandler::Reset()
{
    m_inputText = "";
}

std::string InputHandler::GetInput()
{
    return m_inputText;
}