#pragma once

using namespace std;

// 반드시 Windows.h 전에 WinSock2 관련 포함
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#pragma comment(lib, "ws2_32.lib")


#include <Windows.h>
#include <iostream>


#include <assert.h>
#include "define.h"


#include "RWLock.h"

#include <mutex>
#include <atomic>

#include "container.h"
#include "Global.h"
#include "SendBufferChunk.h"
//#include "Allocator.h"
