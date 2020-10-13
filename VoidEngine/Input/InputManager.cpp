#include <VoidEngine/Input/InputManager.hpp>

namespace VOID_NS {
    Hook<Keycode> Input::OnKeyDown;
    Hook<Keycode> Input::OnKeyUp;

    bool Input::m_Keys[(i32) Keycode::Count];
    Vector2f Input::m_Cursor;
};
