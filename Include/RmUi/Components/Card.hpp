#pragma once
#include "../Core/imgui.h"
#include "../Core/imgui_internal.h"

#include "BaseComponent.hpp"

#include "Interfaces/IRippleComponent.hpp"
#include "Interfaces/IElevationComponent.hpp"

#include "../Primitives/MouseState.hpp"
#include "../Primitives/Ripple.hpp"
#include "../Primitives/InteractionState.hpp"

#include "../Utilities/ColorHelpers.h"
#include <iostream>

namespace RmUi::Components {
    class Card : public BaseComponent, public Interfaces::IRippleComponent, public Interfaces::IElevationComponent {
    protected:
        virtual void _reset() override{
            Name = "";
            Label = "";
            Size = ImVec2(0.f, 0.f);
            BackgroundColor = 0x00;
            ForegroundColor = 0x00;
            CursorIcon = GetDefault_CursorIcon();
        }

        IElevationComponent hoveredSurfaceElevation{};
    public:
        virtual ComponentType GetComponentType() const override { return ComponentType::Card; }

        Card() {
            _reset();

            Name = "Card";
            Label = "Card";

            Elevation_IElevationComponent.HeightRange = ImVec2(1.f,8.f);
            TimeOut_IRippleComponent = .8f;
        }

        ~Card() override {
        }

    protected:
        virtual bool DrawInit(Primitives::DrawInfo** pDrInfo) override {
            
            // Execute base
            return BaseComponent::DrawInit(pDrInfo);
        }

        virtual void DrawUpdateInput(Primitives::DrawInfo* drInfo) override {
            
            // Execute base
            BaseComponent::DrawUpdateInput(drInfo);
        }

        virtual void DrawUpdate(Primitives::DrawInfo* drInfo) override {
            // Add ripple effect on mouse down
            if (state.down) {
                ImVec2 mouse_pos_in_bb = ImGui::GetMousePos() - drInfo->bb.Min;
                AddRipple_IRippleComponent(Utilities::ColorHelpers::IsLightColor(BackgroundColor)? IRippleComponent::CreateRipple_IRippleComponent_Black_global(mouse_pos_in_bb, drInfo->actual_size) : IRippleComponent::CreateRipple_IRippleComponent_White_global(mouse_pos_in_bb, drInfo->actual_size));
            }

            // Update ripple effect
            Update_IRippleComponent(drInfo->g->IO.DeltaTime, state.held ? RmUi::Primitives::InteractionState::Start : RmUi::Primitives::InteractionState::End);

            // Update elevation effect
            auto ais = Primitives::AdvancedInteractionState::None;
            if (state.hovered) ais |= Primitives::AdvancedInteractionState::Hovered;
            if (state.held) ais |= Primitives::AdvancedInteractionState::Hold;
            Update_IElevationComponent(drInfo->g->IO.DeltaTime, ais);

            // Execute base
            BaseComponent::DrawUpdate(drInfo);
        }

        virtual void DrawRender(Primitives::DrawInfo* drInfo) override {

            // Execute base
            BaseComponent::DrawRender(drInfo);
        }

        virtual void DrawExternal(const Primitives::DrawInfo& drInfo) override {
            // Draw elevation effect (from IElevationComponent)
            Draw_IElevationComponent(drInfo.window->DrawList, drInfo.bb.Min, drInfo.actual_size);
            
            // Execute base
            BaseComponent::DrawExternal(drInfo);

        }

        virtual void DrawInternal(const Primitives::DrawInfo& drInfo) override {
            
            // Execute base
            BaseComponent::DrawInternal(drInfo);

            // Draw ripple effect (from IRippleComponent)
            Draw_IRippleComponent(drInfo.window->DrawList, drInfo.bb.Min);
        }

        virtual bool DrawFinish(const Primitives::DrawInfo& drInfo) override {

            // Execute base
            return BaseComponent::DrawFinish(drInfo);
        }

    };
}
