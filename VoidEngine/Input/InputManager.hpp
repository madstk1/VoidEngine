#ifndef VOID_INPUT_INPUTMANAGER_H__
#define VOID_INPUT_INPUTMANAGER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Math/Vectors.hpp>
#include <VoidEngine/Input/Keycodes.hpp>

namespace VOID_NS {
    class Input {
    private:
    protected:
        static bool m_Keys[Keycode::MAX_KEYCODES];
        static Vector2 m_Cursor;

    public:
        static inline bool GetKeyDown(Keycode key) {
            VOID_ASSERT(key != Keycode::Unknown, "Keycode::Unknown is not a valid key.");
            return m_Keys[key];
        }

        static inline f32 GetAxis(std::string axis) {
            if(axis == "Mouse X") { return m_Cursor.x; }
            if(axis == "Mouse Y") { return m_Cursor.y; }

            Logger::LogWarning("Invalid axis: %s", axis.c_str());
            return 0.0f;
        }

        friend class Window;
        friend class WindowGL;
    };
};

#endif /* VOID_INPUT_INPUTMANAGER_H__ */
