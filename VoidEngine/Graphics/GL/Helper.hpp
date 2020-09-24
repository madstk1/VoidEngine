#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <VoidEngine/Core/Common.hpp>
#include <VoidEngine/Graphics/RenderTypes.hpp>

namespace VOID_NS {
    u32 Translate(ClearFlag e) {
        u32 r = 0;
        if(HASBIT(e, ClearFlag::ColorBufferBit))   { r |= GL_COLOR_BUFFER_BIT; }
        if(HASBIT(e, ClearFlag::DepthBufferBit))   { r |= GL_DEPTH_BUFFER_BIT; }
        if(HASBIT(e, ClearFlag::StencilBufferBit)) { r |= GL_STENCIL_BUFFER_BIT; }
        return r;
    }

    u32 Translate(DepthTest e) {
        switch(e) {
            case DepthTest::Always:        return GL_ALWAYS;
            case DepthTest::Never:         return GL_NEVER;
            case DepthTest::Less:          return GL_LESS;
            case DepthTest::LessEqual:     return GL_LEQUAL;
            case DepthTest::Greater:       return GL_GREATER;
            case DepthTest::GreaterEqual:  return GL_GEQUAL;
            case DepthTest::Equal:         return GL_EQUAL;
            case DepthTest::NotEqual:      return GL_NOTEQUAL;
            default: break;
        }
        return 0;
    }

    u32 Translate(CullFace e) {
        switch(e) {
            case CullFace::Front:   return GL_FRONT;
            case CullFace::Back:    return GL_BACK;
            case CullFace::Both:    return GL_FRONT_AND_BACK;
            default: break;
        }
        return 0;
    }
};
