#pragma once

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "ThreadGuard.h"

namespace ThreadTest
{
	static void SayHello()
	{
		std::cout << "Hello" << std::endl;
	}

	static void Test()
	{
		auto hardwareThreads = std::thread::hardware_concurrency();
		std::cout << "hardware concurrency: " << hardwareThreads << std::endl;
		std::cout << "Before thread guard" << std::endl;
		ThreadTest::ThreadGuard g(std::thread(SayHello), true);
		std::cout << "After thread guard" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
}
