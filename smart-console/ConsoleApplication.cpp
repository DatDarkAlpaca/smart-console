#include "ConsoleApplication.h"
#include "EventCallbacks.h"

namespace dat
{
    void ConsoleApplication::initialize()
    {
        m_HandleStdIn = GetStdHandle(STD_INPUT_HANDLE);
        m_HandleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

        if (m_HandleStdIn == INVALID_HANDLE_VALUE || m_HandleStdOut == INVALID_HANDLE_VALUE)
        {
            MessageBox(NULL, TEXT("GetStdHandle"), TEXT("Console Error"), MB_OK);
            return;
        }

        DWORD mode = ENABLE_WINDOW_INPUT;
        if (!SetConsoleMode(m_HandleStdIn, mode))
            return;

        m_Running = true;
    }

    void ConsoleApplication::run()
    {
        while (m_Running)
        {
            onEvent();
        }
    }

    void ConsoleApplication::writeConsole(const std::string& text)
    {
        DWORD cWritten;
        LPCSTR prompt = (LPCSTR)text.c_str();

        if (!WriteFile(m_HandleStdOut, prompt, lstrlenA(prompt), &cWritten, NULL))
            MessageBox(NULL, TEXT("WriteFile"), TEXT("Console Error"), MB_OK);
    }

    DataRead<char*, DWORD> ConsoleApplication::readConsole()
    {
        CHAR chBuffer[STI_BUFFER_SIZE];
        DWORD cRead;

        if (ReadFile(m_HandleStdIn, chBuffer, STI_BUFFER_SIZE, &cRead, NULL))
            return { chBuffer, cRead };
    }

    DataRead<INPUT_RECORD*, DWORD> ConsoleApplication::readConsoleInput()
    {
        INPUT_RECORD inputBuffer[STI_BUFFER_SIZE];
        DWORD cRead;

        if (ReadConsoleInput(m_HandleStdIn, inputBuffer, STI_BUFFER_SIZE, &cRead))
            return { inputBuffer, cRead };
    }

    void ConsoleApplication::onEvent()
    {
        auto [inputRecord, size] = readConsoleInput();

        for (DWORD i = 0; i < size; ++i)
        {
            switch (inputRecord[i].EventType)
            {
                case KEY_EVENT:
                    m_CurrentState->onKeyPressEvent(inputRecord[i].Event.KeyEvent);
                    break;

                case MOUSE_EVENT:
                    m_CurrentState->onMousePressEvent(inputRecord[i].Event.MouseEvent);
                    break;

                default:
                    break;
            }
        }
    }

    void ConsoleApplication::setState(const std::string& stateName)
    {
        if(m_CurrentState)
            m_CurrentState->onStateEntered();

        m_CurrentState = m_States[stateName];
    }

    void ConsoleApplication::addState(const std::string& stateName, IState* state)
    {
        m_States[stateName] = state;

        if(!m_CurrentState)
            setState(stateName);
    }
}
