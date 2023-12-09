#include "platform/gl/shader_gl.hpp"

#include <fstream>
#include <sstream>

namespace Noether {
    static ShaderSourceGL load_gl_shader_source(const std::string& path) {
        std::string code;
        std::ifstream file(path);
        if (!file.is_open()) {
            NT_ERROR("Failed to open shader source: %s", path.c_str());
            NT_ASSERT(false, "Failure to read shader.");
        }
        std::string line;
        std::stringstream streams[2];
        u32 shaderType = -1;
        while (getline(file, line)) {
            if (line.find("#shader") != std::string::npos) {
                if (line.find("vertex") != std::string::npos) {
                    shaderType = 0;
                } else if (line.find("fragment") != std::string::npos) {
                    shaderType = 1;
                }
            } else {
                streams[shaderType] << line << "\n";
            }
        }
        
        return {streams[0].str(), streams[1].str()};
    }

    ShaderGL::ShaderGL(const std::string& path) {
        u32 vertShader, fragShader;
        i32 success;

        const ShaderSourceGL source = load_gl_shader_source(path);
        const char* vertSource = source.VertexShaderCode.c_str();
        const char* fragSource = source.FragmentShaderCode.c_str();

        vertShader = glCreateShader(GL_VERTEX_SHADER); GL_LOG_ERROR
        glShaderSource(vertShader, 1, &vertSource, NULL); GL_LOG_ERROR
        glCompileShader(vertShader); GL_LOG_ERROR
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
            NT_ERROR("Shader Compilation Error: %s", infoLog);
        }

        fragShader = glCreateShader(GL_FRAGMENT_SHADER); GL_LOG_ERROR
        glShaderSource(fragShader, 1, &fragSource, NULL); GL_LOG_ERROR
        glCompileShader(fragShader); GL_LOG_ERROR
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success); GL_LOG_ERROR
        if (success == GL_FALSE) {
            char infoLog[512];
            glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
            NT_ERROR("Shader Compilation Error: %s", infoLog);
        }

        m_RendererID = glCreateProgram(); GL_LOG_ERROR
        glAttachShader(m_RendererID, vertShader); GL_LOG_ERROR
        glAttachShader(m_RendererID, fragShader); GL_LOG_ERROR
        glLinkProgram(m_RendererID); GL_LOG_ERROR
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
        if(!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
            NT_ERROR("Shader Linking Error: %s", infoLog);
        }

        glDeleteShader(vertShader); GL_LOG_ERROR
        glDeleteShader(fragShader); GL_LOG_ERROR
    }

    ShaderGL::~ShaderGL() {

    }   
}