#pragma once

#include <functional>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Misc/Vector.hpp>

namespace VOID_NS {
    /**
     *  Delegate class.
     *  This is a more streamlined version of a callback.
     */
    template<typename ... A>
    class Hook {
    public:
        typedef std::function<void(A...)> func;

        Hook() {}
        virtual ~Hook() = default;

        /**
         *  Append callback to the delegate.
         */
        void operator += (func f) {
            m_Callbacks.Append(f);
        }

        /**
         *  Execute all callbacks, with the specified parameters.
         */
        void operator () (A... args) {
            for(auto callback : m_Callbacks) {
                callback(std::forward<A>(args)...);
            }
        }
        
    protected:
        Vector<func> m_Callbacks;
    };
};
