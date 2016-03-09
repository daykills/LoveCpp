#ifndef _STATUS_TABLE_H
#define _STATUS_TABLE_H

#include <memory>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <atomic>
#include <mutex>
#include <boost/signals2/signal.hpp>

namespace CppTest
{
	class ComputedPropertySettingLock
	{
	private:
		static bool _isLocked;
	public:
		ComputedPropertySettingLock();
		~ComputedPropertySettingLock();
	};

	class StatusTable
	{
	public:
		// singleton
		static StatusTable& getInstance()
		{
			static StatusTable instance;
			return instance;
		}
		// start collect dependent dynamic properties
		void startCollectDependentDP();
		// end collect dependent DP, and update binding
		void endCollectDependentDP(void* ptr_CP);
		// 
		bool isComputedPropertyChanged(void* ptr_CP);		
		// add ptr_DP to the _DPObservers
		void collectDynamicProperty(void* ptr_DP);
		// set changed for all affected CP
		void dynamicPropertyChanged(void* ptr_DP);

	private:
		StatusTable()
		{
			_startCollectDependentDP = false;
		}
		bool _startCollectDependentDP;
		typedef std::unordered_map<void*, std::vector<void*> > ObserverLookupTable;
		// key = ptr to computed computed property value = whether its dependence changed
		std::unordered_map<void*, bool> _computedPropertyChanged;
		// key = ptr_dynamic_property; value = computed properties affected by it
		ObserverLookupTable _dynamicPropertyObservers;
		std::vector<void*> _tmpCollectedDP;
		
		// singleton
		StatusTable(StatusTable const&);    // Don't Implement.
		void operator=(StatusTable const&); // Don't implement
	};
}

#endif