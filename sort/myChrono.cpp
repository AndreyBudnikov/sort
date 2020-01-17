#include "myChrono.h"

HronoTimer::HronoTimer(std::string str)
{
	start = std::chrono::high_resolution_clock::now();
	std::cout << std::endl << "START - " << str << std::endl;
}
HronoTimer::~HronoTimer()
{
	std::cout << "STOP - Time Elapsed " << std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() << std::endl;
}

