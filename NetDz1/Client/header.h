#pragma once

#define WIN32_LEAN_AND_MEAN 

#include<windows.h>
#include <windowsX.h>
#include <commctrl.h>
#include <tchar.h>
#include"resource.h"
#include <vector>
#include <string>
#include <fstream> 
#include <algorithm> 
#include <sstream> 
#include <locale>

#include "WinSock2.h"
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

#pragma comment(lib,"comctl32")
using namespace std;