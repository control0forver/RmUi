#pragma once

#include <vector>

namespace RmUi::Primitives
{
    struct MouseState
    {
        bool hovered = false;
        bool held = false;
        bool down = false;
        bool click = false;
    };
}