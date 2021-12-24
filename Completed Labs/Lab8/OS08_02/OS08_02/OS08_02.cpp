#include <iostream>
#include <ctime>

int main()
{
	clock_t start = clock();
	bool passed_five_seconds = false, passed_ten_seconds = false;
	for (int i = 1; ; ++i)
	{
		if ((clock() - start) / CLOCKS_PER_SEC == 5 && !passed_five_seconds)
		{
			std::cout << "5 s : " << i << std::endl;
			passed_five_seconds = true;
		}
		else if ((clock() - start) / CLOCKS_PER_SEC == 10 && !passed_ten_seconds)
		{
			std::cout << "10 s : " << i << std::endl;
			passed_ten_seconds = true;
		}
		else if ((clock() - start) / CLOCKS_PER_SEC == 15)
		{
			std::cout << "15 s : " << i << std::endl;
			break;
		}
	}
	
	return 0;
}