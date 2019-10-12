//logÊä³ö;  
#include "stdafx.h"
#include <iostream>  
#include <iomanip>  
#include <fstream>  
#include "commonDefine.h"

#include <stdarg.h>
using namespace std;

//other code  
FILE *fpLog = NULL;
ofstream outfile;


void WriteLogBegin()
{
#ifdef _OUTPUT_TO_CONSOLE_
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#elif defined _OUTPUT_TO_FILE_ 
	fpLog = fopen("c:\\Accurate3DMeasurement.txt", "w+");
	outfile.open("c:\\Accurate3DMeasurement.txt");
#endif
}

void WriteLog(const char * logStr, ...)
{
	char szFormt[4096];
#ifdef _OUTPUT_TO_FILE_
	if (fpLog == NULL) return;
	
	va_list args;

	va_start(args, logStr);
	vfprintf(fpLog, logStr, args);
	va_end(args);

	//fwrite(logStr, logStr.GetLength()*2, 1, fpLog);
	//fprintf(fpLog, "%S", logStr.GetBuffer(logStr.GetLength()));

	/*if (outfile.is_open())
	{
		//      outfile<<logStr;        //´íÎó  
		outfile << CT2A(logStr);
		outfile.close();
	}*/
#elif defined _OUTPUT_TO_CONSOLE_
	//printf((char*)(LPCTSTR)logStr);

	
	va_list valist;

	//char *ch;
	//ch = (LPSTR)(LPCTSTR)logStr;

	va_start(valist, logStr);

	vsnprintf(szFormt, sizeof(szFormt), logStr, valist);

	vprintf(szFormt, valist);

	va_end(valist);

	//printf("%S",logStr.GetBuffer(logStr.GetLength()));
#endif
}

void WriteLogEnd()
{
#ifdef _OUTPUT_TO_CONSOLE_
	FreeConsole();
#elif defined _OUTPUT_TO_CONSOLE_
	//outfile.close();
	fclose(fpLog);
#endif
}
