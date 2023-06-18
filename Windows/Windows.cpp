// Windows.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Windows.h"

#include <windows.h>
#include <ctime>
#include <cstdio>
#include <string>
#include <chrono>

HWND hwndEdit;

LRESULT CALLBACK winpro1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        // Crea un control de texto (edit control) para mostrar el tiempo
        hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL, WS_CHILD | WS_VISIBLE | ES_READONLY,
            18, 10, 250, 30, hwnd, NULL, NULL, NULL);


        SetTimer(hwnd, 1, 1000, NULL);
        break;
    }
    case WM_TIMER:
        if (wParam == 1) {
            // Obtiene el tiempo actual
            auto now = std::chrono::system_clock::now();
            auto now_t = std::chrono::system_clock::to_time_t(now);

            // Convierte el tiempo en una cadena de caracteres
            char timeString[26];
            ctime_s(timeString, sizeof(timeString), &now_t);
            timeString[24] = '\0'; // Elimina el carácter de nueva línea al final

            // Actualiza el texto del control de texto con el tiempo actual
            SetWindowTextA(hwndEdit, timeString);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        KillTimer(hwnd, 1); // Detiene el temporizador
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain( _In_ HINSTANCE h, _In_ HINSTANCE ph, LPSTR LineCmd, int ShowCmd) {

    const wchar_t* className = L"MyWindowClass";
    const wchar_t* windowTitle = L"Reloj";

    WNDCLASS wc = { 0 };
    wc.hInstance = h;
    wc.lpszClassName = className;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = winpro1;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        className,
        windowTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        300,
        150,
        NULL,
        NULL,
        h,
        NULL);

    MSG msg;

    ShowWindow(hwnd, ShowCmd);
    UpdateWindow(hwnd);

    while (TRUE == GetMessage(&msg, NULL, 0, 0) > 0) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return (int)msg.wParam;



}
