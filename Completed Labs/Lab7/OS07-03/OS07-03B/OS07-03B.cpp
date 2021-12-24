#include <Windows.h>
#include <iostream>

using namespace std;

int main() {

    HANDLE hm = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");

    hm == NULL ? cout << "OS07_03B: Open Error Mutex\n" : cout << "OS07_03B: Open Mutex\n";

    for (int i = 1; i <= 90; i++) {
        if (i == 30) {
            WaitForSingleObject(hm, INFINITE);
        }
        if (i == 60) {
            ReleaseMutex(hm);
        }

        cout << "OS07-03B " << i << endl;
        Sleep(100);
    }

    CloseHandle(hm);

    system("pause");
}