#pragma once

#include "graphics/shader.hpp"
#include "platform/gl/graphicsutils_gl.hpp"

namespace Noether {
    struct ShaderSourceGL {
        std::string VertexShaderCode;
        std::string FragmentShaderCode;
    };

    class ShaderGL : public Shader {
        public:
            ShaderGL(const std::string& path);
            ~ShaderGL();

            inline void Bind() override { glUseProgram(m_RendererID); GL_LOG_ERROR; }
            inline void Unbind() override { glUseProgram(0); GL_LOG_ERROR; }

            inline void SetUniformInt(const char* name, i32 value) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform1i(location, value); GL_LOG_ERROR;
            }

            inline void SetUniformFloat(const char* name, f32 value) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform1f(location, value); GL_LOG_ERROR;
            }

            inline void SetUniformFloat2(const char* name, Vec2 v) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform2fv(location, 1, (float*)&v); GL_LOG_ERROR;
            }

            inline void SetUniformFloat3(const char* name, Vec3 v) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform3fv(location, 1, (float*)&v); GL_LOG_ERROR;
            }

            inline void SetUniformFloat4(const char* name, Vec4 v) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform4fv(location, 1, (float*)&v); GL_LOG_ERROR;
            }

            inline void SetUniformMat2(const char* name, const Mat2& m) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniformMatrix2fv(location, 1, GL_FALSE, (float*)&m); GL_LOG_ERROR;
            }

            inline void SetUniformMat3(const char* name, const Mat3& m) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniformMatrix3fv(location, 1, GL_FALSE, (float*)&m); GL_LOG_ERROR;
            }

            inline void SetUniformMat4(const char* name, const Mat4& m) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&m); GL_LOG_ERROR;
            }

            inline void SetUniformBool(const char* name, bool value) override {
                i32 location = glGetUniformLocation(m_RendererID, name); GL_LOG_ERROR;
                glUniform1i(location, value); GL_LOG_ERROR;
            }

        private:
            u32 m_RendererID;
    };   
}