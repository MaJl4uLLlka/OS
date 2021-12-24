#include <iostream>
#include <windows.h>
using namespace std;

void printProcessPrty(HANDLE h);
void printThreadPrty(HANDLE h);
string getProcessorsNumbers(ULONG_PTR affinityMask);

int main() {
    HANDLE processHandle = GetCurrentProcess();
    HANDLE threadHandle  = GetCurrentThread();

    DWORD_PTR processAffinityMask = NULL, systemAffinityMask = NULL, icpu = -1;


    for(int i=0; i< 1'000'000; i++)
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
                cout << "Processor: " << dec <<icpu <<endl;
            }
            catch (char* message) {
                std::cout << "Error: " << message << endl;
            }
        }
    }
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