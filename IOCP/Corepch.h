#pragma once


#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.

#include <WinSock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
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

using namespace std;