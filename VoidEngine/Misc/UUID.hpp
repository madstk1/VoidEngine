#pragma once

#include <uuid/uuid.h>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    /**
     *  Simple UUID class, for differentiating objects.
     */
    class UUID {
    public:
        /**
         *  On creation, generate a new UUID.
         */
        UUID() {
            uuid_generate(m_ID);
        }

        /**
         *  Simple comparison of UUIDs.
         */
        bool operator == (const UUID &v) {
            return uuid_compare(m_ID, v.m_ID) == 0;
        }

    protected:
        uuid_t m_ID;
    };
};
