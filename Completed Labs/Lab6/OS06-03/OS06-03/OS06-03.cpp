#include <iostream>
#include <Windows.h>
#define KB (1024)
#define PG (4 * KB)

int main()
{
    //K = CA
    //а = E0
    //н = ED
    // page = CA = 202
    //offset = E0E = 3598
    //адрес =  202 * PG + 3598 = CAE0E= 830990
    //xmeaddr -> потом + aдрес

    int pages = 256;
    int arraySize = pages * PG / sizeof(int);

    LPVOID xmeaddr = VirtualAlloc(NULL, pages * PG, MEM_COMMIT, PAGE_READWRITE);

    int* arr = new (xmeaddr) int[arraySize];

    for (int i = 0; i < arraySize; i++)
    {
        arr[i] = i;
    }

    getchar();

    VirtualFree(xmeaddr, NULL, MEM_RELEASE) ?
        std::cout << "VirtualFree released\n" : std::cout << "VirtualFree not released\n";

    system("pause");
}
