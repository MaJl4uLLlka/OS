#include <iostream>
#include "windows.h"
#include <direct.h>

std::string current_working_directory()
{
    char* cwd = _getcwd( 0, 0 ) ;
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
}

int main() {
    std::string path = current_working_directory();

    std::string OS03_02_1_path = path + "\\OS03-02-1\\OS03-02-1.exe";
    std::string OS03_02_2_path = path + "\\OS03-02-2\\OS03-02-2.exe";

    LPCSTR pr1Path = OS03_02_1_path.c_str();
    LPCSTR pr2Path = OS03_02_2_path.c_str();

    STARTUPINFO cif1;
    STARTUPINFO cif2;
    PROCESS_INFORMATION pi1;
    PROCESS_INFORMATION pi2;

    ZeroMemory(&cif1 , sizeof(STARTUPINFO));  cif1.cb = sizeof(STARTUPINFO);
    ZeroMemory(&cif2 , sizeof(STARTUPINFO));  cif2.cb = sizeof(STARTUPINFO);

    if(CreateProcess(pr1Path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE,NULL, NULL, &cif1, &pi1)){
        std::cout << "Process os03-02-1 created" << std::endl;
    }
    else
    {
        std::cout << "Not created process os03-02-1" << std::endl;
    }

    if(CreateProcess(pr2Path, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &cif2, &pi2)){
        std::cout << "Process OS03_02_2 created" << std::endl;
    } else{
        std::cout << "Not created process os03_02_2" << std::endl;
    }

    for (int i = 0; i < 100; ++i) {
        std::cout << "PID: " << GetCurrentProcessId() << std::endl;
        Sleep(1'000);
    }

    WaitForSingleObject(pi1.hProcess, INFINITE);
    WaitForSingleObject(pi2.hProcess, INFINITE);
    CloseHandle(pi1.hProcess);
    CloseHandle(pi2.hProcess);
    return 0;
}
