#pragma once

#include "../Core/imgui.h"


namespace RmUi::Primitives
{
    class Elevation
    {
    public:
        ImVec2 HeightRange = ImVec2(0.f, 0.f); // Range of height for the elevation effect (min, max)
    };
}
