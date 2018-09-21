// ThreadTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
using namespace std;

condition_variable cond_var;
mutex m;

int main() {
	int value = 100;
	bool notified = false;
	thread reporter([&]() {
		
		unique_lock<mutex> lock(m);
		cond_var.wait(lock);
		
		cout << "The value is " << value << endl;
	});

	thread assigner([&]() {
		value = 20;		
		notified = true;
		cond_var.notify_one();		
	});

	reporter.join();
	assigner.join();
	return 0;
}