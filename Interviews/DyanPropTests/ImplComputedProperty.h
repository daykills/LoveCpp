#ifndef _IMPL_COMPUTED_PROPERTY_H
#define _IMPL_COMPUTED_PROPERTY_H

#include "IDynamicProperty.h"
#include <memory>

namespace CppTest
{
	/*
	* Implementation class dynamic property.
	*/
	template<typename T> class ImplComputedProperty : public virtual IDynamicProperty<T>
	{
	public:		
		ImplComputedProperty(std::function<T()> const & read,
			std::function<void(T)> const & write,
			std::function<bool(void*)> const & isValueChanged)
			:_read(read), _write(write), _isValueChanged(isValueChanged)
		{
			_value = _read();
		}
		T getValue() const override
		{
			return _value;
		}
		void setValue(T value) override
		{
			T tmpV = _value;
			_write(value);

			if (_isValueChanged((void*)this) == false) return;
			
			_value = _read();
			notifySubscribers(value);
		}
	private:
		T _value;
		std::function<T()> const _read;
		std::function<void(T)> const _write;
		std::function<bool(void*)> const _isValueChanged;
	};
}

#endif