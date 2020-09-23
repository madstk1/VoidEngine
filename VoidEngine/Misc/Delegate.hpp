#ifndef VOID_MISC_DELEGATE_H__
#define VOID_MISC_DELEGATE_H__

#include <vector>
#include <functional>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    template<typename ... A>
    class Delegate {
    public:
        typedef std::function<void(A...)> func;

        Delegate() {}
        virtual ~Delegate() = default;

        void operator += (func f) {
            m_Callbacks.push_back(f);
        }

        void operator () (A... args) {
            for(auto callback : m_Callbacks) {
                callback(std::forward<A>(args)...);
            }
        }
        
    protected:
        std::vector<func> m_Callbacks;
    };
};

#endif /* VOID_MISC_DELEGATE_H__ */
