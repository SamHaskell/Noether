#pragma once

#include "core/defines.hpp"
#include "graphics/buffers.hpp"

#ifdef PLATFORM_WEB
    #include <GLES3/gl3.h>
#endif
#ifdef PLATFORM_MAC
    #include "glad/glad.h"
#endif

#define GL_LOG_ERROR { u32 e; while ((e = glGetError())) { NT_ERROR("%u", e); } }

namespace Noether {
    inline u32 get_buffer_element_type_component_count_gl(BufferElementType type) {
        switch(type) {
            case BufferElementType::Int:
                return 1;
            case BufferElementType::Int2:
                return 2;
            case BufferElementType::Int3:
                return 3;
            case BufferElementType::Int4:
                return 4;
            case BufferElementType::Float:
                return 1;
            case BufferElementType::Float2:
                return 2;
            case BufferElementType::Float3:
                return 3;
            case BufferElementType::Float4:
                return 4;
            case BufferElementType::Mat2:
                return 4;
            case BufferElementType::Mat3:
                return 9;
            case BufferElementType::Mat4:
                return 16;
            case BufferElementType::Bool:
                return 1;
            default:
                return 0;
        }
    }

    inline u32 get_buffer_element_type_native_gl(BufferElementType type) {
        switch(type) {
            case BufferElementType::Int:
                return GL_INT;
            case BufferElementType::Int2:
                return GL_INT;
            case BufferElementType::Int3:
                return GL_INT;
            case BufferElementType::Int4:
                return GL_INT;
            case BufferElementType::Float:
                return GL_FLOAT;
            case BufferElementType::Float2:
                return GL_FLOAT;
            case BufferElementType::Float3:
                return GL_FLOAT;
            case BufferElementType::Float4:
                return GL_FLOAT;
            case BufferElementType::Mat2:
                return GL_FLOAT;
            case BufferElementType::Mat3:
                return GL_FLOAT;
            case BufferElementType::Mat4:
                return GL_FLOAT;
            case BufferElementType::Bool:
                return GL_BOOL;
            default:
                return GL_NONE;
        }
    }
}