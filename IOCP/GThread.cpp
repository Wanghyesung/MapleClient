#include "pch.h"
#include "GThread.h"

thread_local int T_Thread_ID = 0;
thread_local shared_ptr<SendBufferChunk> T_SendBufferChunk = nullptr;
