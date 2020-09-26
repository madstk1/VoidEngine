#include <VoidEngine/Input/InputManager.hpp>
#include <VoidEngine/Graphics/GL/Renderer.hpp>

namespace VOID_NS {
    void RendererGL::HandleMouse(GLFWwindow *win) {
        static Vector2d lastMouse = {0.0f, 0.0f};
        Vector2d mousePosition = {0.0f, 0.0f};

        glfwGetCursorPos(win, &mousePosition.x, &mousePosition.y);
        Input::SetMouse(
            mousePosition.x - lastMouse.x,
            lastMouse.y - mousePosition.y
        );

        lastMouse = mousePosition;
    }

#define GLFW_KEY_MACRO(key, int) \
    case key: Input::SetKey((Keycode) int, action != GLFW_RELEASE); break

    void RendererGL::HandleKeyboard(i32 key, i32 action, i32 mods) {
        switch(key) {
            GLFW_KEY_MACRO(GLFW_KEY_SPACE        , Keycode::Space);
            GLFW_KEY_MACRO(GLFW_KEY_APOSTROPHE   , Keycode::Apostrophe);
            GLFW_KEY_MACRO(GLFW_KEY_COMMA        , Keycode::Comma);
            GLFW_KEY_MACRO(GLFW_KEY_MINUS        , Keycode::Minus);
            GLFW_KEY_MACRO(GLFW_KEY_PERIOD       , Keycode::Period);
            GLFW_KEY_MACRO(GLFW_KEY_SLASH        , Keycode::Slash);
            GLFW_KEY_MACRO(GLFW_KEY_0            , Keycode::Zero);
            GLFW_KEY_MACRO(GLFW_KEY_1            , Keycode::One);
            GLFW_KEY_MACRO(GLFW_KEY_2            , Keycode::Two);
            GLFW_KEY_MACRO(GLFW_KEY_3            , Keycode::Three);
            GLFW_KEY_MACRO(GLFW_KEY_4            , Keycode::Four);
            GLFW_KEY_MACRO(GLFW_KEY_5            , Keycode::Five);
            GLFW_KEY_MACRO(GLFW_KEY_6            , Keycode::Six);
            GLFW_KEY_MACRO(GLFW_KEY_7            , Keycode::Seven);
            GLFW_KEY_MACRO(GLFW_KEY_8            , Keycode::Eight);
            GLFW_KEY_MACRO(GLFW_KEY_9            , Keycode::Nine);
            GLFW_KEY_MACRO(GLFW_KEY_SEMICOLON    , Keycode::Semicolon);
            GLFW_KEY_MACRO(GLFW_KEY_EQUAL        , Keycode::Equal);
            GLFW_KEY_MACRO(GLFW_KEY_A            , Keycode::A);
            GLFW_KEY_MACRO(GLFW_KEY_B            , Keycode::B);
            GLFW_KEY_MACRO(GLFW_KEY_C            , Keycode::C);
            GLFW_KEY_MACRO(GLFW_KEY_D            , Keycode::D);
            GLFW_KEY_MACRO(GLFW_KEY_E            , Keycode::E);
            GLFW_KEY_MACRO(GLFW_KEY_F            , Keycode::F);
            GLFW_KEY_MACRO(GLFW_KEY_G            , Keycode::G);
            GLFW_KEY_MACRO(GLFW_KEY_H            , Keycode::H);
            GLFW_KEY_MACRO(GLFW_KEY_I            , Keycode::I);
            GLFW_KEY_MACRO(GLFW_KEY_J            , Keycode::J);
            GLFW_KEY_MACRO(GLFW_KEY_K            , Keycode::K);
            GLFW_KEY_MACRO(GLFW_KEY_L            , Keycode::L);
            GLFW_KEY_MACRO(GLFW_KEY_M            , Keycode::M);
            GLFW_KEY_MACRO(GLFW_KEY_N            , Keycode::N);
            GLFW_KEY_MACRO(GLFW_KEY_O            , Keycode::O);
            GLFW_KEY_MACRO(GLFW_KEY_P            , Keycode::P);
            GLFW_KEY_MACRO(GLFW_KEY_Q            , Keycode::Q);
            GLFW_KEY_MACRO(GLFW_KEY_R            , Keycode::R);
            GLFW_KEY_MACRO(GLFW_KEY_S            , Keycode::S);
            GLFW_KEY_MACRO(GLFW_KEY_T            , Keycode::T);
            GLFW_KEY_MACRO(GLFW_KEY_U            , Keycode::U);
            GLFW_KEY_MACRO(GLFW_KEY_V            , Keycode::V);
            GLFW_KEY_MACRO(GLFW_KEY_W            , Keycode::W);
            GLFW_KEY_MACRO(GLFW_KEY_X            , Keycode::X);
            GLFW_KEY_MACRO(GLFW_KEY_Y            , Keycode::Y);
            GLFW_KEY_MACRO(GLFW_KEY_Z            , Keycode::Z);
            GLFW_KEY_MACRO(GLFW_KEY_LEFT_BRACKET , Keycode::LeftSquareBracket);
            GLFW_KEY_MACRO(GLFW_KEY_BACKSLASH    , Keycode::Backslash);
            GLFW_KEY_MACRO(GLFW_KEY_RIGHT_BRACKET, Keycode::RightSquareBracket);
            GLFW_KEY_MACRO(GLFW_KEY_GRAVE_ACCENT , Keycode::Grave);
        }
    }
};
