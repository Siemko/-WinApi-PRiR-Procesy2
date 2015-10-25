#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFile, hMutex;
	DWORD ileb, dwWaitResult;
	char buff[] = "\n->Gówno";
	//int wynik;
	cout << "SIEMA!" << endl;
	hFile = (HANDLE)argv[1];
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, argv[2]);
	if (hMutex == NULL)
	{
		cout << "Mutex error" << endl;
		return 1;
	}
	strcpy(buff, (char *)argv[3]);
	dwWaitResult = WaitForSingleObject(hMutex, INFINITE);
	if (dwWaitResult == WAIT_OBJECT_0)
	{
		cout << "Powinienem zapisac do pliku: " << buff << endl;
		WriteFile(hFile, buff, sizeof(buff), &ileb, NULL);
		
	}
	else if (dwWaitResult == WAIT_ABANDONED)
	{
		cout << "B³¹d, chuje!" << endl;
	}
	_getch();
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return 0;
}