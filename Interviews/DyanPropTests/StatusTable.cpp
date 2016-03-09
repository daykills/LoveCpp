#include "StatusTable.h"

using namespace std;

namespace CppTest
{
	bool ComputedPropertySettingLock::_isLocked = false;
	ComputedPropertySettingLock::ComputedPropertySettingLock()
	{
		_isLocked = true;
	}
	ComputedPropertySettingLock::~ComputedPropertySettingLock()
	{
		_isLocked = false;
	}

	void StatusTable::startCollectDependentDP()
	{
		_tmpCollectedDP.clear();
		_startCollectDependentDP = true;		
	}

	void StatusTable::collectDynamicProperty(void* ptr_DP)
	{
		// haven't started collecting, do nothing.
		if (_startCollectDependentDP == false) return;
		_tmpCollectedDP.push_back(ptr_DP);
	}

	// set changed for all affected CP
	void StatusTable::dynamicPropertyChanged(void* ptr_DP)
	{
		unordered_map<void*, std::vector<void*> >::const_iterator got = _dynamicPropertyObservers.find(ptr_DP);
		if (got == _dynamicPropertyObservers.end())
		{
			// not found
			return;
		}
		for each (void* ptr_CP in got->second)
		{
			std::unordered_map<void*, bool>::iterator got_CP = _computedPropertyChanged.find(ptr_CP);
			if (got_CP != _computedPropertyChanged.end())
				got_CP->second = true;
		}
	}

	void StatusTable::endCollectDependentDP(void* ptr_CP)
	{
		_startCollectDependentDP = false;

		// update DP/CP binding
		for each (void* ptr_DP in _tmpCollectedDP)
		{
			unordered_map<void*, std::vector<void*> >::iterator got = _dynamicPropertyObservers.find(ptr_DP);
			if (got == _dynamicPropertyObservers.end())
			{
				// not found
				vector<void*> observers;
				got = (_dynamicPropertyObservers.emplace(ptr_DP, observers)).first;
			}
			got->second.push_back(ptr_CP);
		}
		_tmpCollectedDP.clear();
	}

	bool StatusTable::isComputedPropertyChanged(void* ptr_CP)
	{
		unordered_map<void*, bool>::const_iterator got = _computedPropertyChanged.find(ptr_CP);
		if (got == _computedPropertyChanged.end())
		{
			// not found. return false
			_computedPropertyChanged.emplace(ptr_CP, false);
			return false;
		}
		return got->second;
	}
}