#ifndef SONPROCESSCREATION
#define SONPROCESSCREATION

#include <Windows.h>

#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55

BOOL CreateProcessS(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
int CreateProcessSon(char* forestLine);



#endif