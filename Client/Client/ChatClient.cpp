#include "ChatClient.h"
#include "framework.h"

#include "Resource.h"
#include <ws2tcpip.h>

ChatClient::ChatClient() {
	_isConnected = false;
}

ChatClient::~ChatClient() {
	if (_isConnected) closesocket(_connect);
}

void ChatClient::init(string ipAddress, string port) {
	
	WSADATA wsaData;
	struct addrinfo* result = NULL, * ptr = NULL, hints;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) return;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET6;   
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(ipAddress.c_str(), "8084", &hints, &result);
	if (iResult != 0) return;

	_connect = socket(result->ai_family, result->ai_socktype,
		result->ai_protocol);
	if (_connect == INVALID_SOCKET) return;

	iResult = connect(_connect, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(_connect);
		return;
	}/**/
	
	/*_serverIPAddress = ipAddress;
	_serverPort = port;
	struct sockaddr_in server;
	
	WSADATA wsaData;
	int wsaret = WSAStartup(0x101, &wsaData);
	if (wsaret != 0) return;

	struct addrinfo* result = NULL, * ptr = NULL, hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	PCSTR x = _serverIPAddress.c_str();
	PCSTR y = _serverPort.c_str();

	if (getaddrinfo(x, y, &hints, &result) != 0) return;

	_connect = socket(AF_INET, SOCK_STREAM, 0);
	if (_connect == INVALID_SOCKET) return;

	if (connect(_connect, result->ai_addr, (int)result->ai_addrlen)){
		closesocket(_connect);
		return;
	}*/
	
	_isConnected = true;
	return;
}
int ChatClient::sendMessagePort(WCHAR* message, int len) {
	int iStat = 0;

	iStat = send(_connect, (char*)message, len * 2 + 2, 0);
	if (iStat == -1) return 1;
	return 0;
}

int ChatClient::sendMesPort(WCHAR* message, int len) {
	int iStat = 0;

	iStat = send(_connect, (char*)message, len, 0);
	if (iStat == -1) return 1;
	return 0;
}

int ChatClient::recvMessagePort() {
	char acRetData[4096];
	int iStat = 0;

	iStat = recv(_connect, acRetData, 4096, 0);
	if (iStat == -1) return 1;

	SendMessage(_hwnd, WM_COMMAND, (WPARAM)IDC_RECEIVE, (LPARAM)acRetData);

	return 0;
}
bool ChatClient::isConnected() {
	return _isConnected;
}
void ChatClient::setHWND(HWND hwnd) {
	_hwnd = hwnd;
}
void ChatClient::setUsername(wstring username) {
	_username = username;
}
wstring& ChatClient::getUsername() {
	return _username;
}