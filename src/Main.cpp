// LeetCodeTest.cpp : Defines the entry point for the console application.
//

#include "Common.h"

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define DIR tests/LC
#define TEST_NAME CanPartitionKSubsets
#include STR(DIR/TEST_NAME.h)

#include <iostream>
#include <memory>
#include <chrono>

int main(int argc, char* argv[])
{
	auto begin = chrono::high_resolution_clock::now();
	// code to benchmark
    TEST_NAME::Test();
    std::cout << "Total time lapsed: " << chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - begin).count() * 0.001 << "ms" << std::endl;
	return 0;
}
