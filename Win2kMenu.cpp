// Win2kMenu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win2kMenu.h"
#include <olectl.h>
#include <ole2.h>
#include <stdio.h>
#include <shellapi.h>
#include <shlobj.h>
#include <stdlib.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
HWND hMain;										// Handle to main window
HWND hDlg;										// Handle to dialog
HBITMAP hBMPPro, hBMPSrv, hBMPAdv;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	LoaderDlgProc(HWND , UINT , WPARAM , LPARAM);
HBITMAP LoadAnImage(char*);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN2KMENU, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_WIN2KMENU);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_WIN2KMENU);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 200, 100, NULL, NULL, hInstance, NULL);

   ShowWindow(hWnd,SW_HIDE);

   hDlg = CreateDialog(hInst,MAKEINTRESOURCE(IDD_LOADER),hWnd,(DLGPROC)LoaderDlgProc);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hDlg,nCmdShow);
   UpdateWindow(hDlg);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{	
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:

		wmId = 10;

		switch (wmId)
		{
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK LoaderDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch(Message)
    {
		case WM_INITDIALOG:
		/* Load bitmaps and put them in buttons */
		{
			HICON icon, smicon;

			//hBMPPro = LoadBitmap(GetModuleHandle(NULL),"win2kpro.bmp");
			hBMPPro = LoadAnImage("win2kpro.bmp");
			hBMPSrv = LoadAnImage("win2ksrv.bmp");
			hBMPAdv = LoadAnImage("win2kadv.bmp");

			/* Set images on buttons */
			SendMessage(GetDlgItem(hwnd,IDC_BTNPRO),BM_SETIMAGE,0,(LPARAM)hBMPPro);
			SendMessage(GetDlgItem(hwnd,IDC_BTNSRV),BM_SETIMAGE,0,(LPARAM)hBMPSrv);
			SendMessage(GetDlgItem(hwnd,IDC_BTNADV),BM_SETIMAGE,0,(LPARAM)hBMPAdv);

			/* Set icons for loader */
			icon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_WIN2KMENU));
			SendMessage(hwnd,WM_SETICON,ICON_BIG,(LPARAM)icon);

			smicon = LoadIcon(hInst,MAKEINTRESOURCE(IDI_SMALL));
			SendMessage(hwnd,WM_SETICON,ICON_SMALL,(LPARAM)icon);
		
			break;
		}
        case WM_COMMAND:
		{
            switch(LOWORD(wParam))
            {
				case IDC_BTNPRO:
					ShellExecute(hwnd,"open","SETUP.EXE",NULL,"UENGLISH\\PRO",SW_SHOW);
				break;
				case IDC_BTNSRV:
					ShellExecute(hwnd,"open","SETUP.EXE",NULL,"UENGLISH\\SERVER",SW_SHOW);
				break;
				case IDC_BTNADV:
					ShellExecute(hwnd,"open","SETUP.EXE",NULL,"UENGLISH\\ADV_SRV",SW_SHOW);
				break;
				case IDC_BTNIE6:
					ShellExecute(hwnd,"open","ie6setup.exe",NULL,"Extras\\IE6",SW_SHOW);
				break;
				case IDC_BTNIE6AK:
					ShellExecute(hwnd,"open","ieak6.exe",NULL,"Extras\\IE6",SW_SHOW);
				break;
				case IDC_BTNSYM:
					ShellExecute(hwnd,"open","symbols_sp.exe",NULL,"Extras\\Symbols",SW_SHOW);
				break;
			}
		}
        break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
        default:
            return FALSE;
    }
    return TRUE;
}

HBITMAP LoadAnImage(char* FileName)
    {
  IPicture* p;
  IStream* s;
  IPersistStream* ps;
  HGLOBAL hG;
  void* pp;
  FILE* fp;


  fp = fopen(FileName,"rb");
  if (!fp)
       return NULL;

  fseek(fp,0,SEEK_END);
  int fs = ftell(fp);
  fseek(fp,0,SEEK_SET);
  hG = GlobalAlloc(GPTR,fs);
  if (!hG)
       {
     fclose(fp);
     return NULL;
     }
  pp = (void*)hG;
  fread(pp,1,fs,fp);
  fclose(fp);

  CreateStreamOnHGlobal(hG,false,&s);
  if (!s)
       {
     GlobalFree(hG);
     return NULL;
     }

  OleLoadPicture(s,0,false,IID_IPicture,(void**)&p);

  if (!p)
       {
     s->Release();
     GlobalFree(hG);
     return NULL;
     }
  s->Release();
  GlobalFree(hG);

  HBITMAP hB = 0;
  p->get_Handle((unsigned int*)&hB);

  HBITMAP hBB = (HBITMAP)CopyImage(hB,IMAGE_BITMAP,0,0,LR_COPYRETURNORG);

  p->Release();
  return hBB;
}