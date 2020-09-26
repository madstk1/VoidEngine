#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Core/Engine.hpp>

namespace VOID_NS {
    class Delta {
    public:
        void Update() {
            m_Current = Engine::Get()->GetTime();
            m_Change = m_Current - m_Last;
            m_Last = m_Current;
        }

        const Time Difference() const {
            return m_Change;
        }

    protected:
        Time m_Change = 0.0f;
        Time m_Current, m_Last;
    };
};
