// LeetCodeTest.cpp : Defines the entry point for the console application.
//
#include <iostream> 
#include <memory> 
#include <chrono>
#include "Common.h"
#include "Academic.h"
#include "LC.h"
#include "Real.h"
#include "Hackerrank.h"
#include "IOTemplate.h"

using namespace std;

int main(int argc, char* argv[])
{
	auto begin = chrono::high_resolution_clock::now();

	// code to benchmark
    FindDuplicateInMatrix::Test();

	std::cout << "Total time lapsed: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - begin).count() << "ms" << std::endl;
	return 0;
}
