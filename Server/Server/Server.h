#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "ChatServer.h"
#include "ThreadFunc.h"
#include "resource.h"
#include <fstream>
#include <codecvt>
#include <Windows.h>
#include <iostream>
#include <xlocale>
#include <xstring>
#include <codecvt>

HWND hTextBox;

void LoadData();
void RestoreData();
