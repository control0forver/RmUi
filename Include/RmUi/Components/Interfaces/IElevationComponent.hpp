#pragma once

#include "../../Core/imgui.h"
#include "../../Core/imgui_internal.h"

#include "../../Primitives/Elevation.hpp"
#include "../../Primitives/InteractionState.hpp"

namespace RmUi::Components::Interfaces {

    /// <summary>
    /// Interface Info:
    /// Methods: Update_IElevationComponent, Draw_IElevationComponent
    /// Properties: Elevation_IElevationComponent, ElevationHeightToShadowSizingScale_IElevationComponent, ElevationBaseHeightToShadowSizingScale_IElevationComponent, ElevationExtendedHeightToShadowSizingScale_IElevationComponent, ElevationShadowSpreadingScale_IElevationComponent, ElevationShadowColor_IElevationComponent, ElevationShadowColorDepth_IElevationComponent, ElevationShadowQuality_IElevationComponent
    /// </summary>
    class IElevationComponent
    {
    public:
        Primitives::Elevation Elevation_IElevationComponent{};
        float ElevationHeightToShadowSizingScale_IElevationComponent = 0.700f;
        float ElevationBaseHeightToShadowSizingScale_IElevationComponent = 0.250f;
        float ElevationExtendedHeightToShadowSizingScale_IElevationComponent = 0.150f;
        float ElevationShadowSpreadingScale_IElevationComponent = 15.000f;
        ImU32 ElevationShadowColor_IElevationComponent = IM_COL32(0, 0, 0, 145);
        float ElevationShadowColorDepth_IElevationComponent = 0.300f;
        int ElevationShadowQuality_IElevationComponent = 10;
        /*float ElevationHeightToShadowSizingScale_IElevationComponent = 0.700f;
        float ElevationBaseHeightToShadowSizingScale_IElevationComponent = 0.250f;
        float ElevationExtendedHeightToShadowSizingScale_IElevationComponent = 0.100f;
        float ElevationShadowSpreadingScale_IElevationComponent = 15.000f;
        ImU32 ElevationShadowColor_IElevationComponent = IM_COL32(0, 0, 0, 255);
        float ElevationShadowColorDepth_IElevationComponent = 0.350f;
        int ElevationShadowQuality_IElevationComponent = 10;*/

    public:
        virtual ~IElevationComponent() = default;

    protected:
        float _elevation_height_IElevationComponent_internal = 0.0f;

    public:
        virtual void Update_IElevationComponent(
                   float deltaTime,
                   Primitives::AdvancedInteractionState state
               ) {
                   float target_elevation_height = (state & Primitives::AdvancedInteractionState::Hold) != Primitives::AdvancedInteractionState::None ? Elevation_IElevationComponent.HeightRange.y
                       : (state & Primitives::AdvancedInteractionState::Hovered) != Primitives::AdvancedInteractionState::None ? (Elevation_IElevationComponent.HeightRange.y - Elevation_IElevationComponent.HeightRange.x) / 2 : Elevation_IElevationComponent.HeightRange.x;

                   auto SinInOut = [](float t) {
                       return 0.5f * (1.0f - cosf(t * IM_PI));
                   };

                   float t = deltaTime * 12.0f;
                   t = t > 1.0f ? 1.0f : t; // Clamp t to [0, 1]
                   _elevation_height_IElevationComponent_internal = ImLerp(_elevation_height_IElevationComponent_internal, target_elevation_height, SinInOut(t));
               }

        virtual void Draw_IElevationComponent(
            ImDrawList* drawList,
            const ImVec2& pos,
            const ImVec2& elementSize,
            float shadowRounding = 0.25f
        ) {
            if (_elevation_height_IElevationComponent_internal <= 0.f)
                return;

            float shadow_size = (Elevation_IElevationComponent.HeightRange.x * ElevationBaseHeightToShadowSizingScale_IElevationComponent + _elevation_height_IElevationComponent_internal * ElevationExtendedHeightToShadowSizingScale_IElevationComponent + shadowRounding * shadowRounding) * ElevationHeightToShadowSizingScale_IElevationComponent;
            const ImVec2 shadow_offset(0, shadow_size);

            for (int i = 0; i < ElevationShadowQuality_IElevationComponent; ++i) {
                float step_factor = (float)(ElevationShadowQuality_IElevationComponent - i) / ElevationShadowQuality_IElevationComponent;
                ImU32 shadow_color = IM_COL32(
                    IM_COL32_R(ElevationShadowColor_IElevationComponent),
                    IM_COL32_G(ElevationShadowColor_IElevationComponent),
                    IM_COL32_B(ElevationShadowColor_IElevationComponent),
                    (int)(IM_COL32_A(ElevationShadowColor_IElevationComponent) * step_factor * (shadow_size / Elevation_IElevationComponent.HeightRange.y) * ElevationShadowColorDepth_IElevationComponent*i)
                );
                float step_size = shadow_size * step_factor * ElevationShadowSpreadingScale_IElevationComponent;


                drawList->AddRectFilled(
                    pos + shadow_offset - ImVec2(step_size * 0.5f, step_size * 0.5f),
                    pos + shadow_offset + elementSize + ImVec2(step_size * 0.5f, step_size * 0.5f),
                    shadow_color
                    , step_size * shadowRounding
                    , ImDrawFlags_RoundCornersAll
                );
            }
        }

    public:
        static void ShowExample1();
        static void ShowExample2();
    };
}