#pragma once

#include "Core/imgui.h"
#include "Core/Backends/imgui_impl_win32.h"
#include "Core/Backends/imgui_impl_dx11.h"
#include <d3d11.h>

namespace RmUi {
    class RmUi_SimpleWindow
    {
    private:
        // Helper functions
        bool CreateDeviceD3D(HWND hWnd);
        void CleanupDeviceD3D();
        void CreateRenderTarget();
        void CleanupRenderTarget();

    public:
        int Run(void(*fGUI)(), LPCTSTR title, int sizeX, int sizeY, int posX = 0, int posY = 0);

    private:
        ID3D11Device* g_pd3dDevice = nullptr;
        ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
        IDXGISwapChain* g_pSwapChain = nullptr;
        bool g_SwapChainOccluded = false;
        ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;
    };
}