// ProjektTP.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ProjektTP.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void PaintBackground(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255),10);
	graphics.DrawLine(&pen, 0, 450, 1500, 450);
}

void MyOnPaint(HDC hdc)
{
	Graphics lowerarm(hdc);
	Graphics upperarm(hdc);
	Pen pen(Color(255, 0, 0, 0), 5);
	lowerarm.DrawLine(&pen, xbl,ybl,xel,yel);
	upperarm.DrawLine(&pen, xbu, ybu, xeu, yeu);
}

void PaintSquares(HDC hdc)
{
	Graphics square1(hdc);
	Graphics square2(hdc);
	Graphics square3(hdc);
	Graphics square4(hdc);
	Graphics square5(hdc);
	Graphics square6(hdc);
	Pen pen(Color(255, 255, 0, 0), 5);
	square1.DrawRectangle(&pen, 800, 430, 20, 20);
	square2.DrawRectangle(&pen, 830, 430, 20, 20);
	square3.DrawRectangle(&pen, 860, 430, 20, 20);
	square4.DrawRectangle(&pen, 890, 430, 20, 20);
	square5.DrawRectangle(&pen, 920, 430, 20, 20);
	square6.DrawRectangle(&pen, 950, 430, 20, 20);
}

void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	PaintSquares(hdc);
	EndPaint(hWnd, &ps);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    GdiplusStartupInput gdiplusStartupInput;
	  ULONG_PTR           gdiplusToken;
	  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJEKTTP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJEKTTP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    GdiplusShutdown(gdiplusToken);
    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJEKTTP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJEKTTP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
    
   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Lower part up"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   100, 460,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON1,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Lower part down"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   100, 560,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON2,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Upper part up"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   250, 460,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON3,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Upper part down"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   250, 560,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON4,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Speed+"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   450, 460,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON5,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Speed-"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   450, 560,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON6,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Record Motion"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   650, 460,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON7,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Auto"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   650, 560,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON8,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Catch Object"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   850, 460,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON9,
	   hInstance,
	   NULL);

   g_hbutton = CreateWindow(TEXT("button"),
	   TEXT("Release Object"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   850, 560,
	   150, 100,
	   hWnd,
	   (HMENU)ID_BUTTON10,
	   hInstance,
	   NULL);	
	
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
	    PaintBackground(hdc);
	    PaintSquares(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
