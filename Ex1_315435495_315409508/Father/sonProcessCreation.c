#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include "HardCodedData.h"
#include "sonProcessCreation.h"
#include <string.h>
#include <stdlib.h>

/*#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55

BOOL CreateProcessS(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
int CreateProcessSon(char* forestLine);*/

int CreateProcessSon(char* forestLine)
{
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	char* command;
	command = malloc(sizeof(char) * MAX_LINE_LENGTH); 

	char location[MAX_LINE_LENGTH] = "..\\Debug\\Son.exe";

	snprintf(command, sizeof(char) * MAX_LINE_LENGTH, "%s %s", location, forestLine);
	printf("%s\n", command);
	TCHAR* tmp = (TCHAR*)(command);
	//TCHAR	command[] = TCHAR*)("son.exe TGFGTFGTFGTFGTGTFFFGT");
													/*  Start the child process. */
	retVal = CreateProcessS(tmp, &procinfo);

	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return ERROR_CODE;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */

	printf("WaitForSingleObject output: ");
	switch (waitcode)
	{
	case WAIT_TIMEOUT:
		printf("WAIT_TIMEOUT\n"); break;
	case WAIT_OBJECT_0:
		printf("WAIT_OBJECT_0\n"); break;
	default:
		printf("0x%x\n", waitcode);
	}

	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate,
					note the above command may also fail, so another WaitForSingleObject is required.
					We skip this for brevity */
	}

	GetExitCodeProcess(procinfo.hProcess, &exitcode);

	printf("The exit code for the process is 0x%x\n", exitcode);

	/* Note: process is still being tracked by OS until we release handles */
	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
	//free(commandtmp);
	free(command);
	return (int)exitcode;

}

BOOL CreateProcessS(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr)
{
	printf("%s\n", CommandLine);
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(
		NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}
#endif