#pragma once

#include <chrono>
#include <VoidEngine/Core/Common.hpp>

namespace VOID_NS {
    /**
     *  Timestep class.
     */
    class Timestep {
    public:
        typedef f64 unit;
        typedef std::chrono::microseconds default_unit;
        typedef std::chrono::high_resolution_clock clock;

        /**
         *  Constructors, both default and with defined value.
         */
        Timestep() {}
        Timestep(default_unit v) : value(v) {}

        /**
         *  Convert the value to seconds.
         */
        const unit Seconds() {
            return static_cast<unit>(value.count() / 1000000.0f);
        }

        /**
         *  Convert the value to milliseconds.
         */
        const unit Milliseconds() {
            return static_cast<unit>(value.count() / 1000.0f);
        }

        /**
         *  Convert the value to microseconds.
         */
        const unit Microseconds() {
            return static_cast<unit>(value.count());
        }

        /**
         *  Returns the current time since start, in microseconds.
         */
        static Timestep Now() {
            static auto const start = clock::now();
            return std::chrono::duration_cast<default_unit>(clock::now() - start);
        }

    protected:
        default_unit value;
    };

    /**
     *  Delta class.
     *  A more streamlined of measuring differences in time.
     */
    class Delta {
    public:
        /**
         *  Calculate the difference between last update.
         */
        void Update() {
            m_Current = Timestep::Now().Seconds();
            m_Change = m_Current - m_Last;
            m_Last = m_Current;
        }

        /**
         *  Returns the difference.
         */
        const f64 Difference() const {
            return m_Change;
        }

    protected:
        f64 m_Change = 0.0f;
        f64 m_Current, m_Last;
    };
};
