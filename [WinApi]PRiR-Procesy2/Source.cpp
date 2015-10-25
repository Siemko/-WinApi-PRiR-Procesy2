#include <iostream>
#include <Windows.h>
#include <process.h>
#include <sstream>
#include <tchar.h>
#include <conio.h>
using namespace std;
HANDLE hFile, hMutex;
int _tmain(int argc, char* argv[])
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

	DWORD ile;

	stringstream cmdLine, primenums;
	char mutexName[] = "mutex1";
	char plik[] = "wyjscie.txt";
	hFile = CreateFile(plik, FILE_ALL_ACCESS, 0, &sap, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	hMutex = CreateMutex(NULL, FALSE, mutexName);
	if (hMutex == NULL)
	{
		cout << "Mutex error" << endl;
		return 1;
	}
	char napis[] = "Siema, co robicie?";
	int i = 0;
	WaitForSingleObject(hMutex, INFINITE);
	while (i++ < 50) //5 ty� operacji chyba troch� potrwa
	{
		Sleep(5);
		//wynik += i * 2 + 123;
		cout << ".";
	}
	WriteFile(hFile, napis, strlen(napis), &ile, NULL);
	//ReleaseMutex(hMutex);
	cmdLine << "Child.exe " << reinterpret_cast<std::size_t>(hFile) << " " << mutexName << " " << napis;

	if (!CreateProcess(NULL, (char*)cmdLine.str().c_str(), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		cout << "ERROR";
	}
	Sleep(10000);
	ReleaseMutex(hMutex);
	WaitForSingleObject(pi.hThread, INFINITE);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	_getch();
	return 0;
}