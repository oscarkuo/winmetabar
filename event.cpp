#include "event.h"

extern HBITMAP g_hbmpNumbers;

namespace
{
    enum
    {
        ID_TIMERHIDEWINDOW,
        ID_HOTKEYLWIN = 100,
    };


    void RenderImage(HWND hwnd, HBITMAP hbmp)
    {
        BITMAP bm;
        GetObject(hbmp, sizeof(bm), &bm);
        SIZE sizeSplash = { bm.bmWidth, bm.bmHeight };

        // get the primary monitor's info
        POINT ptZero = { 0 };

        HDC hdcScreen = GetDC(hwnd);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);

        BLENDFUNCTION blend = { 0 };
        blend.BlendOp = AC_SRC_OVER;
        blend.SourceConstantAlpha = 255;
        blend.AlphaFormat = AC_SRC_ALPHA;

        HBITMAP hdcOldBmp = (HBITMAP)SelectObject(hdcMem, hbmp);

        UpdateLayeredWindow(
            hwnd, hdcScreen, NULL, &sizeSplash,
            hdcMem, &ptZero, RGB(0, 0, 0), &blend, ULW_ALPHA);

        SelectObject(hdcMem, hdcOldBmp);

        // delete temporary objects
        DeleteDC(hdcMem);
        ReleaseDC(hwnd, hdcScreen);
    }
}


LRESULT OnTimer(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    auto winKeyState = GetKeyState(VK_LWIN) & 0x8000;
    if (!winKeyState) {
        ShowWindow(hwnd, SW_HIDE);
    }
    return 0;
}


LRESULT OnCreate(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    RegisterHotKey(hwnd, ID_HOTKEYLWIN, MOD_WIN, VK_LWIN);
    RenderImage(hwnd, g_hbmpNumbers);
    return 0;
}


LRESULT OnHotKey(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    POINT ptZero = { 0 };
    HMONITOR hmonPrimary = MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi = { 0 };
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hmonPrimary, &mi);
    SetWindowPos(hwnd, NULL, WMBAR_LEFTMARGIN, mi.rcWork.bottom - 50, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    return 0;
}


LRESULT OnDestroy(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UnregisterHotKey(hwnd, ID_HOTKEYLWIN);
    PostQuitMessage(0);
    return 0;
}


LRESULT OnShowWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // start the hide window timer when the windows is shown and kiil it when not
    if (wParam) {
        SetTimer(hwnd, ID_TIMERHIDEWINDOW, 100, NULL);
    }
    else {
        KillTimer(hwnd, ID_TIMERHIDEWINDOW);
    }

    return 0;
}


LRESULT OnSystemTrayIcon(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return 0;
}

