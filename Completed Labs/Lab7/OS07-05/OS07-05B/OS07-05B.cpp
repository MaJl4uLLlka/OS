#include <Windows.h>
#include <iostream>

using namespace std;

int main() {

    HANDLE he = OpenEvent(EVENT_ALL_ACCESS, FALSE, L"Event");

    he == NULL ? cout << "OS07_05B: Open Error Event\n" : cout << "OS07_05B: Open Event\n";

    WaitForSingleObject(he, INFINITE);
    for (int i = 1; i <= 90; i++) {
        cout << " OS07_05B " << i << endl;
        Sleep(100);
    }

    CloseHandle(he);

    system("pause");
    return 0;
}