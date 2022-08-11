#include "ChatServer.h"//nên để lên đầu vì nó có chứa afxwin.h
#include "framework.h"
#include "Threadfunc.h"
#include "Resource.h"
#include <WS2tcpip.h>

ChatServer::ChatServer()
{
	
	_isConnected = false;

	WSADATA wsaData;

	int iResult;
	SOCKET server = INVALID_SOCKET;
	SOCKET client = INVALID_SOCKET;
	struct addrinfo* result = NULL;
	struct addrinfo hints;
	int iSendResult;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) return;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	//
	iResult = getaddrinfo(NULL, "8084", &hints, &result);
	if (iResult != 0) return;
	
	_socListenClient = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (_socListenClient == INVALID_SOCKET) return;
	
	iResult = bind(_socListenClient, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) return;

	freeaddrinfo(result);

	iResult = listen(_socListenClient, SOMAXCONN);
	if (iResult == SOCKET_ERROR) return;/**/

	/*WSADATA wsaData;
	sockaddr_in local;

	int wsaret = WSAStartup(0x101, &wsaData);

	if (wsaret != 0)
	{
		return;
	}

	local.sin_family = AF_INET;
	local.sin_addr.S_un.S_addr = INADDR_ANY;
	local.sin_port = htons((u_short)8084);
	
	_socListenClient = socket(AF_INET, SOCK_STREAM, 0);

	if (_socListenClient == INVALID_SOCKET)
	{
		return;
	}

	if (bind(_socListenClient, (sockaddr*)&local, sizeof(local)) != 0)
	{
		return;
	}

	if (listen(_socListenClient, 10) != 0)
	{
		return;
	}*/
	
	_isConnected = true;
	return;
}

ChatServer::~ChatServer()
{
	closesocket(_socListenClient);

	WSACleanup();

	if (_clientList.size() != 0)
	{
		for (auto client : _clientList)
		{
			delete client;
		}
	}
}

bool ChatServer::isConnected()
{
	return _isConnected;
}

void ChatServer::startListenClient()
{
	//sockaddr_in from;
	sockaddr_in6 from;
	int fromlen = sizeof(from);

	//_socClient = accept(_socListenClient, (struct sockaddr*)&from, &fromlen);
	_socClient = accept(_socListenClient, NULL, NULL);

	if (_socClient != INVALID_SOCKET)
	{
		auto packet = new ClientPacket;
		packet->socket = _socClient;
		SendMessage(_hwnd, WM_COMMAND, ID_USER_CONNECT, 0);
		_clientList.push_back(packet);
		AfxBeginThread(recServerThread, (void*)_socClient);
	}
}



int ChatServer::sendMessageClient(ClientPacket* client, WCHAR* message, int len)
{
	int iStat = 0;

	iStat = send(client->socket, (char*)message, len * 2 + 2, 0);
	if (iStat == -1)
		_clientList.remove(client);
	if (iStat == -1)
		return 1;

	return 0;

}

int ChatServer::recClient(SOCKET recSocket)
{
	WCHAR* message;
	WCHAR temp[4096];
	int iStat;
	int len;
	iStat = recv(recSocket, (char*)temp, 4096, 0);
	list<ClientPacket*>::iterator itl;
	for (itl = _clientList.begin(); itl != _clientList.end(); itl++)
	{
		if ((*itl)->socket == recSocket)
		{
			break;
		}
	}

	if (iStat == -1)
	{
		
		_clientList.remove((*itl));
		SendMessage(_hwnd, WM_COMMAND, ID_USER_LEAVE, 0);
		return 1;
	}
	else
	{
		message = temp;
		switch (message[0])
		{
		case MessageType::PRIVATE_CHAT:
		{
			/*
			* receive:	message = [FLAG | receiver | NULL | sender | NULL | content | NULL]
			* receive:	message = [FLAG | receiver | NULL | sender | NULL | content | NULL]
			*/

			WCHAR* partner;
			partner = message + 1;


			for (auto client : _clientList)
			{
				if (wcscmp(client->username.c_str(), partner) == 0)
				{
					sendMessageClient(client, (WCHAR*)message, iStat / 2);
					break;
				}
			}
			break;
		}
		
		case MessageType::END_PRIVATE_CHAT:
		{
			/*
			* receive:	message = [FLAG | receiver | NULL | sender | NULL]
			* send:		message = [FLAG | receiver | NULL | sender | NULL]
			*/
			WCHAR* receiver = message + 1;

			for (auto client : _clientList)
			{
				if (wcscmp(client->username.c_str(), receiver) == 0)
				{
					sendMessageClient(client, (WCHAR*)message, iStat / 2);
					break;
				}
			}
			break;
		}
		
		case MessageType::SIGNUP:
		{
			/*
			* receive:	message = [FLAG | user name | NULL | password | NULL]
			* send:		message = [FLAG]
			*/

			WCHAR* username;
			WCHAR* password;

			username = message + 1;
			password = message + wcslen(message) + 1;

			auto user = new User;
			user->username = username;
			user->password = password;
			int result = signUp(user);
			if (result == true)
			{
				message[0] = MessageType::SU_SUCCESS;
				SendMessage(_hwnd, WM_COMMAND, ID_RESTORE, 0);
			}
			else
			{
				message[0] = MessageType::SU_FAILURE;
			}
			sendMessageClient((*itl), (WCHAR*)message, 1);
			break;
		}
		case MessageType::LOGIN:
		{
			/*
			* receive:	message = [FLAG | user name | NULL | password | NULL]
			* send:		message = [FLAG]
			*/

			WCHAR* username;
			WCHAR* password;
			username = message + 1;
			password = message + wcslen(message) + 1;
			User user;
			user.username = username;
			user.password = password;
			int result = logIn(recSocket, user);
			if (result == true)
			{
				message[0] = MessageType::LI_SUCCESS;
			}
			else
			{
				message[0] = MessageType::LI_FAILURE;
			}

			sendMessageClient((*itl), (WCHAR*)message, 1);
			break;
		}
		case MessageType::LIST_USER_ONLINE:
		{
			//receiver: [FLAG]

			for (auto packet : _clientList) {
				wcscat(message, packet->username.c_str());
				wcscat(message, L";");
			}
			sendMessageClient((*itl), (WCHAR*)message, wcslen(message));
			break;
		}
		case MessageType::CREATE_PRIVATE_CHAT:
		{
			/*
			* receive:	message = [FLAG | partner | NULL]
			* send:		message = [FLAG | parter | NULL]	- Succeed
			*					  [FLAG]					- Fail
			*/

			WCHAR* partner;
			partner = message + 1;
			bool result = isOnlineUser(partner);
			if (result == true)
			{

				message[0] = MessageType::C_PC_SUCCESS;
				sendMessageClient((*itl), (WCHAR*)message, iStat / 2);
			}
			else
			{
				message[0] = MessageType::C_PC_FAILURE;
				sendMessageClient((*itl), (WCHAR*)message, 1);
			}
			break;
		}
		
		}

		return 0;
	}
	return 0;

}

void ChatServer::setHWND(HWND hwnd)
{
	_hwnd = hwnd;
}

bool ChatServer::signUp(User* user)
{
	for (auto userdata : _userData)
	{
		if (user->username == userdata->username)
		{
			return false;
		}
	}
	_userData.push_back(user);
	return true;
}

bool ChatServer::logIn(SOCKET socket, User user)
{
	for (auto userdata : _userData)
	{
		if (user.username == userdata->username && user.password == userdata->password)
		{
			for (auto client : _clientList)
			{
				if (client->socket == socket)
				{
					client->username = user.username;
					return true;
				}
			}
		}
	}
	return false;
}

bool ChatServer::isOnlineUser(wstring username)
{
	for (auto client : _clientList)
	{
		if (username == client->username)
		{
			return true;
		}
	}
	return false;
}

void ChatServer::addUser(User* user)
{
	_userData.push_back(user);
}

list<User*>& ChatServer::getUser()
{
	return _userData;
}

list<ClientPacket*>& ChatServer::getClientList()
{
	return _clientList;
}