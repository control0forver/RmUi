# RmUi

RmUi is a library designed for building user interfaces, leveraging the power of [Dear ImGui](https://github.com/ocornut/imgui) as its foundation. It provides a variety of components and utilities to simplify UI development.

## Getting Started

### Download RmUi and Dependencies

1. Visit the [RmUi Releases page](https://github.com/control0forver/RmUi/releases) to download the latest build.
2. Choose the appropriate RmUi files for your needs:
   - Binary libraries:
     - `Debug_Win32.zip`
     - `Release_Win32.zip`
     - `Debug_x64.zip`
     - `Release_x64.zip`
   - Header files:
     - `Include.zip`
3. Install the [DirectX SDK](https://learn.microsoft.com/windows/win32/directx-sdk--august-2009-).

### Configure Your Project

1. Extract the downloaded files.
2. Add the `Include` folder to your project's include paths.
3. Link the appropriate `RmUi.lib` file based on your target platform and configuration (Debug/Release, Win32/x64).
4. Make sure the DirectX library directory is included in your linker settings.
5. Use a C++ compiler that supports C++ 20 or later.

### Example Code

Here is a simple example demonstrating how to use RmUi to create a button:

```cpp
// Use RmUi
#include <RmUi/RmUi.h>
#include <RmUi/Utilities/ColorHelpers.h>

// Pick up the RmUi components
#include <RmUi/Components/Card.hpp>
#include <RmUi/Components/Button.hpp>

// Standard library
#include <iostream> // For output
#include <vector> // For std::vector
#include <format> // For formatting
#include <memory> // For smart pointers
#include <tchar.h> // For TCHAR

bool DrawComponent(RmUi::Components::BaseComponent* component);

RmUi::RmUi_SimpleWindow window{};
std::vector<std::unique_ptr<RmUi::Components::BaseComponent>> UiComponents{};
static void InitUi() {
    auto createButton = [](const char* name, ImU32 bgColor) {
        auto btn = std::make_unique<RmUi::Components::Button>();
        btn->Size = ImVec2(90, 35);
        btn->Name = name;
        btn->Label = "Remove";
        btn->BackgroundColor = bgColor;
        btn->ForegroundColor = RmUi::Utilities::ColorHelpers::IsLightColor(bgColor) ? IM_COL32_BLACK : IM_COL32_WHITE;
        return btn;
        };

    UiComponents.push_back(createButton("1", IM_COL32(0, 0, 0, 255)));
    UiComponents.push_back(createButton("2", IM_COL32(255, 255, 255, 255)));
    UiComponents.push_back(createButton("3", IM_COL32(0x24, 0x24, 0x24, 255)));
    UiComponents.push_back(createButton("4", IM_COL32(0xAA, 0xAA, 0xAA, 255)));
    UiComponents.push_back(createButton("5", IM_COL32(33, 150, 243, 255)));
    UiComponents.push_back(createButton("6", IM_COL32(255, 235, 59, 255)));
}

static void DrawGUI() {
    for (auto it = UiComponents.begin(); it != UiComponents.end();) {
        bool clicked = DrawComponent(&(**it));
        ImGui::NewLine();

        if (clicked)
            it = UiComponents.erase(it); // Delete on Click
        else
            it++;
    }
}

int main() {
    InitUi();
    
    auto uiExitCode = window.Run(DrawGUI, _T("RmUi Example"), 800, 600);

    std::cout << std::format("RmUi exit with code {}", uiExitCode) << std::endl;

    return 0;
}

bool DrawComponent(RmUi::Components::BaseComponent* component) {
    switch (component->GetComponentType())
    {
    case  RmUi::Components::ComponentType::BaseComponent:
        return false;
    case  RmUi::Components::ComponentType::Card:
        return dynamic_cast<RmUi::Components::Card*>(component)->Draw();
    case  RmUi::Components::ComponentType::Button:
        return dynamic_cast<RmUi::Components::Button*>(component)->Draw();

    default: return false;
    }
}
```

## Building RmUi

If you prefer to build RmUi yourself, follow these steps:

1. Ensure the following tools are installed:
   - Visual Studio 2022 or later
   - MSBuild 17.0 or later
   - DirectX SDK (June 2010) or later
2. Clone the repository:
   ```bash
   git clone https://github.com/control0forver/RmUi.git
   ```
3. Navigate to the directory and build all configurations:
   ```powershell
   cd RmUi

   msbuild RmUi.vcxproj /p:Configuration=Debug /p:Platform=Win32
   msbuild RmUi.vcxproj /p:Configuration=Release /p:Platform=Win32
   msbuild RmUi.vcxproj /p:Configuration=Debug /p:Platform=x64
   msbuild RmUi.vcxproj /p:Configuration=Release /p:Platform=x64
   ```

## Releases

With every version tag (e.g., `v1.0.0`) pushed to the repository, GitHub Actions automatically builds and publishes the following:

- Binary libraries:
  - Debug | Win32: `Debug_Win32.zip`
  - Release | Win32: `Release_Win32.zip`
  - Debug | x64: `Debug_x64.zip`
  - Release | x64: `Release_x64.zip`
- Header files:
  - `Include.zip`

For more details, refer to the [GitHub Actions Workflow](.github/workflows/Build_Release_on_version_tag_pushed.yml).

## README.md
 - English
 - [简体中文](README.zh-CN.md)