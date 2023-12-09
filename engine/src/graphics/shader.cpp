#include "graphics/shader.hpp"
#include "platform/gl/shader_gl.hpp"

namespace Noether {
    std::shared_ptr<Shader> Shader::Create(const std::string& path) {
        return std::make_shared<ShaderGL>(path);
    }
}