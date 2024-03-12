#include "CserverDlg.h"

CserverDlg* CserverDlg::ptr = NULL;

const int MAXSTRLEN = 255;

CserverDlg::CserverDlg(void)
{
	ptr = this;
}

CserverDlg::~CserverDlg(void)
{

}

void CserverDlg::Cls_OnClose(HWND hwnd)
{
	closesocket(acceptSocket);
	closesocket(_socket);

	WSACleanup();
	EndDialog(hwnd, 0);
}

BOOL CserverDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hStart = GetDlgItem(hwnd, IDC_START);
	hTextToClient = GetDlgItem(hwnd, IDC_EDIT_TO_CLIENT);
	hSend = GetDlgItem(hwnd, ID_SEND_TO_CLIENT);
	hListFromClient = GetDlgItem(hwnd, IDC_LIST_FROM_CLIENT);

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_CLIENT), FALSE);

	return TRUE;
}


void CserverDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_START:
	{
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		addr.sin_family = AF_INET;

		inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);

		addr.sin_port = htons(20000);

		bind(_socket, (SOCKADDR*)&addr, sizeof(addr));

		listen(_socket, 1);

		MessageBox(hwnd, TEXT("Сервер запущен и ожидает подключений."), TEXT("Сервер"), MB_OK);
		EnableWindow(GetDlgItem(hwnd, IDC_START), FALSE);

		EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_CLIENT), TRUE);

		break;

	}
	case ID_SEND_TO_CLIENT:
	{
		acceptSocket = accept(_socket, NULL, NULL);
		char buf[MAXSTRLEN];

		int i = recv(acceptSocket, buf, MAXSTRLEN - 1, 0);

		buf[i] = '\0';
		HWND hList = GetDlgItem(hwnd, IDC_LIST_FROM_CLIENT);
		SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)buf);

		char buf1[MAXSTRLEN];
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_TO_CLIENT);
		GetWindowTextA(hEdit, buf1, MAXSTRLEN);

		send(acceptSocket, buf1, strlen(buf1), 0);

		EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_CLIENT), FALSE);

		break;
	}

	}
}

BOOL CALLBACK CserverDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}