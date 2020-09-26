#pragma once

#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    template<class T>
    class Singleton {
    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    public:
        Singleton(const Singleton &) = delete;
	    Singleton(Singleton &&) noexcept = default;

	    Singleton & operator = (const Singleton &) = delete;
	    Singleton & operator = (Singleton &&) noexcept = default;

        static T *Get() {
            Logger::Assert(std::is_default_constructible<T>::value, "T is not constructable.");

            static T m_Instance;
            return &m_Instance;
        }
    };
};
