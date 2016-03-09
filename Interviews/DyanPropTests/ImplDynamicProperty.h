#ifndef _IMPL_DYNAMIC_PROPERTY_H
#define _IMPL_DYNAMIC_PROPERTY_H

#include <memory>
#include <functional>
#include <boost/signals2/signal.hpp>
#include "IDynamicProperty.h"

namespace CppTest
{
	/*
	* Implementation class dynamic property.
	*/
	template<typename T> class ImplDynamicProperty : public virtual IDynamicProperty<T>
	{
	public:
		ImplDynamicProperty(T value) : _value(value)
		{
		}
		T getValue() const override
		{
			if (!_signalGetValue.empty())
				_signalGetValue((void*)this);

			return _value;
		}
		void setValue(T value) override
		{
			if (value == _value) return;

			_value = value;

			if (!_signalSetValue.empty())
				_signalSetValue((void*)this);

			notifySubscribers(value);
		}
		void subscribeGetValue(const std::function<void(void*)> & callback)
		{
			_signalGetValue.connect(callback);			
		}
		void subscribeSetValue(const std::function<void(void*)> & callback)
		{
			_signalSetValue.connect(callback);
		}
	typedef ImplDynamicProperty<T> type;
	private:
		T _value;

		boost::signals2::signal<void(void*)> _signalGetValue;
		boost::signals2::signal<void(void*)> _signalSetValue;
	};
}

#endif