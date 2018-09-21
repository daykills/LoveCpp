#pragma once
/*

*/

#include <iostream>
#include <climits>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

namespace TestOnly
{
	class PhoneNumberSolver
	{
	public:
		PhoneNumberSolver(const string& filename = "") : m_filename(filename)
		{
		}
		// read parameters from stdin or file
		void readParameters()
		{
			// no op for istream init
			struct noop
			{
				void operator()(...) const {}
			};
			// choose input between stdin and file stream
			shared_ptr<istream> input;
			if (m_filename.empty())
				input.reset(&cin, noop());
			else
				input.reset(new ifstream(m_filename), [](std::ifstream* ptr) { ptr->close(); });

			int rowReadCount = 0;
			while (true)
			{
				std::string line;
				getline(*input, line);
				if (line.empty()) break;
			}
		}

	private:
		// fields
		string m_filename;
	};

	void Test()
	{
	}
}