#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Delegate.hpp>

namespace VOID_NS {
    template<typename T, typename ... Args>
    class GetSet {
    public:
        Delegate<T> OnChange;

        GetSet(Args ... a) {
            value = T(std::forward<Args>(a)...);
        }
        virtual ~GetSet() = default;

        const T &Get() const {
            return value;
        }

        void Set(T value) {
            this->value = value;
            OnChange(this->value);
        }

    protected:
        T value;
    };
};
