#pragma once

#include "../Core/imgui.h"

namespace RmUi::Utilities {
    class ColorHelpers
    {
    public:
        static bool IsLightColor(ImU32 color, float threshold = 0.5f);
    };
}

