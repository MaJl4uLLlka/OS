#include <iostream>
#include <Windows.h>
#include <ctime>

int main() {
    time_t t;
    t = time(&t);

    tm ttm;

    localtime_s(&ttm, &t); // локальное время

    //localtime in format <dd.mm.yyyy hh:min:sec>
    if (ttm.tm_mday < 10)
    {
        std::cout << '0';
    }
    std::cout << ttm.tm_mday;
    std::cout << '.';
    
    if (ttm.tm_mon + 1 < 10)
    {
        std::cout << '0';
    }
    std::cout << ttm.tm_mon + 1;
    std::cout << '.';
    std::cout << 1900 + ttm.tm_year;
    std::cout << " ";

    if (ttm.tm_hour < 10)
    {
        std::cout << '0';
    }
    std::cout << ttm.tm_hour;
    std::cout << ":";

    if (ttm.tm_min < 10)
    {
        std::cout << '0';
    }
    std::cout << ttm.tm_min;
    std::cout << ":";

    if (ttm.tm_sec < 10)
    {
        std::cout << '0';
    }
    std::cout << ttm.tm_sec << std::endl;

    system("pause");
    return 0;
}
