#pragma once

#include "../Core/imgui.h"

#include "../Primitives/InteractionState.hpp"

namespace RmUi::Primitives
{
    class Ripple
    {
    public:
        ImU32 Color;
        float Size;
        float Percent;
        float Alpha;

        ImVec2 Center{};

    public:
        Ripple(ImU32 color, float size, float percent, float alpha, ImVec2 center)
            : Color(color), Size(size), Percent(percent), Alpha(alpha), Center(center) {
        }
        Ripple() : Color(0), Size(0), Percent(0), Alpha(0), Center(ImVec2(0, 0)) {}
    };
}
