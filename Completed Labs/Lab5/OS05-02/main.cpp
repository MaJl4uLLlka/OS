#include <iostream>
#include <windows.h>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) {
    DWORD affinityMask;
    DWORD process1Priority;
    DWORD process2Priority;
    try {
        if(argc == 4) {
            affinityMask = atol(argv[1]);
            process1Priority = atol(argv[2]);
            process2Priority = atol(argv[3]);

            cout << "Affinity Mask:" << affinityMask << endl;
            cout << "Process1 Priority: " << process1Priority << endl;
            cout << "Process2 Priority: " << process2Priority << endl;
        }
        else throw "Needed Parameters: (mask, process1Priority, process2Priority )";

        string path = "D:\\3ks1\\OS\\Completed Labs\\Lab5\\OS05-02\\OS05_02x.exe";
        string path2 = "D:\\3ks1\\OS\\Completed Labs\\Lab5\\OS05-02\\OS05_02x.exe";

        LPCSTR OS05_02_1 = path.c_str();
        LPCSTR OS05_02_2 = path2.c_str();

        STARTUPINFO cif1;
        STARTUPINFO cif2;

        PROCESS_INFORMATION pi1;
        PROCESS_INFORMATION pi2;

        HANDLE mainProcessHandler = GetCurrentProcess();

        ZeroMemory(&cif1, sizeof(STARTUPINFO)); cif1.cb = sizeof(STARTUPINFO);
        ZeroMemory(&cif2, sizeof(STARTUPINFO)); cif2.cb = sizeof(STARTUPINFO);

        if(!SetProcessAffinityMask(mainProcessHandler, affinityMask))
            throw "SetAffinityMask";

        ULONG_PTR processAffinityMask;
        ULONG_PTR systemAffinityMask;
        bool success = GetProcessAffinityMask(mainProcessHandler, &processAffinityMask, &systemAffinityMask);
        if(success){
            std::cout << "process mask: " << showbase << bitset<8>(processAffinityMask) << std::endl;
        }

        if(!CreateProcess(OS05_02_1, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE|process1Priority, nullptr,
                          nullptr,&cif1, &pi1 ))
        {
            throw "CreateProcess 1";
        }

        if(!CreateProcess(OS05_02_2, nullptr, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE|process2Priority, nullptr,
                              nullptr,&cif2, &pi2 ))
        {
            throw "CreateProcess 2";
        }

        WaitForSingleObject(pi1.hProcess, INFINITE);
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi2.hProcess);
    }
    catch (const char* message) {
        cout<< "Error: " << message << endl;
    }

    system("pause");
    return 0;
}
