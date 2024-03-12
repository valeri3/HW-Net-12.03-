#pragma once
#include "header.h"



class CserverDlg
{
public:
	CserverDlg(void);
public:
	HANDLE hEventFinishProcessing;
	~CserverDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static CserverDlg* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	HWND hDialog, hStart, hTextToClient, hSend, hListFromClient;


	WSADATA wsaData;
	SOCKET _socket; 
	SOCKET acceptSocket; 
	sockaddr_in addr; 
};
