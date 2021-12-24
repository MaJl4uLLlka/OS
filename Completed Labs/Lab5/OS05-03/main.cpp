#include <iostream>
#include <windows.h>
#include <bitset>
#define PAUSE 200
#define COUNT 1'000'000
using namespace std;

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);
string getProcessorsNumbers(ULONG_PTR affinityMask);

DWORD WINAPI TA()
{
    HANDLE processHandle = GetCurrentProcess();
    HANDLE threadHandle = GetCurrentThread();
    DWORD_PTR processAffinityMask = NULL, systemAffinityMask = NULL, icpu = -1;

    for(int i =0; i < COUNT; ++i)
    {
        if(i % 1'000 == 0)
        {
            Sleep(200);
            cout << "*****" << i << "*****"<<endl;
            printProcessPrty(processHandle);
            printThreadPrty(threadHandle);

            try {
                if(!GetProcessAffinityMask(processHandle, &processAffinityMask, &systemAffinityMask))
                    throw "GetProcessAffinityMask";

                icpu = SetThreadIdealProcessor(threadHandle, MAXIMUM_PROCESSORS);
                cout << getProcessorsNumbers(processAffinityMask) << endl;
                cout << "Processor: " << dec << icpu <<endl;
            }
            catch (char* message) {
                std::cout << "Error: " << message << endl;
            }
        }
    }
    return 0;
}

int main(int argc, char* argv []) {
    DWORD mask, priority_process, thread1_priority, thread2_priority;

    try {
        if(argc == 5)
        {
            mask = atol(argv[1]);
            priority_process = atol(argv[2]);
            thread1_priority = atol(argv[3]);
            thread2_priority = atol(argv[4]);
        }
        else throw "Parameters: (affinity_mask, process_priority, thread1_priority, thread2_priority)";

        HANDLE handler = GetCurrentProcess();

        SetPriorityClass(handler, priority_process);

        if(!SetProcessAffinityMask(handler, mask))
        {
            throw "SetProcessAffinityMask";
        }

        HANDLE hChild1 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA),
                                      nullptr, CREATE_SUSPENDED, nullptr);

        HANDLE hChild2 = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(&TA),
                                      nullptr, CREATE_SUSPENDED, nullptr);

        SetThreadPriority(hChild1, thread1_priority);
        SetThreadPriority(hChild2, thread2_priority);

        ResumeThread(hChild1);
        ResumeThread(hChild2);

        WaitForSingleObject(hChild1, INFINITE);
        WaitForSingleObject(hChild2, INFINITE);
        CloseHandle(hChild1);
        CloseHandle(hChild2);

    }
    catch (const char* message) {
        std::cout << "Error: " << message << endl;
    }

    system("pause");
    return 0;
}


void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);
    cout << "---- Current PID: " << GetCurrentProcessId() << endl;
    switch (prty) {
        case IDLE_PRIORITY_CLASS:           cout << "----+ priority = IDLE_PRIORITY_CLASS" << endl;
            break;
        case BELOW_NORMAL_PRIORITY_CLASS:   cout << "----+ priority = BELOW_NORMAL_PRIORITY_CLASS" << endl;
            break;
        case NORMAL_PRIORITY_CLASS:         cout << "----+ priority = NORMAL_PRIORITY_CLASS" << endl;
            break;
        case ABOVE_NORMAL_PRIORITY_CLASS:   cout << "----+ priority = ABOVE_NORMAL_PRIORITY_CLASS" << endl;
            break;
        case HIGH_PRIORITY_CLASS:           cout << "----+ priority = HIGH_PRIORITY_CLASS" << endl;
            break;
        case REALTIME_PRIORITY_CLASS:       cout << "----+ priority = REALTIME_PRIORITY_CLASS" << endl;
            break;
        default:                            cout << "----+ priority = ?" << endl;
            break;
    }

    return;
}

void printThreadPrty(HANDLE h)
{
    int prty = GetThreadPriority(h);
    cout << "---- Current Thread ID: " << GetCurrentThreadId() << endl;
    switch (prty) {
        case THREAD_PRIORITY_LOWEST:        cout << "----+ priority = THREAD_PRIORITY_LOWEST" << endl;
            break;
        case THREAD_PRIORITY_BELOW_NORMAL:  cout << "----+ priority = THREAD_PRIORITY_BELOW_NORMAL" << endl;
            break;
        case THREAD_PRIORITY_NORMAL:        cout << "----+ priority = THREAD_PRIORITY_NORMAL" << endl;
            break;
        case THREAD_PRIORITY_ABOVE_NORMAL:  cout << "----+ priority = THREAD_PRIORITY_ABOVE_NORMAL" << endl;
            break;
        case THREAD_PRIORITY_HIGHEST:       cout << "----+ priority = THREAD_PRIORITY_HIGHEST" << endl;
            break;
        case THREAD_PRIORITY_IDLE:          cout << "----+ priority = THREAD_PRIORITY_IDLE" << endl;
            break;
        case THREAD_PRIORITY_TIME_CRITICAL: cout << "----+ priority = THREAD_PRIORITY_TIME_CRITICAL" << endl;
            break;
        default:           cout << "----+ priority = ?" << endl;
            break;
    }

    return;
}

string getProcessorsNumbers(ULONG_PTR affinityMask)
{
    string processors = "using processors: ";

    for (int i = 0; affinityMask != 0 ; ++i)
    {
        if(affinityMask & 0x1)
            processors += to_string(i) + " ";
        affinityMask = affinityMask >> 1;
    }
    return processors;
}