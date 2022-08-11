#include "ChatClient.h"
#include "framework.h"
#include "ThreadFunc.h"

ChatClient gClientObj;
UINT recMessageThread(LPVOID lParam) {
	while (1) {
		if (gClientObj.recvMessagePort()) break;
	}
	return 0;
}