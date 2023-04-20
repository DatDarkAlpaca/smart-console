#pragma once
#include "WindowHeader.h"

namespace dat
{
    void KeyEventProc(KEY_EVENT_RECORD ker)
    {
        if (ker.bKeyDown)
            printf("key pressed\n");

        else 
            printf("key released\n");
    }
}