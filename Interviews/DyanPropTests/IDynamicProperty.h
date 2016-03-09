#ifndef _IDYNAMIC_PROPERTY_H
#define _IDYNAMIC_PROPERTY_H

#include <functional>
#include <boost/signals2/signal.hpp>

namespace CppTest
{
    /*
     * A property that can change values over time.
     * Change notifications can be observed via a Boost::Signals2::Signal
     */
    template<typename T> class IDynamicProperty
    {
        public:
            /*
             * Gets the value of the property
             */
            virtual T getValue() const = 0;

            /*
             * Sets the value of the property.
             */
            virtual void setValue(T value) = 0;

            /*
             * Subscribes to this dynamic property.
             * Anytime the value returned by "getValue()" has changed, callback will be called with the new value.
             * Returns a boost::signals2::connection which can be used to unsubscribe.
             */
            boost::signals2::connection subscribe(const std::function<void (T)> & callback) const
            {
                return _signal.connect(callback);
            }

            virtual ~IDynamicProperty() {}
        protected:
            /*
             * Implementations should call this method to notify subscribers when the instance has taken on a new value
             */
            void notifySubscribers(T value) const
            {
                _signal(value);
            }

        private:
            mutable boost::signals2::signal<void (T)> _signal;
    };
}



#endif
