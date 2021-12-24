#include <iostream>
#include <windows.h>
#define SLEEP_TIME 1'000

DWORD WINAPI OS04_02_T1()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 50; ++i) {
        std::cout << i <<"- PID: " << pid << " TID:" << tid << std::endl;
        Sleep(SLEEP_TIME);
    }
    return 0;
}
DWORD WINAPI OS04_02_T2()
{
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();
    for (int i = 0; i < 125; ++i) {
        std::cout << i <<"- PID: " << pid << " TID:" << tid << std::endl;
        Sleep(SLEEP_TIME);
    }
    return 0;
}

int main() {

    DWORD pid = GetCurrentProcessId();

    DWORD child1ID = NULL;
    DWORD child2ID = NULL;

    HANDLE hChild1 = CreateThread(NULL, 0 , (LPTHREAD_START_ROUTINE)OS04_02_T1,
                                  NULL, 0, &child1ID);
    HANDLE hChild2 = CreateThread(NULL, 0 , (LPTHREAD_START_ROUTINE)OS04_02_T2,
                                  NULL, 0, &child2ID);

    for (int i = 0; i < 100; ++i) {
        if( i == 20 )
        {
            SuspendThread(hChild1);
        }

        if( i == 40)
        {
            SuspendThread(hChild2);
        }

        if( i == 60)
        {
            ResumeThread(hChild1);
        }
        std::cout << i << "- PID: " << pid << std::endl;
        Sleep(SLEEP_TIME);
    }

    ResumeThread(hChild2);

    WaitForSingleObject(hChild1, INFINITE);
    WaitForSingleObject(hChild2, INFINITE);
    CloseHandle(hChild1);
    CloseHandle(hChild2);

    return 0;
}
