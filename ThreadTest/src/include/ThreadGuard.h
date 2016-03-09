#pragma once

#include <thread>
#include <iostream>

namespace ThreadTest
{
	class ThreadGuard
	{
	public:
		explicit ThreadGuard(std::thread t, bool isDetached = false) : m_thread(std::move(t)), m_isDetached(isDetached)
		{
			std::cout << "Enter ThreadGuard" << std::endl;
			if (m_thread.joinable() == false)
				throw std::logic_error("No thread");
		}
		explicit ThreadGuard(std::thread t)
		{
			ThreadGuard(std::move(t), false);
		}
		~ThreadGuard()
		{
			std::cout << "Exit ThreadGuard" << std::endl;
			if (m_isDetached)
				m_thread.detach();
			else
				m_thread.join();
		}
	private:
		ThreadGuard(ThreadGuard const & other) {}
    ThreadGuard& operator=(const ThreadGuard &) { return *this; }
		std::thread m_thread;
		bool m_isDetached;
	};
}