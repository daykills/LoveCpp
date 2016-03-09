#ifndef _DYNAMIC_PROPERTY_H
#define _DYNAMIC_PROPERTY_H

#include "IDynamicProperty.h"
#include <memory>
#include <unordered_map>
#include <vector>
#include <boost/signals2/signal.hpp>
#include <functional>

#include "ImplDynamicProperty.h"
#include "ImplComputedProperty.h"
#include "StatusTable.h"

namespace CppTest
{
	/*
	 * Factory class for constructing instances of your implementation.
	 * The unit tests use these methods
	 */
	struct DynamicProperty
	{
		/*
		 * Allocates an IDynamicProperty<T> instance that has the provided initialValue as its value
		 */
		template<typename T> static IDynamicProperty<T> *create(T const & initialValue)
		{
			// return new ???;
			// throw std::exception();
			ImplDynamicProperty<T>* dp = new ImplDynamicProperty<T>(initialValue);

			std::function<void(void*)> getValueCallback = [](void* ptr){StatusTable::getInstance().collectDynamicProperty(ptr); };
			dp->subscribeGetValue(getValueCallback);

			std::function<void(void*)> setValueCallback = [](void* ptr){StatusTable::getInstance().collectDynamicProperty(ptr); };
			dp->subscribeGetValue(setValueCallback);

			return dp;
			//return new ImplDynamicProperty<T>(initialValue);
		}

		/*
		 * Allocated an IDynamicProperty<T> instance whose value is determined by running the "read" function.
		 * We call this type of IDynamicProperty a "calculated property".
		 *
		 * During construction, the "read" function should be called once to determine the initial value
		 * of this calculated property.  If the "read" function calls "getValue" on any other IDynamicProperty instances,
		 * a subscription should be setup to those instances.  Whenever any of those instances change, the "read" function
		 * should be invoked again to calculate the new value of this calculated property.  Once the new value is
		 * calculated, all subscribers should be notified of the new value.
		 *
		 * Whenever "setValue" is called, the provided "write" function should be invoked.  Note this does not necessarily mean
		 * the value of this calculated property will change or that subscriber notifications should be sent.  Thus "setValue"
		 * should not actually notify subscribers.  Only when the "read" function gets invoked to determine a new value
		 * should subscribers be notified.
		 *
		 * read - function used to calculate the value.  Will be invoked once during construction and then again anytime any
		 * dependent dynamic properties are modified.
		 * write - function used when client code attempts to set the value of this calculated property.  Write function can do
		 * anything it wants.  But most likely it will write to a dynamic property that the "read" function reads from.
		 */
		template<typename T> static IDynamicProperty<T> *create(std::function<T()> const & read, std::function<void(T)> const & write)
		{
			// return new ???;
			// throw std::exception();
			
			StatusTable::getInstance().startCollectDependentDP();

			std::function<bool(void*)> isValueChangedCallback = [](void* ptr) -> bool{ return StatusTable::getInstance().isComputedPropertyChanged(ptr); };

			IDynamicProperty<T>* cp = new ImplComputedProperty<T>(read, write, isValueChangedCallback);

			StatusTable::getInstance().endCollectDependentDP(cp);

			return cp;
			//return new ImplComputedProperty<T>(read, write);
		}
	};
}

#endif
