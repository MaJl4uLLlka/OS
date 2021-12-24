#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
    
    HANDLE he = CreateEvent(NULL, TRUE, FALSE, L"Event");

    LPCWSTR path1 = L".\\OS07-05A.exe";
    LPCWSTR path2 = L".\\OS07-05B.exe";

    STARTUPINFO si1, si2;

    PROCESS_INFORMATION pi1, pi2;

    ZeroMemory(&si1, sizeof(STARTUPINFO)); 
    ZeroMemory(&si2, sizeof(STARTUPINFO));

    si1.cb = sizeof(STARTUPINFO); 
    si2.cb = sizeof(STARTUPINFO);

    if (CreateProcess(path1, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si1, &pi1)) {
        cout << "--Process OS07_05B created\n";
    }
    else {
        cout << "--Process OS07_05B not created\n";
    }

    if (CreateProcess(path2, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si2, &pi2)) {
        cout << "--Process OS07_05B created\n";
    }
    else {
        cout << "--Process OS07_05B not created\n";
    }

    LONG prevcount = 0;
    for (int i = 1; i <= 90; i++) {
        if (i == 15) {
            PulseEvent(he);
        }

        cout << " OS07_05 "<< i << endl;
        Sleep(100);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);  
    WaitForSingleObject(pi2.hProcess, INFINITE);

    CloseHandle(he);

    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);

    system("pause");
    return 0;
}