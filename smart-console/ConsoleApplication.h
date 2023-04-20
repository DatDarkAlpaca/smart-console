#pragma once
#include <stdio.h>
#include <string>
#include <unordered_map>

#include "WindowHeader.h"
#include "DataRead.h"
#include "IState.h"

#define STI_BUFFER_SIZE 255

namespace dat
{
    struct ConsoleApplication
    {
    public:
        ConsoleApplication() = delete;
        ConsoleApplication(const ConsoleApplication&) = delete;
        ConsoleApplication& operator()(ConsoleApplication&) = delete;

    public:
        static void initialize();

        static void run();

    private:
        static void onEvent();

    public:
        static void setState(const std::string& stateName);

        static void addState(const std::string& stateName, IState* state);

    public:
        static void writeConsole(const std::string& text);

        static DataRead<char*, DWORD> readConsole();

        static DataRead<INPUT_RECORD*, DWORD> readConsoleInput();

    private:
        static inline std::unordered_map<std::string, IState*> m_States = {};
        static inline IState* m_CurrentState = nullptr;

        static inline bool m_Running = false;
        static inline HANDLE m_HandleStdOut = nullptr, m_HandleStdIn = nullptr;
    };
}
