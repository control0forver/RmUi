#pragma once

#include "../../Core/imgui.h"
#include "../../Core/imgui_internal.h"

#include "../../Primitives/Ripple.hpp"
#include "../../Primitives/InteractionState.hpp"

namespace RmUi::Components::Interfaces {
    namespace IRippleComponentInternal {
        struct RipplePresentationInfo_IRippleComponent_Struct
        {
            float elapsed_start_interaction = 0.0f;
            float elapsed_end_interaction = 0.0f;
            const inline static float duration_start_interaction = 0.4f;
            const inline static float duration_end_interaction = 0.75f;
            bool locked_in_end_interaction = false;
            float progress_expected_percent_when_end_interaction = 0.6f;
        };

        class RippleWithRPIWrapper_IRippleComponent_Struct : public RipplePresentationInfo_IRippleComponent_Struct
        {
        public:
            Primitives::Ripple Ripple;

        public:
            RippleWithRPIWrapper_IRippleComponent_Struct(const Primitives::Ripple& ripple) : Ripple(ripple) {}
        };
    }

    /// <summary>
    /// Interface Info:
    /// Methods: Update_IRippleComponent, Draw_IRippleComponent, DrawRipple_IRippleComponent, AddRipple_IRippleComponent, ClearRipples_IRippleComponent
    /// Properties: TimeOut_IRippleComponent
    /// </summary>
    class IRippleComponent
    {
    public:
        float TimeOut_IRippleComponent = -1.f; // Time to force complete animation after start interaction finished, -1 to disable, in seconds

    public:
        virtual ~IRippleComponent() = default;

    protected:
        std::vector<IRippleComponentInternal::RippleWithRPIWrapper_IRippleComponent_Struct> _ripples_IRippleComponent_internal{};

    public:
        virtual void Update_IRippleComponent(float deltaTime, Primitives::InteractionState state) {
            for (auto it = _ripples_IRippleComponent_internal.begin(); it != _ripples_IRippleComponent_internal.end();) {
                if (!UpdateRipple_IRippleComponent_internal(&(*it),state,deltaTime))
                    it = _ripples_IRippleComponent_internal.erase(it); // Remove completed ripple
                else
                    ++it;
            }
        }

        virtual void Draw_IRippleComponent(
            ImDrawList* draw_list,
            const ImVec2& pos
        ) {
            for (const auto& ripple : _ripples_IRippleComponent_internal) {
                DrawRipple_IRippleComponent(draw_list, pos, ripple.Ripple);
            }
        }

        virtual void DrawRipple_IRippleComponent(
            ImDrawList* draw_list,
            const ImVec2& pos,
            const ImVec2& center,
            ImU32 color,
            float size,
            float percent,
            float alpha = 1.f
        ) {
            if (percent <= 0.f || alpha <= 0.f)
                return;

            ImU32 ripple_color = IM_COL32(
                IM_COL32_R(color),
                IM_COL32_G(color),
                IM_COL32_B(color),
                (int)(IM_COL32_A(color) * alpha)
            );
            float radius = ImLerp(0.f, size, percent);

            draw_list->AddCircleFilled(pos + center, radius, ripple_color);
        }

        virtual void DrawRipple_IRippleComponent(
            ImDrawList* draw_list,
            const ImVec2& pos,
            const Primitives::Ripple& ripple
        ) {
            DrawRipple_IRippleComponent(draw_list, pos, ripple.Center, ripple.Color, ripple.Size, ripple.Percent, ripple.Alpha);
        }

        virtual void AddRipple_IRippleComponent(const Primitives::Ripple& ripple) {
            _ripples_IRippleComponent_internal.push_back(IRippleComponentInternal::RippleWithRPIWrapper_IRippleComponent_Struct(ripple));
        }

        virtual void ClearRipples_IRippleComponent() {
            _ripples_IRippleComponent_internal.clear();
        }

    protected:
        /// <summary>
        /// Update ripple animation
        /// </summary>
        /// <param name="ripple">Ripple to update</param>
        /// <param name="state">Interaction state</param>
        /// <param name="deltaTime">Time since last frame, in seconds</param>
        /// <returns>true if animation is still in progress, false if animation is complete</returns>
        virtual bool UpdateRipple_IRippleComponent_internal(IRippleComponentInternal::RippleWithRPIWrapper_IRippleComponent_Struct* ripple, Primitives::InteractionState state, float deltaTime) {
            start:
                float progress_start_interaction = ImMin(ripple->elapsed_start_interaction / ripple->duration_start_interaction, 1.f);
                float easedProgress_start_interaction = SinInOut(progress_start_interaction);
    
                float progress_end_interaction = ImMin(ripple->elapsed_end_interaction / ripple->duration_end_interaction, 1.f);
                float easedProgress_end_interaction = SinInOut(progress_end_interaction);
    
                if (state == Primitives::InteractionState::Start && !ripple->locked_in_end_interaction) {
                    ripple->Ripple.Percent = ImLerp(0.0f, 1.0f, easedProgress_start_interaction);
                    ripple->Ripple.Alpha = ImLerp(0.3f, 1.0f, easedProgress_start_interaction);
    
                    ripple->elapsed_start_interaction += deltaTime;
    
                    if ((TimeOut_IRippleComponent != -1 && progress_start_interaction >= 1.0f) &&
                    ripple->elapsed_start_interaction - ripple->duration_start_interaction >= TimeOut_IRippleComponent) {
                        state = Primitives::InteractionState::End;
                        goto start;
                    }
                }
                else { // InteractionState::End
                    if (!ripple->locked_in_end_interaction)
                        ripple->locked_in_end_interaction = true; // prevents another start interaction
    
                    if (progress_start_interaction < ripple->progress_expected_percent_when_end_interaction) { // continue to animate start interaction
                        ripple->Ripple.Percent = ImLerp(0.0f, 1.0f, easedProgress_start_interaction);
                        ripple->elapsed_start_interaction += deltaTime;
                    }
    
                    ripple->Ripple.Alpha = ImLerp(1.0f, 0.0f, easedProgress_end_interaction);
    
                    if (progress_end_interaction >= 1.0f) {
                        return false; // Animation complete
                    }
    
                    ripple->elapsed_end_interaction += deltaTime;
                }
    
                return true; // Animation still in progress
            }

        private:
            // Easing functions
            float SinInOut(float t) { return 0.5f * (1.0f - std::cos(t * 3.14159265358979323846f)); }

        public:
            static inline float GetRippleSize_IRippleComponent_global(const ImVec2& lastTouchPoint, const ImVec2& elementSize)
            {
                ImVec2 points[4];
                points[0].x = points[2].x = lastTouchPoint.x;
                points[0].y = points[1].y = lastTouchPoint.y;
                points[1].x = points[3].x = lastTouchPoint.x - (float)elementSize.x;
                points[2].y = points[3].y = lastTouchPoint.y - (float)elementSize.y;
                auto maxSize = 0.f;
                for (const auto& point : points)
                {
                    auto size = std::pow(
                        std::pow(point.x - lastTouchPoint.x, 2.f)
                        + std::pow(point.y - lastTouchPoint.y, 2.f),
                        0.5f
                    );
                    if (size > maxSize)
                    {
                        maxSize = size;
                    }
                }
                return maxSize;
            }

            static inline Primitives::Ripple CreateRipple_IRippleComponent_global(const ImVec2& lastTouchPoint, const ImVec2& elementSize, ImU32 color)
            {
                return Primitives::Ripple(
                    color,
                    GetRippleSize_IRippleComponent_global(lastTouchPoint, elementSize),
                    0.f,
                    0.f,
                    lastTouchPoint
                );
            }

            static inline Primitives::Ripple CreateRipple_IRippleComponent_White_global(const ImVec2& lastTouchPoint, const ImVec2& elementSize)
            {
                return CreateRipple_IRippleComponent_global(lastTouchPoint, elementSize, IM_COL32(0xee, 0xee, 0xee, 0x30));
            }

            static inline Primitives::Ripple CreateRipple_IRippleComponent_Black_global(const ImVec2& lastTouchPoint, const ImVec2& elementSize)
            {
                return CreateRipple_IRippleComponent_global(lastTouchPoint, elementSize, IM_COL32(0x20, 0x20, 0x20, 0x30));
            }
    };
}