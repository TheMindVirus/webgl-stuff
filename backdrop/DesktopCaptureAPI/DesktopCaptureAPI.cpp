#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#define SIZE_OF                 sizeof
#define MAX_STR                 255

#define IDR_APP_TITLE			103
#define IDR_MAINFRAME			128

#define IDI_APP_ICON            107
#define IDI_SMALL_ICON			108

#define IDC_APP_CLASS         	109
#define IDC_ICON_CLASS			2

HINSTANCE szhInstance;
WCHAR szTitle[MAX_STR];
WCHAR szWindowClass[MAX_STR];
BOOL szRunning;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, INT);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ INT nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDR_APP_TITLE, szTitle, MAX_STR);
    LoadStringW(hInstance, IDC_APP_CLASS, szWindowClass, MAX_STR);
    MyRegisterClass(hInstance);
    if (!InitInstance (hInstance, nCmdShow)) { return FALSE; }

    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            GetMessage(&msg, NULL, 0, 0);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        InvalidateRect(msg.hwnd, NULL, FALSE);
        if (!szRunning) { ExitProcess(0); }
    }
    return (INT)(msg.wParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = SIZE_OF(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = NULL;
    wcex.cbWndExtra     = NULL;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(COLOR_BACKGROUND);
    wcex.lpszMenuName   = NULL; //MAKEINTRESOURCEW(IDC_APP_CLASS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL_ICON));
    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, INT nCmdShow)
{
    szRunning = TRUE;
    szhInstance = hInstance;
    HWND hWnd = CreateWindowEx(WS_EX_LAYERED, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL, NULL, NULL, hInstance, NULL);
    SetLayeredWindowAttributes(hWnd, COLOR_BACKGROUND, 0, LWA_COLORKEY);
    GetWindowModuleFileName(hWnd, szTitle, MAX_STR);
    PathStripPathW(szTitle);
    PathRemoveExtension(szTitle);
    SetWindowText(hWnd, szTitle);
    if (!hWnd) { return FALSE; }
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case (WM_PAINT):
        {
            PAINTSTRUCT ps;
            HWND hDesktop = GetWindow(hWnd, GW_HWNDLAST);
            HDC hdc = BeginPaint(hWnd, &ps);
            HDC hdcScreen = GetDC(NULL);
            HDC hdcWindow = GetWindowDC(hWnd);
            HDC hdcDesktop = GetWindowDC(hDesktop);

            //Override WM_PAINT with bitmap
            
            //Get the framebuffer dimensions
            RECT source;
            RECT viewport;
            GetClientRect(hDesktop, &source);
            GetClientRect(hWnd, &viewport);
            LONG source_width = source.right - source.left;
            LONG source_height = source.bottom - source.top;
            LONG viewport_width = viewport.right - viewport.left;
            LONG viewport_height = viewport.bottom - viewport.top;

            //Perform scaling on the context
            SetStretchBltMode(hdc, HALFTONE);
            SetStretchBltMode(hdcDesktop, HALFTONE);
            StretchBlt(hdc, 0, 0, viewport_width, viewport_height, hdcDesktop, 0, 0, source_width, source_height, SRCCOPY);
            
            //Avoid memory leaks
            DeleteObject(hdcDesktop);
            DeleteObject(hdcWindow);
            DeleteObject(hdcScreen);

            //STREAM
            /*
            //Set up display contexts
            HDC desktopDC = GetDC(NULL);
            HDC streamDC = CreateCompatibleDC(desktopDC);
            HBITMAP streamBMP = CreateCompatibleBitmap(desktopDC, bmpInfo.biWidth, bmpInfo.biHeight);
            SelectObject(streamDC, streamBMP);
            SetStretchBltMode(desktopDC, HALFTONE);
            SetStretchBltMode(streamDC, HALFTONE);

            //Allocate space for stream buffer
            DWORD dwBmpSize = bmpInfo.biWidth * bmpInfo.biHeight * 4; //((bmpInfo.biWidth * bmpInfo.biBitCount + 31) / 32) * 4 * bmpInfo.biHeight;
            HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
            LPCSTR buffer = (hDIB) ? (LPCSTR)GlobalLock(hDIB) :  "";
            
            //Set up receiver display context
            HDC stream2DC = CreateCompatibleDC(desktopDC);
            HBITMAP stream2BMP = CreateCompatibleBitmap(desktopDC, bmpInfo.biWidth, bmpInfo.biHeight);
            SelectObject(stream2DC, stream2BMP);
            
            StretchBlt(streamDC, 0, 0, width, height, desktopDC, 0, 0, width, height, SRCCOPY);
            GetDIBits(streamDC, streamBMP, 0, bmpInfo.biHeight, (LPVOID)buffer, (LPBITMAPINFO)&bmpInfo, DIB_RGB_COLORS);
            */

            //TETRIS
            /*
            HDC hdcMem = CreateCompatibleDC(hdc);
            HBITMAP bmp = CreateCompatibleBitmap(hdc, width, height);
            SelectObject(hdcMem, bmp);

            SetBkColor(hdcMem, display.back);
            SetTextColor(hdcMem, display.text);

            display.backBrush = CreateSolidBrush(display.back);
            FillRect(hdcMem, &display.clientArea, display.backBrush);
            //DrawTextA(hdcMem, display.title, (int)strlen(display.title), &display.titleArea, DT_LEFT);
            //DrawTextA(hdcMem, display.score, (int)strlen(display.score), &display.scoreArea, DT_LEFT);
            DeleteObject(display.backBrush);

            for (LONG y = 0; y < DISPLAY_HEIGHT; ++y)
            {
                for (LONG x = 0; x < DISPLAY_WIDTH; ++x)
                {
                    display.pixelArea.left = (x * 40) + 5;
                    display.pixelArea.top = (y * 40) + 35;
                    display.pixelArea.right = display.pixelArea.left + 30;
                    display.pixelArea.bottom = display.pixelArea.top + 30;
                    display.pixelBrush = CreateSolidBrush(display.grid[x][y]);
                    FillRect(hdcMem, &display.pixelArea, display.pixelBrush);
                    DeleteObject(display.pixelBrush);
                }
            }

            BitBlt(hdc, 0, 0,
                display.clientArea.right - display.clientArea.left,
                display.clientArea.bottom - display.clientArea.top,
                hdcMem, 0, 0, SRCCOPY);
            DeleteDC(hdcMem);
            DeleteObject(bmp);
            */
            EndPaint(hWnd, &ps);
        }
        break;
        case (WM_MOUSEMOVE):
        {
            //OutputDebugString(L"Something");
            //InvalidateRect(hWnd, NULL, FALSE);
        }
        break;
        case (WM_DESTROY):
        {
            PostQuitMessage(0);
            szRunning = FALSE;
        }
        break;
        default:
        {
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    return 0;
}