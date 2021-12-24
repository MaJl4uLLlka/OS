#include <iostream>
#include <ctime>
#include <Windows.h>

#define SECOND 10000000

int count = 0;

PTIMERAPCROUTINE CALLBACK callback(LPVOID lpArgToCompletionRoutine, DWORD dwTimerLowValue, DWORD dwTimerHighValue)
{
	count = ++count;
	return NULL;
}

int main()
{
	HANDLE htimer = CreateWaitableTimer(NULL, FALSE, NULL);
	long long it = -0 * SECOND;
	clock_t start = clock();

	LPVOID lpArgToCompletionRoutine = NULL;
	DWORD dwTimerLowValue = NULL, dwTimerHighValue = NULL;

	for (int i = 0; ; ++i)
	{
		if (!SetWaitableTimer(htimer, (LARGE_INTEGER*)&it, 3000, callback(lpArgToCompletionRoutine, dwTimerLowValue, dwTimerHighValue), NULL, FALSE))
		{
			std::cout << "Error SetWaitableTimer" << std::endl;
			break;
		}

		if ((((clock() - start) != 0) && (clock() - start) % 3000 == 0)) 
		{
			std::cout << "iterations " << count << ", time - " << clock() - start << '\n';
		}

		if ((clock() - start) / CLOCKS_PER_SEC == 15)
		{
			std::cout << "15 s, iteration: " << count << std::endl;
			break;
		}

		WaitForSingleObject(htimer, INFINITE);
	}

	system("pause");
    return 0;
}