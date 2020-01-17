#pragma once

#include <chrono>
#include <string>
#include <iostream>

class HronoTimer
{
private:
	std::chrono::steady_clock::time_point start;
public:
	HronoTimer(std::string str);
	~HronoTimer();
};
