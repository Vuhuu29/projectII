#include "PrivateChatBox.h"
#include "framework.h"
#include "resource.h"

PrivateChatBox* PrivateChatBox::create(HWND hParent, HINSTANCE hInst, Point pos, Size size, wstring partner)
{
	auto cb = new(std::nothrow)PrivateChatBox();//trả về null nếu k khởi tạo đc thay vì throw 1 ngoại lệ
	cb->_hWnd = CreateWindowEx(0, L"chatbox", (partner + L" - Private Chat").c_str(), WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_MINIMIZEBOX, pos.X, pos.Y, size.Width, size.Height, NULL, NULL, hInst, NULL);
	cb->_hInts = hInst;
	cb->_hParent = hParent;
	cb->_position = pos;
	cb->_size = size;
	cb->_parterUsername = partner;
	cb->_hMessageBox = CreateWindowEx(WS_EX_RIGHTSCROLLBAR, L"edit", L"", WS_VISIBLE | WS_VSCROLL | WS_CHILD | ES_AUTOVSCROLL | ES_MULTILINE | ES_READONLY | WS_BORDER, size.Width * 0.025, size.Height * 0.025, size.Width * 0.925, size.Height * 0.635, cb->_hWnd, (HMENU)1000, hInst, 0);
	cb->_hTextBox = CreateWindow(L"edit", L"", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_BORDER, size.Width * 0.025, size.Height * 0.7, size.Width * 0.55, size.Height * 0.15, cb->_hWnd, 0, hInst, 0);
	cb->_hSend = CreateWindow(L"button", L"Send", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, size.Width * 0.6, size.Height * 0.7, size.Width * 0.15, size.Height * 0.15, cb->_hWnd, (HMENU)IDC_SEND, hInst, 0);
	cb->_hAttach = CreateWindow(L"button", L"Attach", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, size.Width * 0.775, size.Height * 0.7, size.Width * 0.15, size.Height * 0.15, cb->_hWnd, (HMENU)IDC_ATTACH, hInst, 0);
	return cb;
}

wstring PrivateChatBox::getPartner()
{
	return _parterUsername;
}

void PrivateChatBox::setFont(HFONT hFont)
{
	SetWindowFont(_hMessageBox, hFont, true);
	SetWindowFont(_hTextBox, hFont, true);
}

void PrivateChatBox::receiveMessage(WCHAR* message)
{
	WCHAR buffer[10000];
	GetWindowText(_hMessageBox, buffer, 10000);
	wcscat(buffer, L"\r\n\r\n$[");
	wcscat(buffer, _parterUsername.c_str());
	wcscat(buffer, L"]:\r\n");
	wcscat(buffer, message);
	SetWindowText(_hMessageBox, buffer);

	SendMessageA(_hMessageBox, EM_SETSEL, 0, -1);
	SendMessageA(_hMessageBox, EM_SETSEL, -1, -1);
	SendMessageA(_hMessageBox, EM_SCROLLCARET, 0, 0);
}

int PrivateChatBox::onPressBtnSend(WCHAR* message)
{
	WCHAR bufferText[1000];
	WCHAR bufferMess[100000];
	message[0] = MessageType::PRIVATE_CHAT;
	message[1] = NULL;
	GetWindowText(_hTextBox, bufferText, 1000);
	SetWindowText(_hTextBox, L"");
	if (bufferText[0] == NULL) return -1;
	
	WCHAR* content;
	WCHAR* sender;

	int len;
	wcscat(message, _parterUsername.c_str());

	len = _parterUsername.size() + 1;
	sender = message + ++len;
	wcscpy(sender, _username.c_str());
	len += _username.size() + 1;

	content = message + len;
	wcscpy(content, bufferText);
	len += wcslen(bufferText);

	GetWindowText(_hMessageBox, bufferMess, 10000);
	wcscat(bufferMess, L"\r\n\r\n[You]:\r\n");
	wcscat(bufferMess, bufferText);
	SetWindowText(_hMessageBox, bufferMess);

	SendMessageA(_hMessageBox, EM_SETSEL, 0, -1);
	SendMessageA(_hMessageBox, EM_SETSEL, -1, -1);
	SendMessageA(_hMessageBox, EM_SCROLLCARET, 0, 0);

	if (_isEndChat) return -1;

	return len;
}

void PrivateChatBox::onEndChat()
{
	WCHAR buffer[10000];
	GetWindowText(_hMessageBox, buffer, 10000);
	wcscat(buffer, L"\r\n\r\n\tThis conversation was ended by your partner.\r\n");
	SetWindowText(_hMessageBox, buffer);

	SendMessageA(_hMessageBox, EM_SETSEL, 0, -1);
	SendMessageA(_hMessageBox, EM_SETSEL, -1, -1);
	SendMessageA(_hMessageBox, EM_SCROLLCARET, 0, 0);
	_isEndChat = true;
}

void PrivateChatBox::setUsername(const wstring& username)
{
	_username = username;
}

HWND PrivateChatBox::getHWND()
{
	return _hWnd;
}

wstring PrivateChatBox::getUsername()
{
	return _username;
}

PrivateChatBox::PrivateChatBox()
{
	_isEndChat = false;
	_hSentFile = NULL;
	_hReceiveFile = NULL;
	_totalRecSize = 0;
	_recFilesize = 0;
}

PrivateChatBox::~PrivateChatBox()
{

}