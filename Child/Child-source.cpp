#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;
HANDLE hFile, hMutex;

int _tmain(int argc, char* argv[])
{
	stringstream ss(argv[1]);
	UINT_PTR iFile;
	ss >> iFile;
	HANDLE hFile = reinterpret_cast<HANDLE>(iFile);
	DWORD ileb;
	char napis2[] = "\nGowno";
	//int wynik;
	cout << "SIEMA!" << endl;
	
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, (LPWSTR)argv[2]);
	if (hMutex == NULL)
	{
		cout << "Mutex error" << endl;
		return 1;
	}
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Powinienem zapisac do pliku: " << napis2 << endl;
	if(!WriteFile(hFile, napis2, strlen(napis2), &ileb, NULL))
		cout << "Ale nie zapisa³em, bo ERROR NAMBER: " <<GetLastError() <<endl;
	_getch();
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return 0;
}