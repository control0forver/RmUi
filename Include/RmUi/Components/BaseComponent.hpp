#pragma once

#include "../Infrastructure/IClassStructor.hpp"

#include "../Core/imgui.h"
#include "../Core/imgui_internal.h"

#include "../Primitives/DrawInfo.hpp"
#include "../Primitives/MouseState.hpp"
#include "../Primitives/InteractionState.hpp"

#include <cmath>
#include <vector>
#include <memory>
#include <string>

namespace RmUi::Components
{
    enum class ComponentType {
        BaseComponent = 0,
        Card,
        Button
    };

    class BaseComponent : public Infrastructure::IClassStructor
    {
    public:
        std::string Name;
        std::string Label;
        ImVec2 Size;
        ImU32 BackgroundColor;
        ImU32 ForegroundColor;

        ImGuiMouseCursor CursorIcon;

    public:
        virtual ~BaseComponent() {};

        virtual ComponentType GetComponentType() const = 0;
        
    protected:
        Primitives::MouseState state{};

    protected:
        virtual bool DrawInit(Primitives::DrawInfo **pDrInfo)
        {
            ImGuiWindow *window = ImGui::GetCurrentWindow();
            if (window->SkipItems)
                return false;

            ImGuiContext &g = *GImGui;
            ImGuiStyle &style = g.Style;
            ImGuiID id = window->GetID(Name.c_str());
            ImVec2 label_size = ImGui::CalcTextSize(Label.c_str(), NULL, true);

            ImVec2 pos = window->DC.CursorPos;
            ImVec2 actual_size = ImGui::CalcItemSize(Size, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

            ImRect bb(pos, pos + actual_size);
            ImGui::ItemSize(bb, style.FramePadding.y);
            if (!ImGui::ItemAdd(bb, id))
                return false;

            // Set up draw info
            *pDrInfo = new Primitives::DrawInfo{
                window,
                &g,
                &style,
                id,
                label_size,
                pos,
                actual_size,
                bb};

            return true;
        }

        virtual void DrawUpdateInput(Primitives::DrawInfo *drInfo)
        {
            // Update button state
            bool hovered, held;
            bool down, click;

            // TO_BE_FIXED: multiple ImGui::ButtonBehavior calls with the same ID doses not work as expected and causes #8030
            /*if (drInfo->g->IO.ConfigDebugHighlightIdConflicts)
                drInfo->g->IO.ConfigDebugHighlightIdConflicts = false;*/

            down = ImGui::ButtonBehavior(drInfo->bb, drInfo->id, &hovered, &held, ImGuiButtonFlags_PressedOnClick);
            click = state.held && !held && hovered;

            state.hovered = hovered;
            state.held = held;
            state.down = down;
            state.click = click;

            if (hovered)
            {
                ImGui::SetMouseCursor(CursorIcon);
            }
        }

        virtual void DrawUpdate(Primitives::DrawInfo *drInfo)
        {
        }

        ImU32 _bg_color = 0;
        ImU32 _text_color = 0;
        virtual void DrawRender(Primitives::DrawInfo *drInfo)
        {
            _bg_color = BackgroundColor;
            _text_color = ForegroundColor;
        }

        virtual void DrawExternal(const Primitives::DrawInfo &drInfo)
        {
            // Draw button background
            drInfo.window->DrawList->AddRectFilled(drInfo.bb.Min, drInfo.bb.Max, _bg_color, drInfo.style->FrameRounding);

            // Draw border
            drInfo.window->DrawList->AddRect(drInfo.bb.Min, drInfo.bb.Max, IM_COL32(0x25, 0x25, 0x25, 30), drInfo.style->FrameRounding); // TODO: Fix: border not showing?
        }

        virtual void DrawInternal(const Primitives::DrawInfo &drInfo)
        {
            // Draw label
            ImGui::PushStyleColor(ImGuiCol_Text, _text_color);
            {
                ImGui::RenderTextClipped(drInfo.bb.Min + drInfo.style->FramePadding, drInfo.bb.Max - drInfo.style->FramePadding,
                                         Label.c_str(), NULL, &drInfo.label_size, ImVec2(0.5f, 0.5f), &drInfo.bb);
            }
            ImGui::PopStyleColor();
        }

        virtual bool DrawFinish(const Primitives::DrawInfo &drInfo)
        {
            return state.click;
        }

    public:
        bool Draw()
        {
            Primitives::DrawInfo *_drInfo = nullptr;
            if (!DrawInit(&_drInfo))
                return false;

            std::unique_ptr<Primitives::DrawInfo> drInfo = std::unique_ptr<Primitives::DrawInfo>(_drInfo);

            DrawUpdateInput(drInfo.get());
            DrawUpdate(drInfo.get());

            DrawRender(drInfo.get());

            DrawExternal(*drInfo);

            ImGui::PushClipRect(drInfo->bb.Min, drInfo->bb.Max, false);
            {
                DrawInternal(*drInfo);
            }
            ImGui::PopClipRect();

            return DrawFinish(*drInfo);
        }

    protected:
        virtual decltype(CursorIcon) GetDefault_CursorIcon() const { return ImGuiMouseCursor_Arrow; }
    };
}
