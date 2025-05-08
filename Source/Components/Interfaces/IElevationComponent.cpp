#include "Components/Interfaces/IElevationComponent.hpp"

#include <Components/Card.hpp>
#include <Components/Button.hpp>

void RmUi::Components::Interfaces::IElevationComponent::ShowExample1()
{
    static RmUi::Components::Card card1{};
    static RmUi::Components::Card card2{};
    static bool init = false;
    if (!init)
    {
        card1.Name = "IElevationComponentExample1_TestComponent1";
        card1.Label = "Card";
        card1.Size = ImVec2(200, 80);
        card2.Name = "IElevationComponentExample1_TestComponent2";
        card2.Label = "Card";
        card2.Size = ImVec2(200, 80);
        card2.BackgroundColor = IM_COL32_WHITE;
        card2.ForegroundColor = IM_COL32_BLACK;

        init = true;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0xFF, 0xFF, 0xFF, 255));
    if (ImGui::Begin("IElevationComponentExample1 - Card"))
    {
        card1.Draw();

        ImGui::NewLine();
        ImGui::NewLine();

        card2.Draw();

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));

        if (ImGui::SliderFloat("HeightToShadow", &card1.ElevationHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            card2.ElevationHeightToShadowSizingScale_IElevationComponent = card1.ElevationHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("BaseHeightToShadow", &card1.ElevationBaseHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            card2.ElevationBaseHeightToShadowSizingScale_IElevationComponent = card1.ElevationBaseHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("ExtendedHeightToShadow", &card1.ElevationExtendedHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            card2.ElevationExtendedHeightToShadowSizingScale_IElevationComponent = card1.ElevationExtendedHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("ShadowSpreading", &card1.ElevationShadowSpreadingScale_IElevationComponent, 0, 50)) {
            card2.ElevationShadowSpreadingScale_IElevationComponent = card1.ElevationShadowSpreadingScale_IElevationComponent;
        }


        ImVec4 col = ImVec4(
            ((card1.ElevationShadowColor_IElevationComponent >> 0) & 0xFF) / 255.0f,  // R
            ((card1.ElevationShadowColor_IElevationComponent >> 8) & 0xFF) / 255.0f,  // G
            ((card1.ElevationShadowColor_IElevationComponent >> 16) & 0xFF) / 255.0f,  // B
            ((card1.ElevationShadowColor_IElevationComponent >> 24) & 0xFF) / 255.0f   // A
        );
        if (ImGui::ColorEdit4("ShadowColor", (float*)&col))
        {
            card1.ElevationShadowColor_IElevationComponent = IM_COL32(
                (int)(col.x * 255.0f + 0.5f),
                (int)(col.y * 255.0f + 0.5f),
                (int)(col.z * 255.0f + 0.5f),
                (int)(col.w * 255.0f + 0.5f)
            );

            card2.ElevationShadowColor_IElevationComponent = card1.ElevationShadowColor_IElevationComponent;
        }
        if (ImGui::SliderFloat("ShadowColorDepth", &card1.ElevationShadowColorDepth_IElevationComponent, 0, 10)) {
            card2.ElevationShadowColorDepth_IElevationComponent = card1.ElevationShadowColorDepth_IElevationComponent;
        }
        if (ImGui::SliderInt("ShadowQuality", &card1.ElevationShadowQuality_IElevationComponent, 0, 50)) {
            card2.ElevationShadowQuality_IElevationComponent = card1.ElevationShadowQuality_IElevationComponent;
        }

        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleColor();
}
void RmUi::Components::Interfaces::IElevationComponent::ShowExample2()
{
    static RmUi::Components::Button button1{};
    static RmUi::Components::Button button2{};
    static bool init = false;
    if (!init)
    {
        button1.Name = "IElevationComponentExample2_TestComponent1";
        button1.Label = "Button";
        button1.Size = ImVec2(200, 80);
        button2.Name = "IElevationComponentExample2_TestComponent2";
        button2.Label = "Button";
        button2.Size = ImVec2(200, 80);
        button2.BackgroundColor = IM_COL32_WHITE;
        button2.ForegroundColor = IM_COL32_BLACK;

        init = true;
    }

    ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(0xFF, 0xFF, 0xFF, 255));
    if (ImGui::Begin("IElevationComponentExample2 - Button"))
    {
        button1.Draw();

        ImGui::NewLine();
        ImGui::NewLine();

        button2.Draw();

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));

        if (ImGui::SliderFloat("HeightToShadow", &button1.ElevationHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            button2.ElevationHeightToShadowSizingScale_IElevationComponent = button1.ElevationHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("BaseHeightToShadow", &button1.ElevationBaseHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            button2.ElevationBaseHeightToShadowSizingScale_IElevationComponent = button1.ElevationBaseHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("ExtendedHeightToShadow", &button1.ElevationExtendedHeightToShadowSizingScale_IElevationComponent, 0, 10)) {
            button2.ElevationExtendedHeightToShadowSizingScale_IElevationComponent = button1.ElevationExtendedHeightToShadowSizingScale_IElevationComponent;
        }
        if (ImGui::SliderFloat("ShadowSpreading", &button1.ElevationShadowSpreadingScale_IElevationComponent, 0, 50)) {
            button2.ElevationShadowSpreadingScale_IElevationComponent = button1.ElevationShadowSpreadingScale_IElevationComponent;
        }


        ImVec4 col = ImVec4(
            ((button1.ElevationShadowColor_IElevationComponent >> 0) & 0xFF) / 255.0f,  // R
            ((button1.ElevationShadowColor_IElevationComponent >> 8) & 0xFF) / 255.0f,  // G
            ((button1.ElevationShadowColor_IElevationComponent >> 16) & 0xFF) / 255.0f,  // B
            ((button1.ElevationShadowColor_IElevationComponent >> 24) & 0xFF) / 255.0f   // A
        );
        if (ImGui::ColorEdit4("ShadowColor", (float*)&col))
        {
            button1.ElevationShadowColor_IElevationComponent = IM_COL32(
                (int)(col.x * 255.0f + 0.5f),
                (int)(col.y * 255.0f + 0.5f),
                (int)(col.z * 255.0f + 0.5f),
                (int)(col.w * 255.0f + 0.5f)
            );

            button2.ElevationShadowColor_IElevationComponent = button1.ElevationShadowColor_IElevationComponent;
        }
        if (ImGui::SliderFloat("ShadowColorDepth", &button1.ElevationShadowColorDepth_IElevationComponent, 0, 10)) {
            button2.ElevationShadowColorDepth_IElevationComponent = button1.ElevationShadowColorDepth_IElevationComponent;
        }
        if (ImGui::SliderInt("ShadowQuality", &button1.ElevationShadowQuality_IElevationComponent, 0, 50)) {
            button2.ElevationShadowQuality_IElevationComponent = button1.ElevationShadowQuality_IElevationComponent;
        }

        ImGui::PopStyleColor();
    }
    ImGui::End();
    ImGui::PopStyleColor();

}
