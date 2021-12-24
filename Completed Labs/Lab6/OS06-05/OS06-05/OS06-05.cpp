#include <iostream>
#include <Windows.h>
using namespace std;
#define KB 1024
#define MB 1024 * KB

void sh(HANDLE heap);

int main()
{
    setlocale(LC_ALL, "rus");
    HANDLE heap = HeapCreate(HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 4 * MB, 4 * 0 * MB);

    cout << "*************BEFORE****************" << endl;
    sh(heap);

    int size = 300000;
    int* m =  (int*)HeapAlloc(heap, HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, size * sizeof(int));

    cout << hex << m;
    cout << dec;
    cout << "Размер массива в байтах: " << dec << sizeof(int) * size << endl << endl;

    cout << "*************AFTER****************" << std::endl;
    sh(heap);

    HeapFree(heap, HEAP_NO_SERIALIZE, m);
    sh(heap);

    HeapDestroy(heap);

    system("pause");
}

void sh(HANDLE heap)
{
    PROCESS_HEAP_ENTRY phe;
    phe.lpData = NULL;
    int total_memory = 0,
        unallocated_area_size = 0,  //нераспределенная область
        allocated_area_size = 0;    //распределенная область

    while (HeapWalk(heap, &phe))
    {
        total_memory += phe.cbData;
        if (phe.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) unallocated_area_size += phe.cbData; // нераспределенная область
        if (phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) allocated_area_size += phe.cbData; // распределенная память
    }

    cout << "Общий размер heap: " << total_memory << endl
        << "Размер нераспределенной области памяти heap: " << unallocated_area_size << endl
        << "Размер распределенной области памяти heap: " << allocated_area_size << endl << endl;
}