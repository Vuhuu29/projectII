#pragma once
#define _AFXDLL
#define _CRT_SECURE_NO_WARNINGS
#include "Definition.h"


class ChatServer
{
public:
	ChatServer();
	~ChatServer();
	bool isConnected();
	void startListenClient();
	int sendMessageClient(ClientPacket* client, WCHAR* message, int len);
	int recClient(SOCKET recSocket);
	void setHWND(HWND hwnd);
	bool signUp(User* user);
	bool logIn(SOCKET socket, User user);
	bool isOnlineUser(wstring username);
	void addUser(User* user);
	list<User*>& getUser();
	list<ClientPacket*>& getClientList();
	int sendMesClie(ClientPacket* client, WCHAR* message, int len);

private:
	bool _isConnected;
	int _serverPort;
	list<ClientPacket*> _clientList;
	SOCKET _socClient;
	SOCKET _socListenClient = INVALID_SOCKET;
	HWND _hwnd;
	list<User*> _userData;
};

