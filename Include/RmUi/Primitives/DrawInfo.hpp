#pragma once

#include <map>

#include "../Core/imgui.h"
#include "../Core/imgui_internal.h"

namespace RmUi::Primitives
{
    struct DrawInfo {
        ImGuiWindow* window;
        ImGuiContext* g;
        ImGuiStyle* style;
        ImGuiID id;
        ImVec2 label_size;

        ImVec2 pos;
        ImVec2 actual_size;

        ImRect bb;
    };
}
