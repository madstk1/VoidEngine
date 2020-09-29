#pragma once

#include <type_traits>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    /**
     *  Singleton class.
     *  A very simple singleton implementation.
     */
    template<class T>
    class Singleton {
    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    public:
        /**
         *  Delete any form of constructing.
         */
        Singleton(const Singleton &) = delete;
	    Singleton(Singleton &&) noexcept = default;

	    Singleton & operator = (const Singleton &) = delete;
	    Singleton & operator = (Singleton &&) noexcept = default;

        /**
         *  Return the underlying class.
         *  NOTE: The underlying class must the default-constructable.
         */
        static T *Get() {
            Logger::Assert(std::is_default_constructible<T>::value, "T is not constructable.");

            static T m_Instance;
            return &m_Instance;
        }
    };
};
