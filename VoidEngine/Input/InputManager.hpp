#pragma once

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Math/Linear.hpp>
#include <VoidEngine/Misc/Delegate.hpp>
#include <VoidEngine/Input/Keycodes.hpp>

namespace VOID_NS {
    class Input {
    public:
        /**
         *  Executed every time a new key is pressed down.
         */
        static Delegate<Keycode> OnKeyDown;

        /**
         *  Executed every time a new key is released.
         */
        static Delegate<Keycode> OnKeyUp;

        /**
         *  Returns the current state of a key.
         */
        static inline bool GetKeyDown(Keycode key) {
            Logger::Assert(key != Keycode::Unknown, "Keycode::Unknown is not a valid key.");
            return m_Keys[(i32) key];
        }

        /**
         *  Returns the current value for the passed axis.
         *
         *  Current axes:
         *   - Mouse X
         *   - Mouse Y
         */
        static inline f32 GetAxis(std::string axis) {
            if(axis == "Mouse X") { return m_Cursor.x; }
            if(axis == "Mouse Y") { return m_Cursor.y; }

            Logger::Warning("Invalid axis: %s", axis.c_str());
            return 0.0f;
        }

    protected:
        static bool m_Keys[(i32) Keycode::Count];
        static Vector2f m_Cursor;

        static inline void SetKey(Keycode key, bool value) {
            bool curr = m_Keys[(i32) key];

            if(curr != value) {
                if(curr)  { OnKeyDown(key); }
                if(!curr) { OnKeyUp(key); }
            }

            m_Keys[(i32) key] = curr;
        }

        static inline void SetMouse(Vector2f pos) {
            m_Cursor = pos;
        }

        static inline void SetMouse(f32 x, f32 y) {
            m_Cursor = {x, y};
        }

        friend class RendererGL;
    };
};
