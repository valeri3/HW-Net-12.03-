#include "ClientDlg.h"

ClientDlg* ClientDlg::ptr = NULL;

const int MAXSTRLEN = 255;

ClientDlg::ClientDlg(void)
{
	ptr = this;
}

ClientDlg::~ClientDlg(void)
{

}

void ClientDlg::Cls_OnClose(HWND hwnd)
{
	closesocket(_socket);

	WSACleanup();
	EndDialog(hwnd, 0);
}

BOOL ClientDlg::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	hConnect = GetDlgItem(hwnd, IDC_CONNECT);
	hTextToServer = GetDlgItem(hwnd, IDC_EDIT_TO_SERVER);
	hSend = GetDlgItem(hwnd, ID_SEND_TO_SERVER);
	hListFormServer = GetDlgItem(hwnd, IDC_LIST_FROM_SERVER);

	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_SERVER), FALSE);

	return TRUE;
}

void ClientDlg::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDC_CONNECT:
	{
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		addr.sin_family = AF_INET;

		inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

		addr.sin_port = htons(20000);

		int iResult = connect(_socket, (SOCKADDR*)&addr, sizeof(addr));

		if (iResult == SOCKET_ERROR)
		{
			closesocket(_socket);
			MessageBox(hwnd, TEXT("Не удалось подключиться к серверу."), TEXT("Ошибка"), MB_OK | MB_ICONERROR);
			return;
		}

		MessageBox(hwnd, TEXT("Клиент соединился и ожидает отправки сообщения."), TEXT("Клиент"), MB_OK);
		EnableWindow(GetDlgItem(hwnd, IDC_CONNECT), FALSE);
		EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_SERVER), TRUE);

		break;
	}


	case ID_SEND_TO_SERVER:
	{
		char buf[MAXSTRLEN];

		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_TO_SERVER);
		GetWindowTextA(hEdit, buf, MAXSTRLEN);

		send(_socket, buf, strlen(buf), 0);

		char buf1[MAXSTRLEN];
		int i = recv(_socket, buf1, MAXSTRLEN - 1, 0);

		buf1[i] = '\0';
		HWND hList = GetDlgItem(hwnd, IDC_LIST_FROM_SERVER);
		SendMessageA(hList, LB_ADDSTRING, 0, (LPARAM)buf1);

		EnableWindow(GetDlgItem(hwnd, ID_SEND_TO_SERVER), FALSE);

		break;
	}

	}
}

BOOL CALLBACK ClientDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}