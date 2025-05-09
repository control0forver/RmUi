# RmUi

RmUi 是一个用于构建用户界面的库，支持多种组件和功能，并且使用 [Dear ImGui](https://github.com/ocornut/imgui) 作为基础。

## 使用方法

### 下载 RmUi 以及安装依赖

1. 前往 [RmUi Releases 页面](https://github.com/control0forver/RmUi/releases) 下载最新版本的构建文件。
2. 根据需要选择以下 RmUi 库文件：
   - 二进制库：
     - `Debug_Win32.zip`
     - `Release_Win32.zip`
     - `Debug_x64.zip`
     - `Release_x64.zip`
   - 头文件：
     - `Include.zip`
3. [安装 DirectX SDK](https://learn.microsoft.com/windows/win32/directx-sdk--august-2009-)。

### 配置项目

1. 解压下载的文件。
2. 将 `Include` 文件夹添加到项目的包含路径中。
3. 根据目标平台和配置（Debug/Release, Win32/x64），将对应的 `RmUi.lib` 库文件添加到链接器输入中。
4. 确保链接库目录中包含 DirectX 库。
5. 使用 C++ 20 或更高版本的编译器。

### 示例代码

以下是一个简单的示例，展示如何使用 RmUi 创建一个按钮：

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

## 构建

如果需要自行构建 RmUi，可以使用以下步骤：

1. 确保已安装以下工具：
   - Visual Studio 2022 或更高版本
   - MSBuild 17.0 或更高版本
   - DirectX SDK (June 2010) 或更高版本
2. 克隆项目代码：
   ```bash
   git clone https://github.com/control0forver/RmUi.git
   ```
3. 进入目录并使用以下命令构建所有配置：
   ```powershell
   cd RmUi

   msbuild RmUi.vcxproj /p:Configuration=Debug /p:Platform=Win32
   msbuild RmUi.vcxproj /p:Configuration=Release /p:Platform=Win32
   msbuild RmUi.vcxproj /p:Configuration=Debug /p:Platform=x64
   msbuild RmUi.vcxproj /p:Configuration=Release /p:Platform=x64
   ```

## 发布

每次推送版本标签（如 `v1.0.0`）时，GitHub Actions 会自动构建并发布以下内容：

- 二进制库：
  - Debug | Win32: `Debug_Win32.zip`
  - Release | Win32: `Release_Win32.zip`
  - Debug | x64: `Debug_x64.zip`
  - Release | x64: `Release_x64.zip`
- 头文件：
  - `Include.zip`

详情请参阅 [GitHub Actions Workflow](.github/workflows/Build_Release_on_version_tag_pushed.yml)。

## README.md
 - [English](README.md)
 - 简体中文