#ifndef VOID_CORE_ALLOCATOR_H__
#define VOID_CORE_ALLOCATOR_H__

#include <memory>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Errors.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    class Allocator {
    public:
        template<class T, typename... Args >
        static inline T *Allocate(Args&&... args) {
            m_AllocatedSize += sizeof(T);
            T *ptr = new T(std::forward<Args>(args)...);

            Logger::LogDebug("Allocated %ld bytes, %s", sizeof(T), typeid(T).name());
            VOID_ASSERT(ptr != nullptr, VOID_ERR_ALLOC);

            return ptr;
        }

        template<class T>
        static inline void Free(T *ptr) {
            VOID_ASSERT(ptr != nullptr, VOID_ERR_NULLPTR);

            m_AllocatedSize -= sizeof(T);
            delete ptr;
        }

    protected:
        static u64 m_AllocatedSize;

    private:
    };
};

#endif /* VOID_CORE_ALLOCATOR_H__ */
