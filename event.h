#pragma once

#include "stdafx.h"

LRESULT OnTimer(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT OnCreate(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT OnHotKey(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT OnDestroy(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT OnShowWindow(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT OnSystemTrayIcon(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);