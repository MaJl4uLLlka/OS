#include <iostream>
#include <windows.h>

using namespace std;

DWORD WINAPI A();
DWORD WINAPI B();

void EnterCriticalSection();
void LeaveCriticalSection();

int check = 0;

int main() {
    DWORD A_ID = NULL, B_ID = NULL;
    HANDLE hA = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)A, NULL, 0, &A_ID);
    HANDLE hB = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)B, NULL, 0, &B_ID);

    WaitForSingleObject(hA, INFINITE);
    WaitForSingleObject(hB, INFINITE);
    CloseHandle(hA);
    CloseHandle(hB);

    system("pause");

    return 0;
}

DWORD WINAPI A()
{
    EnterCriticalSection();

    for (int i = 0; i < 5; ++i) 
    {
        cout << "A: "<< i << " , check: " << check << endl;
    }
    LeaveCriticalSection();

    return 0;
}

DWORD WINAPI B()
{
    Sleep(15);
    EnterCriticalSection();
    for (int i = 0; i < 5; ++i) 
    {
        cout << "B: " << i << " , check: "<< check << endl;
    }
    LeaveCriticalSection();

    return 0;
}

void EnterCriticalSection() {
    //Префикс lock, помещенный перед командой, устанавливает сигнал
    //  на линии LOCK системной шины и запрещает доступ к шине другим
    //  процессорам на время выполнения данной команды.
    //  
    //Команда BTS сохраняет значение бита, из первого операнда 
    //со смещением, указанным вторым операндом, во флаге CF,
    //а затем устанавливает этот бит в 1.
    _asm {
    CriticalSection:
        lock bts check, 0; 
        js CriticalSection
    }
}

void LeaveCriticalSection() {
    _asm lock btr check, 0
}

