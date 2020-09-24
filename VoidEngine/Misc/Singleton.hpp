#ifndef VOID_MISC_SINGLETON_H__
#define VOID_MISC_SINGLETON_H__

#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    template<class T>
    class Singleton {
    protected:
        explicit Singleton<T>() = default;

    public:
        static T *Get() {
            static T m_Instance;
            return &m_Instance;
        }
    };
};

#endif /* VOID_MISC_SINGLETON_H__ */
