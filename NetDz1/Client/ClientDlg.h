#pragma once
#include "header.h"


class ClientDlg
{
public:
	ClientDlg(void);
public:
	HANDLE hEventFinishProcessing;
	~ClientDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static ClientDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hDialog, hConnect, hTextToServer, hSend, hListFormServer;

	WSADATA wsaData;
	SOCKET _socket; 
	sockaddr_in addr;
};
