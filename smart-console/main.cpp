#include "ConsoleApplication.h"

using namespace dat;

struct OnlyPositiveIntegers final : public dat::IState
{
public:
    void onStateEntered() override
    {
        
    }

    void onKeyPressEvent(KEY_EVENT_RECORD record) override
    {
        char inputChar = record.uChar.AsciiChar;

        // ASCII:
        // 0: 48
        // 1: 49
        // ...

        if (inputChar <= 57 && inputChar > 48 && record.bKeyDown)
            ConsoleApplication::writeConsole(std::string(1, inputChar));
    };
};

int main(void)
{
    ConsoleApplication::initialize();
    ConsoleApplication::addState("example_state", new OnlyPositiveIntegers());

    ConsoleApplication::writeConsole("This console only allows for positive integers.\n");
    ConsoleApplication::run();
}