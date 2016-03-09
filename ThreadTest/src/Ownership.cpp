#pragma once

#include <chrono>
#include <iostream>
#include <cassert>
#include <memory>
#include <thread>

#include "ThreadGuard.h"

namespace ThreadTest
{
	static void SayHello()
	{
		std::cout << "Hello" << std::endl;
	}

	static void SayHi()
	{
		std::cout << "Hi" << std::endl;
	}

	static void Test()
	{
		std::thread t(SayHello);
		std::thread t1 = std::move(t);
		assert(t.joinable() == false);
		t1.join();

		ThreadTest::ThreadGuard q(std::thread(SayHi), true);

		//std::thread s(Hi);		
		//q = std::move(s);	// can't move to a thread that owns another thread.

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
