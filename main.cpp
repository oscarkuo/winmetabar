#include "stdafx.h"
#include "event.h"
#include "image.h"

HBITMAP g_hbmpNumbers;

namespace
{
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        switch (message)
        {
        case WM_CREATE: 
            return OnCreate(hWnd, message, wParam, lParam);

        case WM_DESTROY:
            return OnDestroy(hWnd, message, wParam, lParam);

        case WM_HOTKEY:
            return OnHotKey(hWnd, message, wParam, lParam);

        case WM_SHOWWINDOW:
            return OnShowWindow(hWnd, message, wParam, lParam);

        case WM_TIMER:
            return OnTimer(hWnd, message, wParam, lParam);

        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    CoInitialize(NULL);

    const wchar_t szClassName[] = L"Win Meta Bar Class Name";
    const wchar_t szWindowName[] = L"Win Meta Bar Window Name";

    g_hbmpNumbers = LoadPngToHBITMAP(WMBAR_NUMBERIMAGE);

    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = szClassName;
    wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
    
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
        szClassName, szWindowName,
        WS_POPUP,
        0, 0, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_HIDE);
    UpdateWindow(hwnd);

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        if (msg.message == WM_QUIT) 
            break;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DeleteObject(g_hbmpNumbers);

    return 0;
}
