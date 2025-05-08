#pragma once
#include "../Core/imgui.h"
#include "../Core/imgui_internal.h"

#include "Card.hpp"

#include "Interfaces/IRippleComponent.hpp"

#include "../Primitives/MouseState.hpp"
#include "../Primitives/Ripple.hpp"
#include "../Primitives/InteractionState.hpp"

namespace RmUi::Components {
    class Button final : public Card {
    protected:
        virtual ImGuiMouseCursor GetDefault_CursorIcon() const override { return ImGuiMouseCursor_Hand; }

        virtual void _reset() override{
            Name = "";
            Label = "";
            Size = ImVec2(0.f, 0.f);
            BackgroundColor = 0x00;
            ForegroundColor = 0x00;
            CursorIcon = GetDefault_CursorIcon();
        }

    public:
        virtual ComponentType GetComponentType() const override { return ComponentType::Button; }

        Button() {
            _reset();

            Name = "Button";
            Label = "Button";

            Elevation_IElevationComponent.HeightRange = ImVec2(2.f,8.f);
            TimeOut_IRippleComponent = .95f;

            hoveredSurfaceElevation.Elevation_IElevationComponent.HeightRange = ImVec2{ 0.f, 1.f };
            hoveredSurfaceElevation.ElevationHeightToShadowSizingScale_IElevationComponent = 1.f;
            hoveredSurfaceElevation.ElevationBaseHeightToShadowSizingScale_IElevationComponent = 1.f;
            hoveredSurfaceElevation.ElevationExtendedHeightToShadowSizingScale_IElevationComponent = 0.f;
            hoveredSurfaceElevation.ElevationShadowSpreadingScale_IElevationComponent = 1.f;
            hoveredSurfaceElevation.ElevationShadowColor_IElevationComponent = IM_COL32(0, 0, 0, 0x30);
            hoveredSurfaceElevation.ElevationShadowColorDepth_IElevationComponent = 1.f;
            hoveredSurfaceElevation.ElevationShadowQuality_IElevationComponent = 1;
        }

        ~Button() override {
        }

    protected:
        virtual bool DrawInit(Primitives::DrawInfo** pDrInfo) override {
            
            // Execute base
            return Card::DrawInit(pDrInfo);
        }

        virtual void DrawUpdateInput(Primitives::DrawInfo* drInfo) override {
            
            // Execute base
            Card::DrawUpdateInput(drInfo);
        }

        virtual void DrawUpdate(Primitives::DrawInfo* drInfo) override {
            
            // Execute base
            Card::DrawUpdate(drInfo);
        }

        virtual void DrawRender(Primitives::DrawInfo* drInfo) override {
            
            // Execute base
            Card::DrawRender(drInfo);
        }

        virtual void DrawExternal(const Primitives::DrawInfo& drInfo) override {
            
            // Execute base
            Card::DrawExternal(drInfo);
        }

        virtual void DrawInternal(const Primitives::DrawInfo& drInfo) override {
            
            // Execute base
            Card::DrawInternal(drInfo);
        }

        virtual bool DrawFinish(const Primitives::DrawInfo& drInfo) override {
            
            // Execute base
            return Card::DrawFinish(drInfo);
        }

    };
}
