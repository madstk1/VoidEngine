#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <VoidEngine/Graphics/RendererTypes.hpp>

namespace VOID_NS {
    inline i32 Translate(CullFace face) {
        switch(face) {
            case CullFace::Front:    return GL_FRONT;
            case CullFace::Back:     return GL_BACK;
            case CullFace::Both:     return GL_FRONT_AND_BACK;
            case CullFace::Disabled: break;

            default: break;
        }
        return -1;
    }

    inline i32 Translate(FrontFace face) {
        switch(face) {
            case FrontFace::CW:     return GL_CW;
            case FrontFace::CCW:    return GL_CCW;

            default: break;
        }
        return -1;
    }

    inline u32 Translate(ClearFlag flag) {
        u32 res = 0;

        if(HASBIT((u32) flag, ClearColor))   { res |= GL_COLOR_BUFFER_BIT; }
        if(HASBIT((u32) flag, ClearDepth))   { res |= GL_DEPTH_BUFFER_BIT; }
        if(HASBIT((u32) flag, ClearStencil)) { res |= GL_STENCIL_BUFFER_BIT; }

        return res;
    }

    inline i32 Translate(DepthTest test) {
        switch(test) {
            case DepthTest::Always:         return GL_ALWAYS;
            case DepthTest::Never:          return GL_NEVER;
            case DepthTest::Less:           return GL_LESS;
            case DepthTest::LessEqual:      return GL_LEQUAL;
            case DepthTest::Greater:        return GL_GREATER;
            case DepthTest::GreaterEqual:   return GL_GEQUAL;
            case DepthTest::Equal:          return GL_EQUAL;
            case DepthTest::NotEqual:       return GL_NOTEQUAL;
            case DepthTest::Disabled:       break;

            default: break;
        }
        return -1;
    }
};
