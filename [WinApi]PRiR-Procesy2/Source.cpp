#include <iostream>
#include <Windows.h>
#include <process.h>
#include <sstream>
#include <tchar.h>
#include <conio.h>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "** THIS IS MAIN PROCESS **";
	//Process & File Vars
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES sap;
	ZeroMemory(&pi, sizeof(pi));
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&sap, sizeof(sap));
	si.cb = sizeof(si);
	sap.nLength = sizeof(sap);
	sap.bInheritHandle = TRUE;
	HANDLE hFile, hMutex;
	DWORD ile;

	stringstream cmdLine, primenums;
	string mutexName("mutex1");

	hFile = CreateFile("wyjscie.txt", FILE_ALL_ACCESS, 0, &sap, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hMutex = CreateMutex(NULL, FALSE, mutexName.c_str());
	if (hMutex == NULL)
	{
		cout << "Mutex error" << endl;
		return 1;
	}
	char napis[] = "Siema, co robicie?";
	int i = 0;
	WaitForSingleObject(hMutex, INFINITE);
	while (i++ < 50) //5 tyœ operacji chyba trochê potrwa
	{
		Sleep(5);
		//wynik += i * 2 + 123;
		cout << ".";
	}
	WriteFile(hFile, napis, sizeof(napis), &ile, NULL);
	ReleaseMutex(hMutex);
	cmdLine << "Child.exe " << (DWORD)hFile << " " << mutexName << " " << napis;

	if (!CreateProcess(NULL, (char*)cmdLine.str().c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "ERROR";
	}

	WaitForSingleObject(pi.hThread, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	_getch();
	return 0;
}