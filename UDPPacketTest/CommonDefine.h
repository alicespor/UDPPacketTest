#pragma once

#define _DEBUG_MEM_

#ifdef _DEBUG_MEM_

#define CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>  

#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

inline void EnableMemLeakCheck()
{
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
}

#endif


#define _OUTPUT_TO_CONSOLE_
//#define _OUTPUT_TO_FILE_
//#define _NO_LOG_

void WriteLog(const char* ch,...);
void WriteLogBegin();
void WriteLogEnd();

//define error
#define ERROR_NONE                0
#define ERROR_UNKNOW              (ERROR_NONE + 1)

