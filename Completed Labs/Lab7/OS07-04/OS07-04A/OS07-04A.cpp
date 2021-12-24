#include <Windows.h>
#include <iostream>

using namespace std;

int main() {
    
    HANDLE hs = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"Semaphore");

    hs == NULL ? cout << "OS07_04A: Open Error Semaphore\n" : cout << "OS07_04A: Open Semaphore\n";

    for (int i = 1; i <= 90; i++) {
        if (i == 30) {
            WaitForSingleObject(hs, INFINITE);
        }
        if (i == 60) {
            ReleaseMutex(hs);
        }

        cout <<" OS07_04A "<< i << endl;
        Sleep(100);
    }

    CloseHandle(hs);

    system("pause");
    return 0;
}