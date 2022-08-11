#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define _AFXDLL
#include <afxwin.h>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

class ChatClient
{
public:
	ChatClient();
	~ChatClient();
	void init(string ipAddress, string port);
	int sendMessagePort(WCHAR* message, int len);
	int recvMessagePort();
	bool isConnected();
	void setHWND(HWND hwnd);
	void setUsername(wstring username);
	wstring& getUsername();
	int sendMesPort(WCHAR* message, int len);
private:
	bool _isConnected;
	string _serverIPAddress;
	string _serverPort;
	SOCKET _connect;
	HWND _hwnd;
	wstring _username;
};