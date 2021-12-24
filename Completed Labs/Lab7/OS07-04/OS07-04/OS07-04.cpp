#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
    
    HANDLE hs = CreateSemaphore(NULL, 2, 3, L"Semaphore");

    LPCWSTR path1 = L".\\OS07-04A.exe";
    LPCWSTR path2 = L".\\OS07-04B.exe";

    STARTUPINFO si1, si2;

    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(STARTUPINFO)); 
    ZeroMemory(&si2, sizeof(STARTUPINFO));

    si1.cb = sizeof(STARTUPINFO); 
    si2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(path1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) {
        cout << "--Process OS07_04A created\n";
    }
    else {
        cout << "--Process OS07_04A not created\n";
    }

    if (CreateProcess(path2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
        cout << "--Process OS07_04B created\n";
    }
    else {
        cout << "--Process OS07_04B not created\n";
    }

    LONG prevcount = 0;

    for (int i = 1; i <= 90; i++) {
        if (i == 30) {
            WaitForSingleObject(hs, INFINITE);
        }
        if (i == 60) {
            ReleaseSemaphore(hs, 1, &prevcount);
        }

        cout <<" OS07_04 " << i << endl;
        Sleep(100);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);  
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(hs);

    CloseHandle(pi1.hProcess);  
    CloseHandle(pi2.hProcess);

    system("pause");
    return 0;
}