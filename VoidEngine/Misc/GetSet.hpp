#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Delegate.hpp>

namespace VOID_NS {
    /**
     *  GetSet class.
     *
     *  Used to track changes of values and calling
     *  callbacks in reponse, with the new value.
     */
    template<typename T, typename ... Args>
    class GetSet {
    public:
        /**
         *  Callback delegates.
         *  These are run everytime the value is changed.
         */
        Delegate<T> OnChange;

        /**
         *  Create GetSet, with constructor arguments for the underlying type.
         */
        GetSet(Args ... a) {
            value = T(std::forward<Args>(a)...);
        }
        virtual ~GetSet() = default;

        /**
         *  Return the current value.
         */
        const T &Get() const {
            return value;
        }

        /**
         *  Set the current value and executes OnChange with the new value.
         */
        void Set(T value) {
            this->value = value;
            OnChange(this->value);
        }

        /**
         *  Default operator for assignment, for easier use.
         */
        void operator = (T value) {
            Set(value);
        }

        /**
         *  Default operator for retrieving, for easier use.
         */
        operator T () {
            return Get();
        }

    protected:
        T value;
    };
};
