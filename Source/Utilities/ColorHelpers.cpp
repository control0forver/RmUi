#include "Utilities/ColorHelpers.h"

bool RmUi::Utilities::ColorHelpers::IsLightColor(ImU32 c, float t)
{
    ImVec4 color = ImGui::ColorConvertU32ToFloat4(c);

    // ITU-R BT.601
    float luminance = 0.299f * color.x + 0.587f * color.y + 0.114f * color.z;

    return luminance > t;
}
