#pragma once
#include <afxwin.h>//phải để lên đầu
#include <WinSock2.h>
#include <list>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>
//#pragma comment (lib, "Ws2_32.lib")
using namespace std;
struct ClientPacket
{
	SOCKET socket;
	wstring username;
};

struct User
{
	wstring username;
	wstring password;
};

struct GroupChat
{
	wstring name;
	list<wstring> username;
};

enum MessageType
{
	PRIVATE_CHAT = 1,
	END_PRIVATE_CHAT = 2,
	SIGNUP = 3,
	SU_SUCCESS = 4,
	SU_FAILURE = 5,
	LOGIN = 6,
	LI_SUCCESS = 7,
	LI_FAILURE = 8,
	CREATE_PRIVATE_CHAT = 9,
	C_PC_SUCCESS = 10,
	C_PC_FAILURE = 11,
	LIST_USER_ONLINE = 12
};