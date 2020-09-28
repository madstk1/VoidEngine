#pragma once

#include <uuid/uuid.h>
#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>

namespace VOID_NS {
    class UUID {
    public:
        UUID() {
            uuid_generate(m_ID);
        }

        bool operator == (const UUID &v) {
            return uuid_compare(m_ID, v.m_ID) == 0;
        }

    protected:
        uuid_t m_ID;
    };
};
