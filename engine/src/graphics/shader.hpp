#pragma once

#include "core/defines.hpp"
#include "maths/vector.hpp"
#include "maths/matrix.hpp"

//TODO: Add API to set uniforms. Then draw a rotating test cube to check that the Matrices are all working okay.

namespace Noether {
    class Shader {
        public:
            static std::shared_ptr<Shader> Create(const std::string& path);
            virtual ~Shader() = default;
            
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual void SetUniformInt(const char* name, i32 value) = 0;

            virtual void SetUniformFloat(const char* name, f32 value) = 0;
            virtual void SetUniformFloat2(const char* name, Vec2 v) = 0;
            virtual void SetUniformFloat3(const char* name, Vec3 v) = 0;
            virtual void SetUniformFloat4(const char* name, Vec4 v) = 0;

            virtual void SetUniformMat2(const char* name, const Mat2& m) = 0;
            virtual void SetUniformMat3(const char* name, const Mat3& m) = 0;
            virtual void SetUniformMat4(const char* name, const Mat4& m) = 0;

            virtual void SetUniformBool(const char* name, bool value) = 0;
    };
}