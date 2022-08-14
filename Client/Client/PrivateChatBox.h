#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <new>
#include <ObjIdl.h>
#include <gdiplus.h>
#include <Windows.h>
#include "Definition.h"
#include <Shellapi.h>
#include <windowsx.h>
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
using namespace std;
class PrivateChatBox
{
private:
	HWND _hParent, _hWnd, _hMessageBox, _hTextBox, _hSend;
	HINSTANCE _hInts;
	HANDLE _hSentFile, _hReceiveFile;
	wstring _username, _parterUsername, _filename;
	Point _position;
	Size _size;
	bool _isEndChat;
	DWORD _sendFileSize, _recFilesize, _totalRecSize;
public:
	static PrivateChatBox* create(HWND hParent, HINSTANCE hInst, Point pos, Size size, wstring partner);
	wstring getPartner();
	void setFont(HFONT hFont);
	void receiveMessage(WCHAR* message);
	int onPressBtnSend(WCHAR* messageBuf);
	void onEndChat();
	void setUsername(const wstring& username);
	HWND getHWND();
	wstring getUsername();
	PrivateChatBox();
	~PrivateChatBox();
	
};