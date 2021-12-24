#include <iostream>
#include <Windows.h>

int main() {
    for (int i = 0; i < 10'000; ++i) {
        std::cout << "PID: " << GetCurrentProcessId() << std::endl;
        Sleep(1'000);
    }
    return 0;
}
