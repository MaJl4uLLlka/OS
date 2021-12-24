#include <iostream>
#include <Windows.h>
#include <intrin.h>
#include <bitset>

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);
int getProcessorsCount(DWORD_PTR affinityMask);
std::string getProcessorsNumbers(ULONG_PTR affinityMask);

int main() {
    HANDLE processHandle = GetCurrentProcess();
    HANDLE threadHandle  = GetCurrentThread();

    printProcessPrty(processHandle);
    printThreadPrty(threadHandle);

    try {
        DWORD_PTR processAffinityMask = NULL, systemAffinityMask = NULL;

        if(!GetProcessAffinityMask(processHandle, &processAffinityMask, &systemAffinityMask))
            throw "GetProcessAffinityMask";
        std::cout << "Process Affinity Mask: " <<std::showbase << std::bitset<8>(processAffinityMask) << std::endl;
        std::cout << "System Affinity  Mask: " <<std::showbase << std::bitset<8>(systemAffinityMask)  << std::endl;
        std::cout << "Processors Count:  " << getProcessorsCount(systemAffinityMask) << std::endl;
        std::cout << "Processor Numbers: " << getProcessorsNumbers(processAffinityMask) << std::endl;
    }
    catch (char* message) {
        std::cout << "Error: " << message << std::endl;
    }

    system("pause");
    return 0;
}

void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
    std::cout << "---- Current PID: " << GetCurrentProcessId() << std::endl;
    switch (prty) {
        case IDLE_PRIORITY_CLASS:           std::cout << "----+ priority = IDLE_PRIORITY_CLASS" << std::endl;
            break;
        case BELOW_NORMAL_PRIORITY_CLASS:   std::cout << "----+ priority = BELOW_NORMAL_PRIORITY_CLASS" << std::endl;
            break;
        case NORMAL_PRIORITY_CLASS:         std::cout << "----+ priority = NORMAL_PRIORITY_CLASS" << std::endl;
            break;
        case ABOVE_NORMAL_PRIORITY_CLASS:   std::cout << "----+ priority = ABOVE_NORMAL_PRIORITY_CLASS" << std::endl;
            break;
        case HIGH_PRIORITY_CLASS:           std::cout << "----+ priority = HIGH_PRIORITY_CLASS" << std::endl;
            break;
        case REALTIME_PRIORITY_CLASS:       std::cout << "----+ priority = REALTIME_PRIORITY_CLASS" << std::endl;
            break;
        default:                            std::cout << "----+ priority = ?" << std::endl;
            break;
    }

    return;
}

void printThreadPrty(HANDLE h)
{
    int prty = GetThreadPriority(h);
    std::cout << "---- Current Thread ID: " << GetCurrentThreadId() << std::endl;
    switch (prty) {
        case THREAD_PRIORITY_LOWEST:        std::cout << "----+ priority = THREAD_PRIORITY_LOWEST" << std::endl;
            break;
        case THREAD_PRIORITY_BELOW_NORMAL:  std::cout << "----+ priority = THREAD_PRIORITY_BELOW_NORMAL" << std::endl;
            break;
        case THREAD_PRIORITY_NORMAL:        std::cout << "----+ priority = THREAD_PRIORITY_NORMAL" << std::endl;
            break;
        case THREAD_PRIORITY_ABOVE_NORMAL:  std::cout << "----+ priority = THREAD_PRIORITY_ABOVE_NORMAL" << std::endl;
            break;
        case THREAD_PRIORITY_HIGHEST:       std::cout << "----+ priority = THREAD_PRIORITY_HIGHEST" << std::endl;
            break;
        case THREAD_PRIORITY_IDLE:          std::cout << "----+ priority = THREAD_PRIORITY_IDLE" << std::endl;
            break;
        case THREAD_PRIORITY_TIME_CRITICAL: std::cout << "----+ priority = THREAD_PRIORITY_TIME_CRITICAL" << std::endl;
            break;
        default:           std::cout << "----+ priority = ?" << std::endl;
            break;
    }

    return;
}

int getProcessorsCount(DWORD_PTR affinityMask)
{
    int counter = 0;

    while (affinityMask != 0) {
        if(affinityMask & 0x1)
            ++counter;
        affinityMask = affinityMask >> 1;
    }
    return counter;
}

std::string getProcessorsNumbers(ULONG_PTR affinityMask)
{
    std::string processors = "using processors: ";

    for (int i = 0; affinityMask != 0; ++i)
    {
        if(affinityMask & 0x1)
            processors += std::to_string(i) + " ";
        affinityMask = affinityMask >> 1;
    }
    return processors;
}