#include <iostream>
#include <Windows.h>
using namespace std;

void sh(HANDLE heap);

int main()
{
    setlocale(LC_ALL, "rus");
    HANDLE heap = GetProcessHeap();

    cout << "*************BEFORE****************" << endl;
    sh(heap);

    int size = 300000;
    int* m = new int[size];

    cout << "Размер массива в байтах: " << sizeof(int) * size << endl << endl;

    cout << "*************AFTER****************" << std::endl;
    sh(heap);

    delete[] m;

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
        if(phe.wFlags & PROCESS_HEAP_ENTRY_BUSY) allocated_area_size += phe.cbData; // распределенная память
    }

    cout << "Общий размер heap: " << total_memory << endl
        << "Размер нераспределенной области памяти heap: " << unallocated_area_size << endl
        << "Размер распределенной области памяти heap: " << allocated_area_size << endl << endl;
}