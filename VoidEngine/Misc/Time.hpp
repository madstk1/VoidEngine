#pragma once

#include <chrono>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    class Timestep {
    public:
        typedef std::chrono::microseconds default_unit;

        Timestep() {}
        Timestep(default_unit v) : value(v) {}

        const f64 Seconds() {
            return static_cast<f64>(value.count() / 1000000.0f);
        }

        const f64 Milliseconds() {
            return static_cast<f64>(value.count() / 1000.0f);
        }

        const f64 Microseconds() {
            return static_cast<f64>(value.count());
        }

        static Timestep Now() {
            static auto const start = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<default_unit>(std::chrono::high_resolution_clock::now() - start);
        }

    protected:
        default_unit value;
    };

    class Delta {
    public:
        void Update() {
            m_Current = Timestep::Now().Seconds();
            m_Change = m_Current - m_Last;
            m_Last = m_Current;
        }

        const f64 Difference() const {
            return m_Change;
        }

    protected:
        f64 m_Change = 0.0f;
        f64 m_Current, m_Last;
    };
};
