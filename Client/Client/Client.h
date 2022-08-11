#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_WCSTOK
#include "ChatClient.h"
#include "ThreadFunc.h"
#include "resource.h"
#include "PrivateChatBox.h"
#include <windows.h>
#include <windowsx.h>
#include <list>
#include <stdio.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "Winmm.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


HWND hTextBox, hSignUp, hLogIn, hUsername, hPassword, hInvitedUsername, hPrivateChat, hGroupChat, hGroupName, hCreate, hwnd, hChat, hRefresh, lsbTasks;
HFONT hFont;

int gCurScene;
GdiplusStartupInput gdiplusStartupInput;

list<PrivateChatBox*> gPrivateChatBoxList;

enum MessageType gCurMessageStartupInput;
ULONG_PTR gdiplusToken;

LPWSTR convertSize(DWORD size);
bool myRegClass(WNDPROC lpfnWndProc, WCHAR* szClassName, HINSTANCE hInst);
LRESULT CALLBACK ChatBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);
void OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT* lpDrawItem);
