#include <iostream>
#include <windows.h>

int main() {
    DWORD pid = GetCurrentProcessId();
    DWORD tid = GetCurrentThreadId();

    for (int i = 0; i < 1'000; ++i) {
        std::cout << i << " " << "PID: " << pid << " TID: " << tid << std::endl;
        Sleep(1'000);
    }
    return 0;
}
