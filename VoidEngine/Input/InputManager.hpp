#ifndef VOID_INPUT_INPUTMANAGER_H__
#define VOID_INPUT_INPUTMANAGER_H__

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Debug/Log.hpp>
#include <VoidEngine/Input/Keycodes.hpp>

namespace VOID_NS {
    class Input {
    private:
    protected:
        static bool m_Keys[Keycode::MAX_KEYCODES];
        static f32 m_CursorX;
        static f32 m_CursorY;

    public:
        static inline bool GetKeyDown(Keycode key) {
            VOID_ASSERT(key != Keycode::Unknown, "Keycode::Unknown is not a valid key.");
            return m_Keys[key];
        }

        friend class Window;
        friend class WindowGL;
    };
};

#endif /* VOID_INPUT_INPUTMANAGER_H__ */
