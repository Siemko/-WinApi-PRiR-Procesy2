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
	HANDLE hStdin, hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	//stringstream ss(argv[1]);
	//UINT_PTR iFile;
	//ss >> iFile;
	hFile = (HANDLE)atoi(argv[1]);
	DWORD ileb;
	char napis2[] = " - Gowno";
	//int wynik;
	cout << "SIEMA! Poczekaj 10 sekund na mutexa od procesu main, okej?" << endl;
	
	hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, argv[2]);
	if (hMutex == NULL)
	{
		cout << "Mutex error" << endl;
		_getch();
	}
	WaitForSingleObject(hMutex, INFINITE);
	cout << "Powinienem zapisac do pliku: " << napis2 << endl;
	if (!WriteFile(hFile, napis2, strlen(napis2), &ileb, NULL))
		cout << "Ale nie zapisa³em, bo ERROR NAMBER: " << GetLastError() << endl;
	else
		cout << "I zapisa³em...";
	Sleep(500);
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
	return 0;
}