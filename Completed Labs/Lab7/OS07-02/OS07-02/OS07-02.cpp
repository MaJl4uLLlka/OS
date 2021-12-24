#include <iostream>
#include <Windows.h>
using namespace std;

DWORD WINAPI A();
DWORD WINAPI B();

CRITICAL_SECTION cs;

int main()
{
	InitializeCriticalSection(&cs);

	DWORD A_ID = NULL, B_ID = NULL;
	HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)A, NULL, 0, &A_ID);
	HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)B, NULL, 0, &B_ID);

	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		cout << "main " << i << endl;
		Sleep(100);
	}

	WaitForSingleObject(hA, INFINITY);
	WaitForSingleObject(hB, INFINITY);
	
	DeleteCriticalSection(&cs);

	CloseHandle(hA);
	CloseHandle(hB);


	return 0;
}

DWORD WINAPI A()
{
	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		cout << "A " << i << endl;
		Sleep(100);
	}

	return 0;
}

DWORD WINAPI B()
{
	for (int i = 1; i <= 90; i++)
	{
		if (i == 30)
		{
			EnterCriticalSection(&cs);
		}

		if (i == 60)
		{
			LeaveCriticalSection(&cs);
		}

		cout << "B " << i << endl;
		Sleep(100);
	}

	return 0;
}
