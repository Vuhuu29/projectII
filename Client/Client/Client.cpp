// Client.cpp : Defines the entry point for the application.
//

#include "Client.h"
#include "framework.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    //MyRegisterClass(hInstance);
    if (myRegClass(WndProc, szWindowClass, hInst) == false)
        return 0;
    WCHAR a[] = L"chatbox";
    if (myRegClass(ChatBoxProc, a, hInst) == false)
        return 0;

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

bool myRegClass(WNDPROC lpfnWndProc, WCHAR* szClassName, HINSTANCE hInst)
{
    WNDCLASSEX wincl;        
    wincl.hInstance = hInst;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = lpfnWndProc;     
    wincl.style = CS_HREDRAW | CS_VREDRAW;                
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_CLIENT));
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.hbrBackground = (HBRUSH)(COLOR_BTNHILIGHT + 1);
    wincl.lpszMenuName = NULL;     
    wincl.cbClsExtra = 0;                      
    wincl.cbWndExtra = 0;                      
    wincl.hIconSm = LoadIcon(wincl.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    /* Register the window class, and if it fails quit the program */
    if (RegisterClassEx(&wincl)) return true;
    else return false;
    /*WNDCLASSEX wincl;
    wincl.hInstance = hInst;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = lpfnWndProc;
    wincl.style = CS_HREDRAW | CS_VREDRAW;

    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_CLIENT));
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.hbrBackground = (HBRUSH)(COLOR_BTNHILIGHT + 1);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hIconSm = LoadIcon(wincl.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    if (RegisterClassEx(&wincl)) return true;
    else return false;*/

}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 400, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DRAWITEM, OnDrawItem);
    case WM_CTLCOLORSTATIC:
    {
        HWND hStatic = (HWND)lParam;
        HDC hdc = (HDC)wParam;

        //SetTextColor(hdc, RGB(0, 215, 194));
        SetBkMode(hdc, TRANSPARENT);
        //return (LRESULT)CreateSolidBrush(RGB(255, 255, 255));
        return (LRESULT)GetStockObject(DC_BRUSH);
    }
    }
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void OnDestroy(HWND hwnd) {
    GdiplusShutdown(gdiplusToken);
	PostQuitMessage(0);
}

BOOL OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct) {

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    gCurScene = 0;

	char buf[4096];
	FILE* fp = fopen("server.ini", "r");
	if (fp == NULL) {
		MessageBox(0, L"\nUnable to open server.ini", 0, 0);
		return 1;
	}

	string sServerAddress;
	while (fgets(buf, 4096, fp) != NULL) {
		if (buf[0] == '#') continue;
		sServerAddress = buf;
	}

	/*std::wstring widestr = std::wstring(sServerAddress.begin(), sServerAddress.end());
	const wchar_t* widecstr = widestr.c_str();
	MessageBox(0, widecstr, 0, 0);*/

	fclose(fp);

	if (sServerAddress.size() == 0)
	{
		MessageBox(hWnd, L"\nUnable to connect to the IP address specified in server.ini\r\nPlease check server IP address.", 0, 0);
		return 0;
	}

    gClientObj.init(sServerAddress.c_str(), "8084");
    if (!gClientObj.isConnected())
    {
        MessageBox(hWnd, L"\nUnable to connect to the IP address specified in server.ini\r\nPlease check server IP address.", 0, 0);
        return 0;
    }

	gClientObj.setHWND(hWnd);
	AfxBeginThread(recMessageThread, 0);

    hFont = CreateFont(17, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");

    if (hFont == NULL)
    {
        LOGFONT lf;
        GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
        CreateFont(lf.lfHeight * 1.6, lf.lfWidth * 1.6,
            lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
            lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
            lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
            lf.lfPitchAndFamily, lf.lfFaceName);
    }
    SetWindowFont(hWnd, hFont, true);

	hUsername = CreateWindowEx(0, L"edit", L"", WS_VISIBLE	|  WS_CHILD, 50, 160, 280, 35, hWnd, 0, hInst, 0);
    SetWindowFont(hUsername, hFont, true);

	hPassword = CreateWindowEx(0, L"edit", L"", WS_VISIBLE	|  WS_CHILD | ES_PASSWORD, 50, 250, 280, 35, hWnd, (HMENU)99, hInst, 0);
    SetWindowFont(hPassword, hFont, true);

	hSignUp = CreateWindowEx(0, L"button", L"Sign Up", WS_VISIBLE	|  WS_CHILD | BS_OWNERDRAW, 50, 320, 135, 30, hWnd, (HMENU)IDC_SIGNUP, hInst, 0);

	hLogIn = CreateWindowEx(0, L"button", L"Log In", WS_VISIBLE		|  WS_CHILD | BS_OWNERDRAW, 195, 320, 135, 30, hWnd, (HMENU)IDC_LOGIN, hInst, 0);

	return TRUE;
}
void OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify){
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hWnd);
		break;
	case IDC_RECEIVE:
	{
		WCHAR* message = (WCHAR*)hwndCtl;
		switch (message[0])
		{
		case MessageType::LIST_USER_ONLINE:
		{
			/*
			* receive:	message = [FLAG | list user online | NULL]
			*/
			int  n = ListBox_GetCount(lsbTasks);
			if ((n = ListBox_GetCount(lsbTasks)) > 0)
				for (int i = 0; i < n; i++)
					ListBox_DeleteString(lsbTasks, i);
			message++;
			WCHAR a[] = L";";
			
			WCHAR* token = wcstok(message, a); 
			while (token != NULL)
			{
				ListBox_AddString(lsbTasks, token);
				token = wcstok(NULL, a); // C4996
			}
			break;
		}
		case MessageType::PRIVATE_CHAT:
		{
			/*
			* receive:	message = [FLAG | receiver | NULL | sender | NULL | content | NULL]
			*/
			PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
			message++;
			int	len = wcslen(message);
			WCHAR* partner;
			WCHAR* content;

			partner = message + len + 1;
			content = partner + wcslen(partner) + 1;

			for (auto chatbox : gPrivateChatBoxList)
			{
				if (wcscmp(chatbox->getPartner().c_str(), partner) == 0)
				{
					chatbox->receiveMessage(content);
					SetForegroundWindow(chatbox->getHWND());
					SetActiveWindow(chatbox->getHWND());
					return;
				}
			}
			auto cb = PrivateChatBox::create(hWnd, hInst, Point(CW_USEDEFAULT, CW_USEDEFAULT), Size(500, 500), partner);
			cb->setFont(hFont);
			cb->setUsername(gClientObj.getUsername());
			gPrivateChatBoxList.push_back(cb);
			cb->receiveMessage(content);
			SetForegroundWindow(cb->getHWND());
			SetActiveWindow(cb->getHWND());
			break;
		}
		
		case MessageType::END_PRIVATE_CHAT:
		{
			/*
			* receive:	message = [FLAG | receiver | NULL | sender | NULL]
			*/
			message++;
			WCHAR* sender;
			sender = message + wcslen(message) + 1;

			for (auto chatbox : gPrivateChatBoxList)
			{
				if (wcscmp(chatbox->getPartner().c_str(), sender) == 0)
				{
					chatbox->onEndChat();
					break;
				}
			}
			break;
		}
		
		case MessageType::SU_SUCCESS:
		{
			/*
			* receive:	message = [FLAG]
			*/
			MessageBox(hWnd, L"Sign Up Successfull!", L"Congratulations", 0);
			break;
		}
		case MessageType::SU_FAILURE:
		{
			/*
			* receive:	message = [FLAG]
			*/
			MessageBox(hWnd, L"Sign Up Failed", 0, 0);
			break;
		}
		case MessageType::LI_SUCCESS:
		{
			/*
			* receive:	message = [FLAG]
			*/
			MessageBox(hWnd, L"Log In Successful!", L"Congratulations", 0);
			DestroyWindow(hUsername);
			DestroyWindow(hPassword);
			DestroyWindow(hSignUp);
			DestroyWindow(hLogIn);
			gCurScene = 1;
			InvalidateRect(hWnd, 0, TRUE);

			HWND lbl = CreateWindowEx(NULL, L"BUTTON", L"User Online",
				WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
				40, 20, 310, 460, hWnd,
				NULL, hInst, NULL);
			SetWindowFont(lbl, hFont, TRUE);
			lsbTasks = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTBOX, NULL, WS_CHILD | WS_VISIBLE,
				50, 60, 290, 425, hWnd, NULL, hInst, NULL);
			SetWindowFont(lsbTasks, hFont, TRUE);

			hChat = CreateWindowEx(0, L"button", L"Chat", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 40, 500, 145, 30, hWnd, (HMENU)IDC_CHAT, hInst, 0);

			hRefresh = CreateWindowEx(0, L"button", L"Refresh", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 205, 500, 145, 30, hWnd, (HMENU)IDC_REFRESH, hInst, 0);

			message[0] = MessageType::LIST_USER_ONLINE;
			message[1] = NULL;
			gClientObj.sendMessagePort(message, 1);

			/*hInvitedUsername = CreateWindowEx(0, L"edit", L"", WS_VISIBLE | WS_CHILD, 50, 190, 280, 35, hWnd, 0, hInst, 0);
			SetWindowFont(hInvitedUsername, hFont, true);
			hPrivateChat = CreateWindowEx(0, L"button", L"Private Chat", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 50, 120, 280, 35, hWnd, (HMENU)IDC_PRIVATECHAT, hInst, 0);
			SetWindowFont(hPrivateChat, hFont, true);
			hGroupName = CreateWindowEx(0, L"edit", L"", WS_VISIBLE | WS_CHILD, 50, 330, 280, 35, hWnd, 0, hInst, 0);
			SetWindowFont(hGroupName, hFont, true);
			hGroupChat = CreateWindowEx(0, L"button", L"Group Chat", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 50, 260, 280, 35, hWnd, (HMENU)IDC_GROUPCHAT, hInst, 0);
			SetWindowFont(hGroupChat, hFont, true);
			hCreate = CreateWindowEx(0, L"button", L"Create", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 50, 400, 280, 35, hWnd, (HMENU)IDC_CREATE, hInst, 0);
			SendMessage(hPrivateChat, BM_SETCHECK, BST_CHECKED, 0);*/
			
			break;
		}
		case MessageType::LI_FAILURE:
		{
			/*
			* receive:	message = [FLAG]
			*/
			MessageBox(hWnd, L"Username or password is incorrect.", 0, 0);
			break;
		}
		case MessageType::C_PC_FAILURE:
		{
			/*
			* receive:	message = [FLAG]
			*/
			MessageBox(hWnd, L"The user is offline.", L"Create private chat", 0);
			break;
		}
		case MessageType::C_PC_SUCCESS:
		{
			/*
			* receive:	message = [FLAG | partner | NULL]
			*/
			message++;
			int	len = wcslen(message);
			MessageBox(hWnd, L"The user is online.", L"Create private chat", 0);
			for (auto chatbox : gPrivateChatBoxList)
			{
				if (wcscmp(chatbox->getPartner().c_str(), message) == 0)
				{
					return;
				}
			}
			auto cb = PrivateChatBox::create(hWnd, hInst, Point(100, 100), Size(500, 500), message);
			cb->setFont(hFont);
			cb->setUsername(gClientObj.getUsername());
			gPrivateChatBoxList.push_back(cb);
			break;
		}
		break;
		}
		break;
	}
	case IDC_SIGNUP:
	{
		/*
		* send:		message = [FLAG | username | NULL | password | NULL]
		*/
		WCHAR username[50];
		WCHAR password[50];
		WCHAR message[100];
		message[0] = MessageType::SIGNUP;
		message[1] = NULL;
		GetWindowText(hUsername, username, 50);
		if (username[0] == NULL)
		{
			MessageBox(hWnd, L"Username is empty.", 0, 0);
			return;
		}
		for (int i = 0; username[i] != NULL; i++)
		{
			if (username[i] == L';')
			{
				MessageBox(hWnd, L"The username has invalid characters: ;", 0, 0);
				return;
			}
		}
		GetWindowText(hPassword, password, 50);
		if (password[0] == NULL)
		{
			MessageBox(hWnd, L"Password is empty.", 0, 0);
			return;
		}
		wcscat(message, username);
		int len = wcslen(message);
		len++;
		int i;
		for (i = 0; password[i] != NULL; i++)
		{
			message[len + i] = password[i];
		}
		len += i;
		message[len] = NULL;
		gClientObj.sendMessagePort(message, len);
		break;
	}
	case IDC_LOGIN:
	{
		/*
		* send:		message = [FLAG | username | NULL | password | NULL]
		*/
		WCHAR username[50];
		WCHAR password[50];
		WCHAR message[100];
		message[0] = MessageType::LOGIN;
		message[1] = NULL;
		GetWindowText(hUsername, username, 50);
		if (username[0] == NULL)
		{
			MessageBox(hWnd, L"Uername is empty.", 0, 0);
			return;
		}
		for (int i = 0; username[i] != NULL; i++)
		{
			if (username[i] == L';')
			{
				MessageBox(hWnd, L"Username has an invalid character: ;", 0, 0);
				return;
			}
		}
		GetWindowText(hPassword, password, 50);
		if (password[0] == NULL)
		{
			MessageBox(hWnd, L"Password is empty.", 0, 0);
			return;
		}
		wcscat(message, username);
		int len = wcslen(message);
		len++;
		int i;
		for (i = 0; password[i] != NULL; i++)
		{
			message[len + i] = password[i];
		}
		len += i;
		message[len] = NULL;
		gClientObj.sendMessagePort(message, len);
		gClientObj.setUsername(username);
		break;
	}
	case IDC_CHAT:
	{
		//send:		message = [FLAG | partner | NULL]
		WCHAR message[50];
		WCHAR buffer[50];
		ListBox_GetText(lsbTasks, ListBox_GetCurSel(lsbTasks), buffer);

		message[0] = MessageType::CREATE_PRIVATE_CHAT;
		message[1] = NULL;
		//GetWindowText(hInvitedUsername, buffer, 50);
		if (buffer[0] == NULL)
		{
			MessageBox(hWnd, L"You haven't sellected Username!", 0, 0);
			return;
		}

		if (wcscmp(buffer, gClientObj.getUsername().c_str()) == 0)
		{
			MessageBox(hWnd, L"You can't create the private chat by your username!", 0, 0);
			return;
		}
		wcscat(message, buffer);
		int len = wcslen(message);
		gClientObj.sendMessagePort(message, len);
		break;
	}
	case IDC_REFRESH:
	{
		/*
		* send:		message = [FLAG | NULL]
		*/
		WCHAR message[50];
		message[0] = MessageType::LIST_USER_ONLINE;
		message[1] = NULL;
		gClientObj.sendMessagePort(message, 1);
	}
	}
}
void OnPaint(HWND hWnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);

    auto graphics = new Graphics(hdc);
    Gdiplus::Pen pen(Gdiplus::Color(255, 37, 156, 236));
    switch (gCurScene)
    {
    case 0:
    {
        graphics->DrawRectangle(&pen, 49, 159, 282, 37);
        graphics->DrawRectangle(&pen, 49, 249, 282, 37);

        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::PointF     pointF(46.0f, 135.0f);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 37, 156, 236));

        graphics->DrawString(L"Username:", -1, &font, pointF, &solidBrush);
        pointF = Gdiplus::PointF(46.0f, 225.0f);

        graphics->DrawString(L"Password:", -1, &font, pointF, &solidBrush);
        break;
    }
    case 2:
    {
        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::PointF pointF(46.0f, 165.0f);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 171, 210, 237));

        graphics->DrawString(L"Chat:", -1, &font, pointF, &solidBrush);
        graphics->DrawRectangle(&pen, 49, 189, 282, 37);

        pointF = Gdiplus::PointF(46.0f, 305.0f);
        graphics->DrawString(L"Group name", -1, &font, pointF, &solidBrush);
        graphics->DrawRectangle(&pen, 49, 329, 282, 37);
    }
    }
    EndPaint(hWnd, &ps);
}
void OnDrawItem(HWND hwnd, const DRAWITEMSTRUCT* lpDrawItem) {
    switch (lpDrawItem->CtlID)
    {
    case IDC_SIGNUP:
    {
        auto graphics = new Graphics(lpDrawItem->hDC);
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 254, 88, 136));
        graphics->FillRectangle(&brush, 0, 0, 135, 30);

        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::PointF     pointF(35, 6);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 255, 255));

        graphics->DrawString(L"Sign Up", -1, &font, pointF, &solidBrush);

        if (graphics) delete graphics;
        break;
    }
    case IDC_LOGIN:
    {
        auto graphics = new Graphics(lpDrawItem->hDC);
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 69, 215, 194));
        graphics->FillRectangle(&brush, 0, 0, 135, 30);

        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::PointF     pointF(43, 6);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 255, 255));
        graphics->DrawString(L"Log In", -1, &font, pointF, &solidBrush);

        if (graphics) delete graphics;
        break;
    }
    case IDC_CHAT:
    {
        auto graphics = new Graphics(lpDrawItem->hDC);
        Gdiplus::SolidBrush brush(Gdiplus::Color(255, 254, 88, 136));
        graphics->FillRectangle(&brush, 0, 0, 280, 35);

        Gdiplus::FontFamily fontFamily(L"Arial");
        Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
        Gdiplus::PointF     pointF(50, 8);
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 255, 255));
        graphics->DrawString(L"Chat", -1, &font, pointF, &solidBrush);

        if (graphics) delete graphics;
        break;
    }

	case IDC_REFRESH:
	{
		auto graphics = new Graphics(lpDrawItem->hDC);
		Gdiplus::SolidBrush brush(Gdiplus::Color(255, 69, 215, 194));
		graphics->FillRectangle(&brush, 0, 0, 280, 35);

		Gdiplus::FontFamily fontFamily(L"Arial");
		Gdiplus::Font       font(&fontFamily, 15, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
		Gdiplus::PointF     pointF(40, 8);
		Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 255, 255, 255));
		graphics->DrawString(L"Refresh", -1, &font, pointF, &solidBrush);

		if (graphics) delete graphics;
		break;
	}
    }
}

LRESULT CALLBACK ChatBoxProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CTLCOLORSTATIC:
    {
        HWND hStatic = (HWND)lParam;
        HDC hdc = (HDC)wParam;

        SetBkMode(hdc, TRANSPARENT);
        return (LRESULT)GetStockObject(DC_BRUSH);
    }
    case WM_DRAWITEM:
    {
        auto dit = (DRAWITEMSTRUCT*)(lParam);
        switch (dit->CtlID)
        {
        case IDC_SEND:
        {
            auto graphics = new Graphics(dit->hDC);
            Gdiplus::SolidBrush brush(Gdiplus::Color(255, 69, 215, 194));
            graphics->FillRectangle(&brush, 0, 0, 75, 75);

            Gdiplus::FontFamily  fontFamily(L"Arial");
            Gdiplus::Font        font(&fontFamily, 17, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
            Gdiplus::PointF      pointF(15, 30);
            Gdiplus::SolidBrush  solidBrush(Gdiplus::Color(255, 255, 255, 255));

            graphics->DrawString(L"Send", -1, &font, pointF, &solidBrush);

            if (graphics)
                delete graphics;
            break;
        }
        }
        break;
    }
    case WM_CREATE:
        break;

    case WM_DESTROY:
        for (auto chatbox : gPrivateChatBoxList)
        {
            if (chatbox->getHWND() == hwnd)
            {
                gPrivateChatBoxList.remove(chatbox);
                WCHAR message[101];
                WCHAR* sender;
                message[0] = MessageType::END_PRIVATE_CHAT;
                message[1] = NULL;
                wcscat(message, chatbox->getPartner().c_str());
                sender = message + chatbox->getPartner().size() + 2;
                wcscpy(sender, gClientObj.getUsername().c_str());
                int len = chatbox->getPartner().size() + gClientObj.getUsername().size() + 3;
                gClientObj.sendMessagePort(message, len);
                break;
            }
        }
        DestroyWindow(hwnd);

        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_SEND:
        {
            for (auto chatbox : gPrivateChatBoxList)
            {
                if (chatbox->getHWND() == hwnd)
                {
                    WCHAR buffer[1000];
                    int len = chatbox->onPressBtnSend(buffer);
                    if (len == -1)
                    {
                        return 0;
                    }
                    gClientObj.sendMessagePort(buffer, len);
                    break;
                }
            }
            break;
        }
        }
        break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}