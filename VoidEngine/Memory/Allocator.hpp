#pragma once

#include <memory>
#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/EngineTypes.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Misc/Translations.hpp>

namespace VOID_NS {
    /**
     *  Custom pointer for Void.
     *  While inherited from std::shared_ptr, it contains extra methods.
     */
    template<typename T>
    class Ptr : public std::shared_ptr<T> {
    protected:
        using ptr = std::shared_ptr<T>;

    public:
        Ptr() : ptr() {}
        Ptr(T *t) : ptr(t) {}
        Ptr(ptr t) : ptr(t) {}
        Ptr(const ptr &t) : ptr(t) {}
        Ptr(std::nullptr_t t) : ptr( t) {}
        
        operator T *() { return this->get(); }
        operator const T *() const { return this->get(); }
    };

    /**
     *  Custom allocator for Void.
     *  The allocator is used to measure memory allocations in Void.
     */
    class Allocator {
    public:
        static inline void *Allocate(u64 size) {
            return calloc(1, size);
        }

        static inline void *Allocate(u32 count, u64 size) {
            return calloc(count, size);
        }

        template<typename T, typename ... Args>
        static inline T *Allocate(Args&& ... args) {
            T *ptr = ::new T(std::forward<Args>(args)...);
            Logger::Assert(ptr != nullptr, Translator::TranslateString(Error::ErrorAllocation));

            return ptr;
        }

        template<typename T>
        static inline void Free(T *ptr) {
            ::delete(ptr);
        }
    };
};
